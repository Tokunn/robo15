#!/usr/bin/env python2
# -*- coding: utf-8 -*-

### H27 Oug 29

import os, sys
import send_udp_command


#----- main() -----#
def main():
    ip_addr = '172.16.14.224'
    port = 4000
    buf = chr(0x41)

    UDP = send_udp_command.Send_UDP(ip_addr, port)

    UDP.send(buf)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nCtrl+C -> END")
    except send_udp_command.socket.error:
        print("Socket Error !")
        time.sleep(2)

