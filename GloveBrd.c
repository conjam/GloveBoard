//includes 

int main() {
	init_all();
	
	while(1){
		GET_ADC_VALUES_ALL_CHANNELS(uint16_t * adc_data);
		GET_IMU_VALUES(uint16_t * imu_val);
		STORE_ADC_VALUES(uint16_t * lib, uint16_t * adc, uint16_t * imu);
		CHANGE_MASTER(uint16_t * lib);
		UPDATE_LEDS(uint16_t *	lib, uint16_t * mode);
		SEND_MESSAGE(uint16_t * adc, uint16_t * imu);
	}
}
