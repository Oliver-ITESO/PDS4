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

#define VECTOR_SIZE 400
#define CONST 2048

double frequencyvalue();

int32_t vectorCorr[VECTOR_SIZE*2] = {0};

int main(void) {

	uint32_t index;
	int32_t vectorADC[VECTOR_SIZE] = {0};

	SPI_config_Screen();
	LCD_nokia_init();

	configureTimer();
	Configure_ADC();
	configRGB();

	PIT_callback_init(setFlagTimer, PIT0);
	PIT_callback_init(ADC_Read, PIT1);

	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_5);

	NVIC_global_enable_interrupts;

	while(1)
	{

		if(read_ADC_flag())
		{
			PIT_StartTimer(PIT, kPIT_Chnl_0);
			while(!readFlagTimer());
			clearFlagTimer();
			writeLED(RED, !BIT_ON);
			writeLED(GREEN, !BIT_OFF);
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
			int16_t virtual_index_start;
			uint32_t virtual_value;
			uint32_t virtual_value_c;

			//Adecuacion de vector para negativos y positivos
			for(uint16_t v = 0 ; v < VECTOR_SIZE; v++)
			{
				if(vectorADC[v] != 0)
				{
					vectorADC[v] = vectorADC[v]-CONST;
				}
			}
			//Correlacion
			for(uint16_t z = 1; z<=(VECTOR_SIZE*2)-1; z++)
			{
				virtual_index_start = VECTOR_SIZE-z;

				for(uint16_t c = 0 ; c<z ; c++)
				{
					if((virtual_index_start+c) >= 0)
					{
						virtual_value_c = vectorADC[virtual_index_start+c];
					}
					else
					{
						virtual_value_c = 0;
					}
					if(c < VECTOR_SIZE)
					{
						virtual_value = vectorADC[c];
					}
					else
					{
						virtual_value = 0;
					}
					vectorCorr[z] += (virtual_value*virtual_value_c)/10000000;
				}
				vectorCorr[z] /= 100;
			}
			//Leemos frecuencia
			double freq = frequencyvalue();

			uint8_t freq_cm = freq/100;
			uint8_t freq_dm = (freq-freq_cm*100)/10;
			uint8_t freq_m = (freq-freq_cm*100-freq_dm*10);
			uint8_t freq_cent = (freq-freq_cm*100-freq_dm*10-freq_m)*10;
			uint8_t freq_dec = ((freq*10)-freq_cm*1000-freq_dm*100-freq_m*10-freq_cent)*10;

			freq_cm += '0';
			freq_dm += '0';
			freq_m += '0';
			freq_cent += '0';
			freq_dec += '0';


			uint8_t freq_string[] =  ("Freq Hz");
				LCD_nokia_clear();
				//Send voltage
				LCD_nokia_send_string(freq_string);
				LCD_nokia_goto_xy(0, 1);
				LCD_nokia_send_char(freq_cm);
				LCD_nokia_send_char(freq_dm);
				LCD_nokia_send_char(freq_m);
				LCD_nokia_send_char('.');
				LCD_nokia_send_char(freq_cent);
				LCD_nokia_send_char(freq_dec);
		}

		PIT_StartTimer(PIT, kPIT_Chnl_1);
		clear_ADC_flag();
		writeLED(RED, !BIT_OFF);

		writeLED(GREEN, !BIT_ON);
	}
    return 0 ;
}
double frequencyvalue()
{
	uint8_t flag_down = FALSE;
	uint16_t tmp_index = 0;
	double x = 0;
	tmp_index = VECTOR_SIZE-2;
	while(flag_down<2)
	{
		if(tmp_index>=1)
		{
			if(((vectorCorr[tmp_index] > vectorCorr[tmp_index-1]))&&(flag_down == 0))
			{
				flag_down++;
			}
			else if(((vectorCorr[tmp_index]<vectorCorr[tmp_index-1]))&&(flag_down == 1))
			{
				flag_down++;
			}
			tmp_index--;
		}
		else
		{
			return 0;
		}
	}
	x = (1/((400.0-(float)tmp_index)*0.000086956));
	return x;
}
