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
//	configRGB();


	while(1) {
		adc_value = ADC_Read();
		if(MIN_ADC_VALUE <= adc_value)
		{

		}
    }
    return 0 ;
}
