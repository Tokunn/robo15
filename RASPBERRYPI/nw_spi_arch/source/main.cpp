#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PACKET_SIZE	1
#define BUS 0
#define CS 1
#define SPEED 500000
#define MODE 3

#define VALUE 0x2e

const static char       *spiDev0  = "/dev/spidev0.0" ;
const static char       *spiDev1  = "/dev/spidev0.1" ;
const static uint8_t     spiBPW   = 8 ;
const static uint16_t    spiDelay = 0 ;

static uint32_t    spiSpeeds [2] ;
static int         spiFds [2] ;

int wiringPiSPIDataRW (int channel, unsigned char *txbuf, unsigned char *rxbuf, int len)
{
  struct spi_ioc_transfer spi ;

  channel &= 1 ;

  memset (&spi, 0, sizeof (spi)) ;

  spi.tx_buf        = (unsigned long)txbuf ;
  spi.rx_buf        = (unsigned long)rxbuf ;
  spi.len           = len ;
  spi.delay_usecs   = spiDelay ;
  spi.speed_hz      = spiSpeeds [channel] ;
  spi.bits_per_word = spiBPW ;

  return ioctl (spiFds [channel], SPI_IOC_MESSAGE(1), &spi) ;
}

int wiringPiSPISetupMode (int channel, int speed, int mode)
{
  int fd ;

  mode    &= 3 ;	// Mode is 0, 1, 2 or 3
  channel &= 1 ;	// Channel is 0 or 1

  if ((fd = open (channel == 0 ? spiDev0 : spiDev1, O_RDWR)) < 0)
      return -1;

  spiSpeeds [channel] = speed ;
  spiFds    [channel] = fd ;

  if (ioctl (fd, SPI_IOC_WR_MODE, &mode)            < 0)
      return -1;
  if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0)
      return -1;
  if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)   < 0)
      return -1;

  return fd ;
}

int wiringPiSPISetup (int channel, int speed)
{
  return wiringPiSPISetupMode (channel, speed, 0) ;
}


int main() {
    printf("nw_spi starting ... ");
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4000);
    addr.sin_addr.s_addr = INADDR_ANY;
    char buf[2048];
    //SPI *spi = new SPI(BUS, CS, !SPI_CPOL | SPI_CPHA);
    wiringPiSPISetupMode(CS, SPEED, MODE);
    printf("done\n");

    while (true) {
        bind(sock, (struct sockaddr *)&addr, sizeof(addr));
        memset(buf, 0, sizeof(buf));
        recv(sock, buf, sizeof(buf), 0);

        unsigned char packet[PACKET_SIZE] = {buf[0]};
        unsigned char rxbuf;
        //uint8_t *rxbuf = spi->transfer(PACKET_SIZE, packet);
        //printf("Send:0x%x \t Recive:0x%x\n", packet[0], rxbuf[0]);
        int return_val = wiringPiSPIDataRW(CS, packet, &rxbuf, 1);
        //printf("txbuf:%d, rxbuf:%d return:%d\n", packet[0], rxbuf, return_val);
        printf("Send:0x%x \t Recive:0x%x\n", packet[0], rxbuf);
        //delete(rxbuf);
    }
    //delete(spi);

    return EXIT_SUCCESS;
}
