#include "libspi.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PACKET_SIZE	1
#define BUS 0
#define CS 1

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4000);
    addr.sin_addr.s_addr = INADDR_ANY;
    char buf[2048];
    SPI *spi = new SPI(BUS, CS, !SPI_CPOL | SPI_CPHA);

    while (true) {
        bind(sock, (struct sockaddr *)&addr, sizeof(addr));
        memset(buf, 0, sizeof(buf));
        recv(sock, buf, sizeof(buf), 0);

        uint8_t packet[PACKET_SIZE] = {buf[0]};
        uint8_t *rxbuf = spi->transfer(PACKET_SIZE, packet);

        printf("Send:0x%x \t Recive:0x%x\n", packet[0], rxbuf[0]);
        delete(rxbuf);
    }
    delete(spi);

    return EXIT_SUCCESS;
}
