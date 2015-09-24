#!/usr/bin/env ipython2
# -*- coding: utf-8 -*-


import serial
import time


#----- main() -----#
def main():
    pic = serial.Serial('/dev/ttyUSB0', 9600)
    while True:
        cmd = ord(pic.read())
        print("{0}\t\t0b{1}".format(hex(cmd), bin(cmd)[2:].zfill(8)))


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nCtrl+C -> END")

