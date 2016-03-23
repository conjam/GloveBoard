#include "hardware_SF.h"

char * rf_buf[33];
int count;
int main() {
  nrf24_init(81);

  uint8_t rxaddr[] = {0x69, 0x69, 0x69, 0x69, 0x69 };
  uint8_t txaddr[] = {0x01, 0x02, 0x03, 0x02, 0x01 };
  nrf24_setRxAddress(PIPE_0, rxaddr);
  nrf24_setTxAddress(txaddr);
  nrf24_enableCRC(CRC_MODE_OFF);
  nrf24_enableDataPipe(PIPE_0, TRUE);
  nrf24_enableShockburst(PIPE_0, FALSE);
  nrf24_setAddressWidth(5);
  nrf24_listenMode(NRF_MODE);
  nrf24_setDataRate(SPEED_2M);
  nrf24_setPayloadSize(PIPE_0, NRF_PAYLOAD_SIZE);
  nrf24_powerUp(TRUE);

  while(1){
	count = nrf24_recvPacket(rx_buf);
		if(count != NRF_NO_DATA_AVAILABLE){
			rx_buf[count] = '\0'
			printf(count);
		}
	}
}
