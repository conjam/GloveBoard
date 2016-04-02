void ADC_init(){
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_3|GPIO_PIN_2 |GPIO_PIN_1|GPIO_PIN_0);
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2 |GPIO_PIN_1|GPIO_PIN_0);
	//jus incase you gotta change shit dog
    ADCSequenceDisable(ADC0_BASE, 0);

	/*
	 * Sets up SEQUENCE 0 at highest priority. SEQUENCE 0 takes
	 * 8 samples ALWAYS. Since we only have eight channels of ADC
	 * we don't need any other sequences going on, yfeel.
	 */
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
   
	
	/*
	 * Sets up the 8 ADC channels such that the channel number
	 * equals the step that they're being read from
	 *
     */
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE,0, 1, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE,0, 2, ADC_CTL_CH2);
	ADCSequenceStepConfigure(ADC0_BASE,0, 3, ADC_CTL_CH3);
	ADCSequenceStepConfigure(ADC0_BASE,0, 4, ADC_CTL_CH4);
	ADCSequenceStepConfigure(ADC0_BASE,0, 5, ADC_CTL_CH5);
	ADCSequenceStepConfigure(ADC0_BASE,0, 6, ADC_CTL_CH6); 
    //Interrupt is thrown after this step
	ADCSequenceStepConfigure(ADC0_BASE,0, 7,
	 ADC_CTL_CH7 | ADC_CTL_IE | ADC_CTL_END); 

	// Now we can actually send data.
    ADCSequenceEnable(ADC0_BASE, 0);

	/*
	 * Start a transaction with ADCProcessorTrigger.
	 * First field => denotes which ADC. We only use ADC0 for this
     * Second field => denotes the sequence. Only using sequence
	 * zero as well. 
	 *
    */

}

void BeginConversion(){
	ADCProcessorTrigger(ADC0_BASE, 0);
}

void ADCint_init(){
	ADCIntEnable(ADC0_BASE, 0);
	ADCIntEnableEx(ADC0_BASE, ADC_INT_SS0);
	ADCIntRegister(ADC0_BASE, 0, ADCHandler);
}

void ADCHandler(){
	ADCIntClear(ADC0_BASE, 0);
	ADCSequenceDataGet(ADC0_BASE, 0, GLOBAL_BUFFER);
}




void test() {
    while(1)
    {
    ADCIntClear(ADC0_BASE, 0);
        ADCProcessorTrigger(ADC0_BASE, 0);
        while(!ADCIntStatus(ADC0_BASE, 0, false))
        {
        }
        ADCSequenceDataGet(ADC0_BASE, 0, pui32ADC0Value);
    }
}
