import struct, serial
num_pixels = 100

buffer = struct.pack(f'>{num_pixels}B', *list(range(num_pixels)))

ser = serial.Serial('/dev/ttyUSB0', 115200)
ser.write(buffer)
ser.close()
