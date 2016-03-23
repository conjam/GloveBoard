	

void ConfigReg(uint8_t reg, uint8_t value){
		set_gpio(CSN, 0);
		SPI_FULL(CMD_W_REGISTER | (0x1f & reg));
		SSI_FULL(value);
		set_gpio(CSN, 1);
}


void RF24_init(uint8_t channel, uint8_t listen) {
		SPI_INIT(); // fill in
		GPIO_INIT(); // fill in
		ConfigReg(REG_RF_CH, &channel); // write what channel
		RF24_cleanFifo(0);
		RF24_cleanFifo(1);
		uint8_t temp = listen + 2; //also turns power on
		ConfigReg(REG_CONFIG, &temp);
}

void GRead(uint8_t reg, uint8_t * data, uint8_t len){
	int i;
	set_gpio(CSN, 0);
	SPI_FULL(CMD_R_REGISTER | (0x1f & reg));
	for(i = 0; i < len; i++)
		SPI_FULL(0);
	set_gpio(CSN,0);
}

void GWrite(uint8_t reg, uint * data, uint8_t len){
	int i;
	set_gpio(CSN, 0);
	SPI_FULL(CMD_W_REGISTER | (0x1f & reg));
	for(i = 0; i < len; i++)
		SPI_FULL(data[i]);
	set_gpio(CSN,0);
}


void RF24_SET_TX_TARGET(uint8_t * addr){
	GWrite(REG_TX_ADDR, addr, 5);
}

void RF_RXFLUSH() {  
  set_gpio(CSN, 0);
  SPI_FULL(CMD_FLUSH_RX);
  csnHigh(CSN, 0);
}

void RF24_setRxAddress(uint8_t pipeId, uint8_t* rxAddr) {
  switch(pipeId) {
    case 0: 
      GWrite(REG_RX_ADDR_P0, rxAddr, 5);
      break;
    case 1:
      GWrite(REG_RX_ADDR_P1, rxAddr, 5);
      break;
    case 2:
      GWrite(REG_RX_ADDR_P2, rxAddr, 1);
      break;
    case 3:
      GWrite(REG_RX_ADDR_P3, rxAddr, 1);
      break;
    case 4:
      GWrite(REG_RX_ADDR_P4, rxAddr, 1);
      break;
    case 5:
      GWrite(REG_RX_ADDR_P5, rxAddr, 1);
      break;
    default:
      break;
  }
}

void RF24_SET_TX_TARGET(uint8_t * addr){
	GWrite(REG_TX_ADDR, addr, 5);
}

void RF24_GET_TX_TARGET(uint8_t * addr){
	GRead(REG_TX_ADDR, addr, 5);
}

int8_t SET_PAYLOAD(uint8_t * message, uint8_t length){
	if(length > 32 || length == 0)
		return -1;
	gpio_set(CSN, 0);
	SPI_FULL(CMD_W_TX_PAYLOAD);
	int i;
	for(i =0; i < length; ++i)
		SPI_FULL(message[i]);
	gpio_set(CSN, 1);
}
		
	

void SEND_PACKET_SLOW(uint8_t * addr, uint8_t *message ){
	ConfigReg(REG_CONFIG, 0x08);

	//set both RX and TX to the same address. need ack packet.
	RF24_setRxAddress(0, addr);
	RF24_SET_TX_TARGET(addr);

	SET_PAYLOAD(message, 25);


uint8_t nrf24_txFifoIsFull() {
  uint_8
  readRegisterB(REG_FIFO_STATUS, &fifostatus);
  return fifostatus.tx_full;
}

uint8_t nrf24_txFifoIsEmpty() {
  RegNrf24FIFO_STATUS_t fifostatus;
  readRegisterB(REG_FIFO_STATUS, &fifostatus);
  return fifostatus.tx_empty;
}
 


