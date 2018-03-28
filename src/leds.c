#include <string.h>
#include <ch.h>
#include <chprintf.h>
#include <hal.h>
#include <hal_streams.h>
#include <memstreams.h>
#include "periph_driver.h"

THD_FUNCTION(leds, arg)
{
  println("<led blinking> thread started...");
  register uint32_t timepwm=30000;
/*  println("ledthread is running");*/
#define LED1 GPIOE_LED10_RED
#define LED2 GPIOE_LED8_ORANGE
#define LED3 GPIOE_LED6_GREEN
#define LED4 GPIOE_LED4_BLUE
#define LED5 GPIOE_LED3_RED
#define LED6 GPIOE_LED5_ORANGE
#define LED7 GPIOE_LED7_GREEN
#define LED8 GPIOE_LED9_BLUE
  /* Chibi s alredy configured this
  palSetPadMode(GPIOE, GPIOE_LED4_BLUE, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOE, GPIOE_LED3_RED, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOE, GPIOE_LED5_ORANGE, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOE, GPIOE_LED7_GREEN, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOE, GPIOE_LED9_BLUE, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOE, GPIOE_LED10_RED, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOE, GPIOE_LED8_ORANGE, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOE, GPIOE_LED6_GREEN, PAL_MODE_OUTPUT_PUSHPULL);*/
  if(arg != NULL)
  {
    timepwm = *(uint32_t*) arg;
  }
  while(1) 
  {                    
    palTogglePad(GPIOE, LED1);  
    chThdSleep(timepwm);        
    palTogglePad(GPIOE, LED1);  
    palTogglePad(GPIOE, LED2);  
    chThdSleep(timepwm);        
    palTogglePad(GPIOE, LED2);  
    palTogglePad(GPIOE, LED3);  
    chThdSleep(timepwm);        
    palTogglePad(GPIOE, LED3);  
    palTogglePad(GPIOE, LED4);  
    chThdSleep(timepwm);        
    palTogglePad(GPIOE, LED4);  
    palTogglePad(GPIOE, LED5);  
    chThdSleep(timepwm);        
    palTogglePad(GPIOE, LED5);  
    palTogglePad(GPIOE, LED6);  
    chThdSleep(timepwm);        
    palTogglePad(GPIOE, LED6);  
    palTogglePad(GPIOE, LED7);  
    chThdSleep(timepwm);        
    palTogglePad(GPIOE, LED7);  
    palTogglePad(GPIOE, LED8);  
    chThdSleep(timepwm);        
    palTogglePad(GPIOE, LED8);  
  }                             
}
extern void sys_halted(void)
{
  palWritePort(GPIOE, PAL_PORT_BIT(GPIOE_LED10_RED) | 
      PAL_PORT_BIT(GPIOE_LED3_RED));
}
