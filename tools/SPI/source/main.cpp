#include "libspi.h"
#include <iostream>
#include <stdio.h>

#define MCP320X_PACKET_SIZE	1
#define MCP320X_DIFF		0
#define MCP320X_SINGLE		1
#define MCP320X_RESOLUTION	4095
#define MCP3204_CHANNELS	4
#define MCP3208_CHANNELS	8

#define SIZE 1

int main() {
    int bus=0, cs=1;
    uint8_t mode = !SPI_CPOL | SPI_CPHA;
    uint8_t packet[MCP320X_PACKET_SIZE] = {0x6};
    SPI *spi = new SPI(bus, cs, mode);

    uint8_t *rxbuf = spi->transfer(MCP320X_PACKET_SIZE, packet);

    printf("Send:0x%x \t Recive:0x%x\n", packet[0], rxbuf[0]);

    delete(rxbuf);
    delete(spi);
    return 0;
}
