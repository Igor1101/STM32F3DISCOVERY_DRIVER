# STM32F3DISCOVERY_DRIVER
## How to compile this:
dependencies:
arm-none-eabi-gcc
arm-none-eabi-newlib
stlink
ChibiOS\RT

### Steps:

#### install above packages:
arm-none-eabi-gcc
arm-none-eabi-newlib
stlink
#### Download ChibiOS\RT source, 
for example from here: https://github.com/ChibiOS/ChibiOS
#### put this (DRIVER) directory into:
"CHIBIOSFOLDER"/demos/STM32/

#### run:
```
make # for compilation;
make install # for flashing to device
```

## I dont want to compile this, just run
your steps:
download [this](./build/ch.bin)
and flash.

### RUN DRIVER!
if you see the leds blinking and their light is running clockwise,
thats allright with driver, if you see only two red leds alight, 
this means kernel panic, if you see kernel panic, LET ME KNOW about that.
Connect uart to PA13, PA14 pins;(baud is 115200), and see results, gyroscope axis info.
