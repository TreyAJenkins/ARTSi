import json

with open("keymap.json") as f:
    js = json.load(f)

karray = "int keyArr[] = {\n\t"

count = 0

for x in js:
    for y in x:
        count += 1
        name = x[y]
        name = name.replace(" ", "_").upper()
        print("#define KBD_" + name + " " + "0x" + y[0:2])
        #karray += "0x" + y[0:2] + ", "
        karray += "KBD_" + name + ", "
    karray += "\n\t"
    print("")

karray = karray.strip()
karray = karray[:-1]
karray += "\n};"

print("#define NUM_KEYS " + str(count) + "\n")

print(karray)

print("""

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
""")
