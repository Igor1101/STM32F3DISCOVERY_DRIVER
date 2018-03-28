/*\n\r\
 * Copyright (c) 2018 Igor Muravyov\n\r\
 * ChibiOS/RT - based STM32F303DISCOVERY peripherals driver\n\r\
 * for board based gyroscope and E-compass / accelerometer.\n\r\
 * This file (main.c) contains initialization process \n\r\
 * of this driver\\n\n\r\
 */
#include <string.h>
#include <ch.h>
#include <chprintf.h>
#include <hal.h>
#include <hal_streams.h>
#include <memstreams.h>
#include "periph_driver.h"

/* definitions */
MUTEX_DECL(stds);/* standart streams mutex */
/* variables */
char *COPYRIGHT =
"/*\n\r\
 * Copyright (c) 2018 Igor Muravyov\n\r\
 */\n\r";

BaseSequentialStream *  ser = (BaseSequentialStream *) &SD1;
/* working areas: */
static THD_WORKING_AREA(ledswa, WASTACK);
static THD_WORKING_AREA(ledswa1, WASTACK);
static THD_WORKING_AREA(l3gd20wa, WASTACK);

int main(void) 
{
  /* system init */
  halInit();
  /*
   * configure serial  \  USART 1 init
   * PA9(TX) and PA10(RX) 
   */

  chSysInit();
  sdStart(&SD1, NULL);
  palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));
  palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));
  println(BOARD_NAME);
  println(COPYRIGHT);
  println("ChibiOS/RT ver ");
  print(CH_KERNEL_VERSION);
  if(strcmp(CH_KERNEL_VERSION, "5.0.0") != 0)
  {
    println("warning: this software is written for 5.0.0 \
ChibiOS kernel");
  }
  /* creating leds thread */
  thread_t* ledsthr = chThdCreateStatic(ledswa, 
      sizeof (ledswa) , LOWPRIO, (tfunc_t)leds, NULL);
  const uint32_t freq=30000*60; /* */
  thread_t* ledsthr1 = chThdCreateStatic(ledswa1, 
      sizeof (ledswa1) , LOWPRIO, (tfunc_t)leds, (void*)&freq);

  /* creating l3gd20 driver thread */
  thread_t* l3gd20thr = chThdCreateStatic(l3gd20wa, 
      sizeof (l3gd20wa) , NORMALPRIO, (tfunc_t)l3gd20, NULL);
  while(1)
    chThdSleep(100);
}
