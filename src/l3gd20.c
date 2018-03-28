#include <string.h>
#include <ch.h>
#include <chprintf.h>
#include <hal.h>
#include <hal_streams.h>
#include <memstreams.h>
#include "periph_driver.h"

BaseSequentialStream *  stdout_ch;

typedef union 
{
  uint16_t CMD;
  struct
  {
    uint8_t DO:8;/* data */
    uint8_t AD:6;/* reg address */
    bool MS:1;/* if 1: autoincrement */
    bool RW:1;/*if 1: read */
  } bits;
} l3gdCMD;

void init_l3gdCMD(void) 
{/* XYZ also enable */
  l3gdCMD reg;
  reg.bits.RW = 0;
  reg.bits.MS = 0;
  reg.bits.AD = 0x20;/* CTRL 1 */
  reg.bits.DO = 0b1111;
  spiSelect(&SPID1);
  spiSend(&SPID1, 1, &reg);
  spiUnselect(&SPID1);
}

bool is_l3gd_running(void)
{
  l3gdCMD txreg;
  l3gdCMD rxreg;
  txreg.bits.RW = 1;
  txreg.bits.MS = 0;
  txreg.bits.AD = 0x0F; /* WHO_AM_I */
  spiSelect(&SPID1);
  spiExchange(&SPID1, 1, &txreg, &rxreg);
  spiUnselect(&SPID1);
  chMtxLock(&stds);
  chprintf(stdout_ch, "\n\rL3GD10 INFO: %X", rxreg.CMD);
  chMtxUnlock(&stds);
  if((uint8_t)rxreg.CMD == 0b11010100)
  {
    return true;
  }
  return false;
}

THD_FUNCTION(l3gd20, arg)
{
  println("<l3gd20> thread started...");
  stdout_ch = (BaseSequentialStream *) &SD1;
  /* configure SPI1 */
  spiStop(&SPID1);
  static const SPIConfig spi1 = 
  {
    false, /* circular buffer mode */
    NULL, /* callback function after completion of 
             operation */
    GPIOE, /* port of CS */
    GPIOE_SPI1_CS, /* pin of CS */
    (1|1<<1|1<<2|(0b011)<<3), 
                              /* 
                               *  cr1 : 
                               *  MASTER
                               *  CPHA=1, 
                               *  CPOL=1, 
                               *  BAUD=f/16 
                               *  */
    (0b1111<<8)  /* 
                  * cr2:
                  * 16bitmode
                  */
  };
  spiStart(&SPID1, &spi1);
  /*
  palSetLineMode(LINE_SPI1_SCK, PAL_MODE_ALTERNATE(5)|PAL_STM32_PUPDR_PULLDOWN);
  palSetLineMode(LINE_SPI1_MOSI, PAL_MODE_ALTERNATE(5)|PAL_STM32_PUPDR_PULLDOWN);
  palSetLineMode(LINE_SPI1_CS, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_SPI1_MISO, PAL_MODE_ALTERNATE(5)|PAL_STM32_PUPDR_PULLDOWN);*/
  l3gdCMD txreg;
  l3gdCMD rxreg;
  init_l3gdCMD();
  if(is_l3gd_running() == true)
  {
    println("l3gd Succesfully initialized");
  }
  else
  {
    println("smth wrong with l3gd");
  }
  txreg.bits.RW = 1;/*read */
  txreg.bits.MS = 0;
  uint16_t conv;
  while(1) 
  {/* read axis info */
    spiSelect(&SPID1);
    chMtxLock(&stds);
    txreg.bits.AD = 0x28; /* XL */
    spiExchange(&SPID1, 1, &txreg, &rxreg);
    spiUnselect(&SPID1);
    spiSelect(&SPID1);
    conv = rxreg.CMD & 0xFF;/*least significant */
    txreg.bits.AD = 0x29; /* XH */
    spiExchange(&SPID1, 1, &txreg, &rxreg);
    spiUnselect(&SPID1);
    spiSelect(&SPID1);
    conv |= rxreg.CMD<<8;
    chprintf(stdout_ch, "\n\rL3GD10 X: %X", conv);
    txreg.bits.AD = 0x2A; /* YL */
    spiExchange(&SPID1, 1, &txreg, &rxreg);
    spiUnselect(&SPID1);
    spiSelect(&SPID1);
    conv = rxreg.CMD & 0xFF;/*least significant */
    txreg.bits.AD = 0x2B; /* YH */
    spiExchange(&SPID1, 1, &txreg, &rxreg);
    spiUnselect(&SPID1);
    spiSelect(&SPID1);
    conv |= rxreg.CMD<<8;
    chprintf(stdout_ch, "\n\rL3GD10 Y: %X", conv);
    txreg.bits.AD = 0x2C; /* ZL */
    spiExchange(&SPID1, 1, &txreg, &rxreg);
    spiUnselect(&SPID1);
    spiSelect(&SPID1);
    conv = rxreg.CMD & 0xFF;/*least significant */
    txreg.bits.AD = 0x2D; /* ZH */
    spiExchange(&SPID1, 1, &txreg, &rxreg);
    spiUnselect(&SPID1);
    conv |= rxreg.CMD<<8;
    chprintf(stdout_ch, "\n\rL3GD10 Z: %X", conv);
    chThdSleep(100000);
    chMtxUnlock(&stds);
    spiUnselect(&SPID1);
  }
  while(1);
}
