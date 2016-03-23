#include "hardware.h"

void sysInit(){
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | 
				   SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);	//on board OSC is slower (10Mhz)
	//more?
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
}


/* 
	INITIALIZES SPI FOR THE NRF, ACCORDING TO 
	PCB DESIGN
*/

void spiInit(){
	

/*
s function configures the pin mux that selects the peripheral function associated with a
particular GPIO pin. Only one peripheral function at a time can be associated with a GPIO
pin, and each peripheral function should only be associated with a single GPIO pin at a time
(despite the fact that many of them can be associated with more than one GPIO pin). To fully
configure a pin, a GPIOPinType∗() function should also be called.
*/	

	GPIOPinConfigure(GPIO_PF0_SSI1RX);
	GPIOPinConfigure(GPIO_PF1_SSI1TX);
	GPIOPinConfigure(GPIO_PF2_SSI1CLK);


/*
SI pins must be properly configured for the SSI peripheral to function correctly. This
function provides a typical configuration for those pin(s); other configurations may work as well
depending upon the board setup (for example, using the on-chip pull-ups).
The pin(s) are specified using a bit-packed byte, where each bit that is set identifies the pin to
be accessed, and where bit 0 of the byte represents GPIO port pin 0, bit 1 represents GPIO
port pin 1, and so on.
*/
	GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |               GPIO_PIN_2);


	/* These values will change.
	 * Specifically, should probably change clock rate
	 * Fields, respectfully:
	 * BaseReg
	 * Clock Supplied to SSI
	 * Phase + Polarity (see DS for more)
	 * Mode (Master or Slave)
	 * Bit rate (see DS for req)
	 * Frame size, between 4 and 16 bits inclusive
	*/
	SSIConfigSetExpClk(SSI1_BASE, 4000000, SSI_FRF_MOTO_MODE_0,
		 SSI_MODE_MASTER, 1000000, 8);
	SSIEnable(SS1_BASE);
}

void gpioInit(){
	/*
		fields:
			PORT_BASE = which gpio port you're dealin w/
			PIN = BIT_MAP OF WHAT PINS U WANT. OR THESE PUPS
	*/

	//IRQ
	PinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_1);
	//CS
	PinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_0);
	//CE
	PinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
}

void csnHigh(){
	GPIOPinWrite(GPIO_Port_A, GPI0_PIN_0, 1);
}

void csnLow() {
	GPIOPinWrite(GPIO_Port_A, GPI0_PIN_0, 0);
}

void ceHigh() {
	GPIOPinWrite(GPIO_Port_F, GPI0_PIN_3, 1);
}

void ceLow() {
	GPIOPinWrite(GPIO_Port_F, GPI0_PIN_3, 0);
}

uint8_t spiXmitByte(uint8_t data){
	SSIDataPut(SSI1_BASE, data);
	uint32_t temp;
	while(SSIBusy(SSI1_BASE)){}
	SSIDataGet(SSI1_Base, &temp);
	temp &= 0xFF;
	return (uint8_t) temp;
}


//FIND BETTER WAY. THIS LEGIT WASTES CYCLES. 
void delayUs(uint16_t delay){
	SysCtlDelay(delay * (SysCtlClockGet() / (3000000)));
}



