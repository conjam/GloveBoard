volatile uint32_t * REG_CONFIG = (uint32_t *) 0x40013000;
volatile uint32_t * REG_BASE = (uint32_t * ) 0x4001388;
void sysInit(){}
	

void spiInit(){
	MSS_SPI_init(&g_mss_spi1);
	MSS_SPI_configure_master_mode
 	(
 	&g_mss_spi1,
	 MSS_SPI_SLAVE_0,
	 MSS_SPI_MODE1,
 	MSS_SPI_PCLK_DIV_256,
 	8
 );
}
void gpioInit(){

	//CSN
	*REG_CONFIG = 1;
	//CE
	*(REG_CONFIG + 1) = 1;
	//IRQ
	*(REG_CONFIG + 2) = 2;
}

void csnLow() {
	*REG_BASE = *REG_BASE & 0xFFFE;
}

void csnHigh(){
	*REG_BASE |= 1;
}

void ceHigh(){
	*REG_BASE |= 2;
}

void ceLow(){
	*REG_BASE = *REG_BASE & 0xFFFC;
}

uint8_t spiXmitByte(uint8_t data){
	return (uint8_t) MSS_SPI_transfer_frame(
					 &g_mss_spi1, (uint32_t) data);
}

void delayUs(uint16_t delay){
	clock_t diff = delay * 100;
	clock_t start = clock();
	while(start - clock() < diff) {}
}
