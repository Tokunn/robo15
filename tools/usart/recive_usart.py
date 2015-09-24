#!/usr/bin/env ipython2
# -*- coding: utf-8 -*-


import serial
import time


#----- main() -----#
def main():
    pic = serial.Serial('/dev/ttyUSB0', 9600)
    while True:
        cmd = ord(pic.read())
        if (cmd > 128):
            cmd_10 = cmd - 128
        else:
            cmd_10 = cmd
        print("{0}\t\tspeed: {1}\t\t0b{2}".format(hex(cmd), cmd_10,  bin(cmd)[2:].zfill(8)))


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nCtrl+C -> END")

