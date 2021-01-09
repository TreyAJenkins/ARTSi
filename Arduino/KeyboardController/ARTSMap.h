#define KBD_M1 0x61
#define KBD_M2 0x62
#define KBD_M3 0x65
#define KBD_M4 0x66
#define KBD_CON 0x67
#define KBD_MAP 0x68
#define KBD_M5 0x69
#define KBD_M6 0x6A
#define KBD_M7 0x6B
#define KBD_M8 0x6C

#define KBD_M9 0x63
#define KBD_M10 0x64
#define KBD_M11 0x6D
#define KBD_M12 0x6E
#define KBD_TRK 0x6F
#define KBD_USR 0x70
#define KBD_M13 0x71
#define KBD_M14 0x72
#define KBD_M15 0x73
#define KBD_M16 0x74

#define KBD_CLEAR 0x5F
#define KBD_BACK_SPACE 0x3A
#define KBD_SPACE 0x3B
#define KBD_ENTER 0x3C

#define KBD_INIT_CNTL 0x00
#define KBD_TRK_RPOS 0x01
#define KBD_TRK_SUSP 0x02
#define KBD_TERM_CNTL 0x03
#define KBD_HDN_OFF 0x04
#define KBD_FLT_DATA 0x05
#define KBD_MULTI_FUNC 0x06
#define KBD_F8 0x07
#define KBD_TRIANGLE 0x3D
#define KBD_DOT 0x3E

#define KBD_F9 0x08
#define KBD_F10 0x09
#define KBD_CA 0x0A
#define KBD_F12 0x0B
#define KBD_F13 0x0C
#define KBD_F14 0x0D
#define KBD_TGT_GEN 0x0E
#define KBD_F16 0x0F
#define KBD_IFR_PLUS 0x3F
#define KBD_VFR_SLASH 0x40

#define KBD_A 0x41
#define KBD_B 0x42
#define KBD_C 0x43
#define KBD_D 0x44
#define KBD_E 0x45
#define KBD_F 0x46
#define KBD_G 0x47
#define KBD_1 0x31
#define KBD_2 0x32
#define KBD_3 0x33

#define KBD_H 0x48
#define KBD_I 0x49
#define KBD_J 0x4A
#define KBD_K 0x4B
#define KBD_L 0x4C
#define KBD_M 0x4D
#define KBD_N 0x4E
#define KBD_4 0x34
#define KBD_5 0x35
#define KBD_6 0x36

#define KBD_O 0x4F
#define KBD_P 0x50
#define KBD_Q 0x51
#define KBD_R 0x52
#define KBD_S 0x53
#define KBD_T 0x54
#define KBD_U 0x55
#define KBD_7 0x37
#define KBD_8 0x38
#define KBD_9 0x39

#define KBD_V 0x56
#define KBD_W 0x57
#define KBD_X 0x58
#define KBD_Y 0x59
#define KBD_Z 0x5A
#define KBD_ASTERISK 0x5B
#define KBD_MIN 0x5C
#define KBD_DEC 0x5D
#define KBD_0 0x30
#define KBD_INC 0x5E

#define NUM_KEYS 84

int keyArr[] = {
	KBD_M1, KBD_M2, KBD_M3, KBD_M4, KBD_CON, KBD_MAP, KBD_M5, KBD_M6, KBD_M7, KBD_M8,
	KBD_M9, KBD_M10, KBD_M11, KBD_M12, KBD_TRK, KBD_USR, KBD_M13, KBD_M14, KBD_M15, KBD_M16,
	KBD_CLEAR, KBD_BACK_SPACE, KBD_SPACE, KBD_ENTER,
	KBD_INIT_CNTL, KBD_TRK_RPOS, KBD_TRK_SUSP, KBD_TERM_CNTL, KBD_HDN_OFF, KBD_FLT_DATA, KBD_MULTI_FUNC, KBD_F8, KBD_TRIANGLE, KBD_DOT,
	KBD_F9, KBD_F10, KBD_CA, KBD_F12, KBD_F13, KBD_F14, KBD_TGT_GEN, KBD_F16, KBD_IFR_PLUS, KBD_VFR_SLASH,
	KBD_A, KBD_B, KBD_C, KBD_D, KBD_E, KBD_F, KBD_G, KBD_1, KBD_2, KBD_3,
	KBD_H, KBD_I, KBD_J, KBD_K, KBD_L, KBD_M, KBD_N, KBD_4, KBD_5, KBD_6,
	KBD_O, KBD_P, KBD_Q, KBD_R, KBD_S, KBD_T, KBD_U, KBD_7, KBD_8, KBD_9,
	KBD_V, KBD_W, KBD_X, KBD_Y, KBD_Z, KBD_ASTERISK, KBD_MIN, KBD_DEC, KBD_0, KBD_INC
};


struct COMMAND {
    byte MAGIC; // 0xEE
    bool SHIFT;
    bool CTRL;
    bool ALT;
    byte SCANCODE;
};

struct CONFIG {
    byte HEADER; // 0xAA
    COMMAND KEYMAP[NUM_KEYS];
    int ILLUMINATION;
	int MODE;
	byte RESERVED[32];
    byte FOOTER; // 0xBB
};
