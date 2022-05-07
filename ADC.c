/*
 * ADC.c
 *
 *  Created on: 4 may 2022
 *      Author: axel1
 */

#include "ADC.h"

boolean_t flag = FALSE;
boolean_t flag_save = FALSE;

uint32_t ADC_read = 0;

void Configure_ADC(void)
{
	adc16_config_t adc16ConfigStruct;

	CLOCK_EnableClock(kCLOCK_PortB);

	/* PORTB16 (pin 62) is configured as UART0_RX */
	PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);

	/* PORTB17 (pin 63) is configured as UART0_TX */
	PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt3);

	/* PORTB2 (pin 55) is configured as ADC0_SE12 */
	PORT_SetPinMux(PORTB, 2U, kPORT_PinDisabledOrAnalog);

	ADC16_GetDefaultConfig(&adc16ConfigStruct);
	ADC16_Init(ADC0, &adc16ConfigStruct);
	ADC16_EnableHardwareTrigger(ADC0, false);
	ADC16_DoAutoCalibration (ADC0);
}

uint32_t ADC_Read(void)
{
	adc16_channel_config_t adc16ChannelConfigStruct;
	adc16ChannelConfigStruct.channelNumber                        = 12U;
	adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
	adc16ChannelConfigStruct.enableDifferentialConversion = false;
	ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct);
	while (0U == (kADC16_ChannelConversionDoneFlag &
	  ADC16_GetChannelStatusFlags(ADC0, 0)))
	{
	}
	ADC_read = ADC16_GetChannelConversionValue(ADC0, 0);
	flag_save = TRUE;
	if(MIN_ADC_VALUE <= ADC_read)
	{
		set_ADC_flag();
	}
	return ADC_read;
}

uint32_t getValueADC(void)
{
	return ADC_read;
}

boolean_t read_ADC_flag(void)
{

	return flag;
}

void set_ADC_flag(void)
{
	flag = TRUE;
}
void clear_ADC_flag(void)
{
	flag = FALSE;
}

boolean_t read_flag_save_adc(void)
{
	return flag_save;
}

void clear_flag_save_adc(void)
{
	flag_save = FALSE;
}
