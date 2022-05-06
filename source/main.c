/**
 * @file    Guitar_Strings.c
 * @brief   Application entry point.
 */
#include "ADC.h"
#include "PIT.h"
#include "SPI.h"
#include "LCD_nokia.h"
#include "NVIC.h"
#include "Frequency_check.h"
#include "RGB.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

#define VECTOR_SIZE 200

int main(void) {

	uint32_t adc_value;
	uint32_t vectorADC[VECTOR_SIZE];

	SPI_config_Screen();
	configureTimer();
	Configure_ADC();
	configRGB();

	PIT_callback_init(ADC_Read, PIT0);
	PIT_callback_init(setFlagTimer, PIT1);

	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_5);

	NVIC_global_enable_interrupts;

	while(1) {

		if(read_ADC_flag())
		{
			PIT_StartTimer(PIT, kPIT_Chnl_1);
			clear_ADC_flag();
		}
		if(readFlagTimer())
		{

		}

    }
    return 0 ;
}
