/**
 * @file    Guitar_Strings.c
 * @brief   Application entry point.
 */
#include "ADC.h"
#include "PIT.h"
#include "SPI.h"
#include "LCD_nokia.h"
#include "NVIC.h"
#include "RGB.h"
#include "Bits.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

#define VECTOR_SIZE 590*3

int main(void) {

	uint32_t index;
	uint32_t adc_value;
	uint32_t vectorADC[VECTOR_SIZE] = {0};
	uint32_t vectorADC_copy[VECTOR_SIZE] = {0};
	uint32_t vectorCorr[VECTOR_SIZE] = {0};

	SPI_config_Screen();
	configureTimer();
	Configure_ADC();
	configRGB();

	PIT_callback_init(setFlagTimer, PIT0);
	PIT_callback_init(ADC_Read, PIT1);

	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_5);

	NVIC_global_enable_interrupts;

	while(1) {

		if(read_ADC_flag())
		{
			writeLED(RED, !BIT_ON);
			writeLED(GREEN, !BIT_OFF);
			PIT_StartTimer(PIT, kPIT_Chnl_0);
			clear_ADC_flag();
			index = 0;
			while(!readFlagTimer())
			{
				if(read_flag_save_adc())
				{
					clear_flag_save_adc();
					vectorADC[index] = getValueADC();
					index++;
				}
			}
		}

		if(readFlagTimer())
		{
			PIT_StopTimer(PIT, kPIT_Chnl_0);
			PIT_StopTimer(PIT, kPIT_Chnl_1);
			clearFlagTimer();
			for(uint16_t x = 0; x<VECTOR_SIZE/3; x++)
			{
				vectorADC_copy[(VECTOR_SIZE/3)+x] = vectorADC[x];
			}
			for(uint16_t z = 1; z<=240; z++)
			{
				for(int16_t i = (VECTOR_SIZE/3)-1; i>=-1; i--)
				{
					if(i==-1)
					{
						vectorADC[i+z]=0;
					}
					else
					{
						vectorADC[i+z] = vectorADC[i+(z-1)];
					}
				}
				for(uint16_t j = 0; j<VECTOR_SIZE ;j++)
				{
					vectorCorr[z] += vectorADC[j]/100 * vectorADC_copy[j]/100;
				}
			}
			writeLED(RED, !BIT_OFF);
			writeLED(GREEN, !BIT_ON);
		}
	}
    return 0 ;
}

