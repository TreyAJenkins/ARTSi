import time
import serial
import json

ser = serial.Serial("/dev/tty.SLAB_USBtoUART")
print(ser.name)


keys = [["M1", "M2", "M3", "M4", "CON", "MAP", "M5", "M6", "M7", "M8"],
	["M9", "M10", "M11", "M12", "TRK", "USR", "M13", "M14", "M15", "M16"],
	["CLEAR", "BACK SPACE", "SPACE", "ENTER"],
	["INIT CNTL", "TRK RPOS", "TRK SUSP", "TERM CNTL", "HDN OFF", "FLT DATA", "MULTI FUNC", "F8", "TRIANGLE", "DOT"],
	["F9", "F10", "CA", "F12", "F13", "F14", "TGT GEN", "F16", "IFR +", "VFR /"],
	["A", "B", "C", "D", "E", "F", "G", "1", "2", "3"],
	["H", "I", "J", "K", "L", "M", "N", "4", "5", "6"],
	["O", "P", "Q", "R", "S", "T", "U", "7", "8", "9"],
	["V", "W", "X", "Y", "Z", "*", "MIN", "DEC", "0", "INC"]]

keymap = []

def doRead():
	didRead = False
	partRead = bytearray()
	while (not didRead):
		i = ser.read()
		#print(i)
		if (i == bytes([0xAA])):
			continue
		else:
			if (len(partRead) > 0):
				didRead = True
			partRead += i
	return partRead.hex().upper()

for r in keys:
	row = {}
	print("Row: " + str(len(keymap)))
	for k in r:
		print("Press " + k)
		ch = doRead()
		print("Read " + ch)
		row[ch] = k
	keymap.append(row)

ser.close()


with open("keymap.json", "w") as f:
	json.dump(keymap, f)
