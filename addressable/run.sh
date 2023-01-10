#!/bin/sh

sudo chmod 777 /dev/ttyUSB0
stty -F /dev/ttyUSB0 115200 cs8 -cstopb -parenb # setup tty on output with 8 bit frame, one stop bit, no parity
sleep 5

cava -p ./config > /dev/ttyUSB0
