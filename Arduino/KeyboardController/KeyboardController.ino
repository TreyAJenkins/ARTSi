
#include "Keyboard.h"
#include "Mouse.h"
#include <EEPROM.h>
#include "ARTSMap.h"

//int STATUS_LED = 13;

int KBD_BAUD = 9600;
int COM_BAUD = 9600;
int mode = 0;

CONFIG config;

bool TRK_BTN[5];
int TRK_SENS = 10;
bool TRK_INVRT = true;

#define VSTARS 1
#define VERAM 2

#define DEBUG 0

#define SHIFT TRK_BTN[0]

void(* resetFunc) (void) = 0;

void setup() {
    // put your setup code here, to run once:
    //pinMode(STATUS_LED, OUTPUT);

    mode = DEBUG;

    Serial.begin(COM_BAUD);
    Serial1.begin(KBD_BAUD);

    Serial1.setTimeout(100);
    //Mouse.begin();

    if (!DEBUG) {
        Keyboard.begin();
        Mouse.begin();
    }

    delay(1000);
    Serial.println("# Reading EEPROM");
    EEPROM.get(0, config);
    if (!(config.HEADER == 0xAA && config.FOOTER == 0xBB)) {
        Serial.println(config.FOOTER, HEX);
        Serial.println("# EEPROM not initialized");
        Serial.println("# INIT EEPROM");
        initEEPROM();
        Serial.println("# EEPROM initialized");
        //resetFunc();
    }
    Serial.println("# Loaded from EEPROM");

}

byte nextKey() {
    //while (true) {
        if (Serial1.available() > 0) {

            unsigned char inChar = Serial1.read();
            //if (DEBUG) Serial.write((int)(inChar));
            if (inChar == 0xAA) { // Keyboard heartbeat
                //if (DEBUG) Serial.println("heartbeat");
                return;
            }

            if (inChar == 0x1B) { // Trackball data
                trackball();
            }

            if (DEBUG) {
                Serial.print("RX: ");
                Serial.print(inChar, HEX);
                Serial.println();
            }
            //Serial.println(findInKeyArray(inChar));

            if (findInKeyArray(inChar) != -1) {
                //Serial.println("VALID KEY");
                return inChar;
            }
        }
        return -1;
    //}
}

void trackball() {
    //delay(100);
    byte ball[4] = {};
    Serial1.readBytes(ball, 4);

    int x = ball[0];
    int y = ball[1];
    byte status = ball[2];

    if (!(status & (1 << 6))) {
        if (DEBUG) Serial.println("TRK Update");
        TRK_BTN[0] = (status & (1 << 1));
        TRK_BTN[1] = (status & (1 << 2));
        TRK_BTN[2] = (status & (1 << 3));
        TRK_BTN[3] = (status & (1 << 4));
        TRK_BTN[4] = (status & (1 << 5));

        bool TRK_ENTR = (status & (1 << 0));

        if (x >= 64) {
            x = x - 128;
        }

        if (y >= 64) {
            y = y - 128;
        }

        if (TRK_INVRT) {
            y *= -1;
        }

        x *= TRK_SENS;
        y *= TRK_SENS;

        if (x != 0 || y != 0) {
            Mouse.move(x, y, 0);
        }

        if (TRK_ENTR && !Mouse.isPressed()) {
            Mouse.press();
        }

        if (!TRK_ENTR && Mouse.isPressed()) {
            Mouse.release();
        }

        if (DEBUG) {
            Serial.print(x);
            Serial.print(" ");
            Serial.print(y);
            Serial.print(" ");
            Serial.print(ball[2], BIN);
            Serial.print(" ");
            Serial.print(ball[3], HEX);
            Serial.println("");
        }
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    byte next = nextKey();
    if (next != -1) {
        handleKeypress(next);
    }

}

void sendKey(unsigned char key) {
    Keyboard.write(key);
    if (DEBUG) Serial.println(key);
}

void sendCTRL(unsigned char key) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(key);
    Keyboard.releaseAll();
}

void handleKeypress(unsigned char key) {

    if (SHIFT == 1) {
        switch (key) {
            case KBD_L: // LDR
                if (mode == VSTARS)
                    sendCTRL(KEY_F5);
                return;
        }
    }

    switch (key) {
        case KBD_0 ... KBD_9:
            sendKey(key);
            break;
        case KBD_A ... KBD_Z:
            sendKey(key);
            break;
        case KBD_CLEAR:
            sendKey(KEY_ESC);
            break;
        case KBD_BACK_SPACE:
            sendKey(KEY_BACKSPACE);
            break;
        case KBD_SPACE:
            sendKey(' ');
            break;
        case KBD_ENTER:
            sendKey(KEY_RETURN);
            break;
        default:
            if (mode == 0) {
                sendKey(key);
            }
            break;
    }

    if (mode == VSTARS) {
        switch (key) {
            case KBD_TRIANGLE:
                sendKey('~');
                break;
            case KBD_MIN:
                sendKey(KEY_END);
                break;
            case KBD_INIT_CNTL:
                sendKey(KEY_F3);
                break;
            case KBD_TERM_CNTL:
                sendKey(KEY_F4);
                break;
            case KBD_HDN_OFF:
                sendKey(KEY_F5);
                break;
            case KBD_MULTI_FUNC:
                sendKey(KEY_F7);
                break;
            case KBD_FLT_DATA:
                sendKey(KEY_F9);
                break;
            case KBD_CA:
                sendKey(KEY_F11);
                break;
            case KBD_MAP: // Sign On
                sendKey(KEY_F12);
                break;
            case KBD_M2: // Center
                sendCTRL(KEY_F1);
                break;
            case KBD_M3: // Maps
                sendCTRL(KEY_F2);
                break;
            case KBD_M5: // Brite
                sendCTRL(KEY_F4);
                break;
            case KBD_M6: // LDR
                sendCTRL(KEY_F5);
                break;
            case KBD_M7: // CHARSIZE
                sendCTRL(KEY_F6);
                break;
            case KBD_M8: // DCB-SHIFT
                sendCTRL(KEY_F7);
                break;
            case KBD_M9: // DCB
                sendCTRL(KEY_F8);
                break;
            case KBD_M10: // RNGRING
                sendCTRL(KEY_F9);
                break;
            case KBD_M11: // RANGE
                sendCTRL(KEY_F10);
                break;
            case KBD_M15: // SITE
                sendCTRL(KEY_F11);
                break;
        }
    }
}

int findInKeyArray(byte key) {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (keyArr[i] == key) return i;
    }
    return -1;
}

void initEEPROM() {
    return 0; // disable this function
    CONFIG newConfig = {};
    COMMAND newCommand = {};

    newConfig.HEADER = 0xAA;
    newConfig.FOOTER = 0xBB;
    newConfig.ILLUMINATION = 0;
    newConfig.MODE = 0;

    newCommand.MAGIC = 0xEE;
    newCommand.SHIFT = 0;
    newCommand.CTRL = 0;
    newCommand.ALT = 0;
    newCommand.SCANCODE = 0;

    for (int i = 0; i < NUM_KEYS; i++) {
        newConfig.KEYMAP[i] = newCommand;
    }

    EEPROM.put(0, newConfig);
    config = newConfig;
}
