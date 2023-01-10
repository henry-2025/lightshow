PORT=/dev/ttyUSB0

build: addressable.ino
	arduino-cli compile -b arduino:avr:nano:cpu=atmega328old

flash: build
	arduino-cli upload -b arduino:avr:nano:cpu=atmega328old -p $(PORT) -t
