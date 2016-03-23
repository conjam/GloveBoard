#include "nrf24l01p.h"

#include "time.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
void sysInit();
void spiInit(); 
void csnLow();
void csnHigh();
void gpioInit();
void delayUs(uint16_t delay);
uint8_t spiXmitByte(uint8_t data);
void ceHigh();
void ceLow();
