/*----------------------------------------------------*\
 * This is a library to interface the DAC8564 DAC chip *
 * with a Raspberry Pi usign BCM2835 library           *
 *                                                     *
 * Author: Marco Duarte                                *
 \----------------------------------------------------*/
 
#ifndef DAC8564_BCM2835_h
#define DAC8564_BCM2835_h

#include <bcm2835.h>
#include <stdio.h>

//address of the DAC set by pins 14 (A1) and 13(A0)
#define ADDR_00  0x000000
#define ADDR_01  0x400000
#define ADDR_10  0x800000
#define ADDR_11  0xC00000

//buffer addresses
#define BUFF_A   0x000000
#define BUFF_B   0x020000
#define BUFF_C   0x040000
#define BUFF_D   0x060000

//commands
#define WRITE_BUFF              0x000000
#define WRITE_BUFF_PWR_DOWN     0x010000
#define WRITE_BUFF_LOAD_DAC     0x100000
#define WRITE_BUFF_PWR_LOAD     0x110000
#define WRITE_BUFF_LOAD_ALL     0x200000
#define WRITE_BUFF_PWR_LOAD_ALL 0x210000

//broadcast commands, used when daisy chaining
#define UPDATE_ALL_WITH_BUFF    0x300000
#define WRITE_LOAD_ALL          0x340000
#define WRITE_PWR_ALL           0x350000

//DAC operating modes. Used for power commands
#define NORMAL            0x0000
#define OUTPUT_OHMS_1K    0x4000
#define OUPUT_OHMS_100K   0x8000
#define OUTPUT_HIGH_Z     0xC000

#define SPI_0                 0
#define SPI_AUX               1 //aka SPI1 

class DAC8564
{
  public:
    void sendCommand(uint32_t cmd, uint32_t buff, uint16_t data);
    void disableInternalRef();
    void enableInternalRef();
    void enableInternalRefAlways(); //Keeps the DAC's internal reference on regardless of the DAC state
    void powerDown(uint32_t buff, uint16_t mode);
    bool begin(uint8_t spiModule=SPI_AUX, uint8_t cs=0, uint32_t dacAddr=ADDR_00);
    void sendVal(uint16_t val, uint32_t buff);
    
  private:
    uint8_t spiModule;
    uint8_t cs;
    uint32_t addr;
};

#endif
