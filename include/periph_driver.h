#ifndef DRINC
#define DRINC
#include <string.h>
#include <ch.h>
#include <chprintf.h>
#include <hal.h>
#include <hal_streams.h>
#include <memstreams.h>
/*definitions */

#define STREAMSIZE SERIAL_BUFFERS_SIZE 
#define WASTACK 128
/* variables */
extern mutex_t stds;
/*funcs */
void leds(void *args);
void l3gd20(void *args);
void println(char* str);
void print(char* str);
void sys_halted(void);


#endif /* DRINC */
