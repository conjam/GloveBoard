
#include "hardware_tiva.h"

char rx_bf[33];
uint8_t rxaddr[] = {0x69, 0x69, 0x69, 0x69, 0x69};
uint8_t txaddr[] = {0x69, 0x69, 0x69, 0x69, 0x69};

int main() {
		sysInit();

		nrf24_init(81);

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


		uint8_t count = 0;
		char* message = "this works, you can go to bed!!!";
		while(1) {
				nrf24_sendPacket(message, 32, FALSE);
				delayUs(500000);
		}
}
