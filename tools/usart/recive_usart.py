#!/usr/bin/env python2
# -*- coding: utf-8 -*-


import serial
import time


#----- main() -----#
def main():
    pic = serial.Serial('/dev/ttyUSB0', 9600)
    while True:
        cmd = ord(pic.read())
        sig = '+'
        if (cmd >= 128):
            cmd_10 = cmd - 128
            sig = '-'
        else:
            cmd_10 = cmd
            sig = '+'
        print("{0}\t\tspeed: {1}{2}\t\t0b{3}".format(hex(cmd), sig, cmd_10,  bin(cmd)[2:].zfill(8)))


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nCtrl+C -> END")

