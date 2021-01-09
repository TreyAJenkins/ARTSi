import time
import serial

ser = serial.Serial("/dev/tty.SLAB_USBtoUART")
print(ser.name)


for i in range(0, 255):
	b = bytes([0xa0,i])
	print(b)
	ser.write(b)
	time.sleep(0.5)

ser.close()
