#include <string.h>
#include <ch.h>
#include <chprintf.h>
#include <hal.h>
#include <hal_streams.h>
#include <memstreams.h>
#include "periph_driver.h"


uint8_t streamBuffer[STREAMSIZE];
/* procedures */
void println(char* str)
{
  chMtxLock(&stds);
  chnWriteTimeout((BaseChannel*)&SD1, (uint8_t *)"\n\r", 2, TIME_IMMEDIATE);
  chnWriteTimeout((BaseChannel*)&SD1, 
      (uint8_t*)str, strlen(str), TIME_IMMEDIATE);
  chMtxUnlock(&stds);
}

void print(char* str)
{
  chMtxLock(&stds);
  chnWriteTimeout((BaseChannel*)&SD1, 
      (uint8_t*)str, strlen(str), TIME_IMMEDIATE);
  chMtxUnlock(&stds);
}
