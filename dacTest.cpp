#include <bcm2835.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "DAC8564_BCM2835.h"

int main()
{
  DAC8564 dac;
  struct timespec delay;
  
  delay.tv_sec = 1;
  delay.tv_nsec = 10000;
  
  if (!bcm2835_init())
  {
    printf("bcm2835_init failed. Are you running as root??\n");
    return 1;
  }
  
  //change tp bcm2835_aux_spi_begin() if using SPI1
  if (!bcm2835_spi_begin())
  {
    printf("bcm2835_spi_begin failed. Are you running as root??\n");
    return 1;
  }
  
  //using SPI0 and CS1, comment arguments for SPI1 and CS2
  if(!dac.begin(SPI_0, BCM2835_SPI_CS1))
    return 1;
  
  
  
  //char c;
  //printf("enter something\n");
  
  //scanf("%c", &c);
  
  while(1)
  {
    //dac.enableInternalRef();
    //sleep(20);
    dac.disableInternalRef();
    sleep(20);
	  //write to dac
    //uint16_t val = rand() % 66536;
    //dac.sendVal(val, BUFF_A);
    //printf("val = %d ", val);
    //printf("Voltage = %f\n", (((float)(val)) * 4.096f)/(65535));
	  //nanosleep(&delay, NULL); //must wait at least 10000 ns before next read
  }
}
