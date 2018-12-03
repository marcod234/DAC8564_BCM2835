/*----------------------------------------------------*\
 * This is a library to interface the DAC8564 DAC chip *
 * with a Raspberry Pi usign BCM2835 library           *
 *                                                     *
 * Author: Marco Duarte                                *
 \----------------------------------------------------*/

#include "DAC8564_BCM2835.h"

void DAC8564::sendCommand(uint32_t cmd, uint32_t buff, uint16_t data)
{
  //for power commands just pass (<opMode> << 13) for data parameter
  
  uint32_t send = this->addr | cmd | buff | data;
  
  char out[3] = {0};
  
  out[0] = send >> 16;
  out[1] = send >> 8;
  out[2] = send;
  
  printf("sending: %.2x %.2x %.2x\n", out[0], out[1], out[2]);
  
  if(spiModule == SPI_AUX)
    bcm2835_aux_spi_writenb(out, sizeof(out));
  else
  {
    bcm2835_spi_chipSelect(this->cs);
    //bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16);
    bcm2835_spi_writenb(out, sizeof(out));
  }
}

void DAC8564::disableInternalRef()
{
  sendCommand(0x010000, 0x000000, 0x2000);
}

void DAC8564::enableInternalRef()
{
  sendCommand(0x010000, 0x000000, 0x0000);
}

void DAC8564::enableInternalRefAlways()
{
  sendCommand(0x010000, 0x000000, 0x1000);
} 

void DAC8564::powerDown(uint32_t buff, uint16_t mode)
{
  sendCommand(WRITE_BUFF_PWR_LOAD, buff, mode);  
}

bool DAC8564::begin(uint8_t spiModule, uint8_t cs, uint32_t dacAddr)
{
  this->cs = cs;
  this->spiModule = spiModule;
  this->addr = dacAddr;
  
  if(this->spiModule == SPI_AUX)
  {
    uint16_t clockDivider = bcm2835_aux_spi_CalcClockDivider(3125000);
    bcm2835_aux_spi_setClockDivider(clockDivider);
  }
  else if(this->spiModule == SPI_0)
  {
    if(this->cs != BCM2835_SPI_CS0 && this->cs != BCM2835_SPI_CS1)
    {
      printf("Choose BCM2835_SPI_CS0 or BCM2835_SPI_CS1\n");
      return false;
    }
    
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16);
    bcm2835_spi_chipSelect(this->cs);
    bcm2835_spi_setChipSelectPolarity(this->cs, LOW);
  }
  else
  {
    printf("Choose MCP3008_SPI_AUX or MCP3008_SPI_0\n");
    return false;
  }
  
  return true;
}

void DAC8564::sendVal(uint16_t val, uint32_t buff)
{
  //write to buff and simultaneously load DAC
  sendCommand(WRITE_BUFF_LOAD_DAC, buff, val);
}
