/*
 * ADC.h
 *
 *  Created on: 4 may 2022
 *      Author: axel1
 */

#ifndef ADC_H_
#define ADC_H_

#include "fsl_adc16.h"
#include "fsl_port.h"
#include "Bits.h"


void Configure_ADC(void);

uint32_t ADC_Read(void);

boolean_t read_ADC_flag(void);
uint32_t getValueADC(void);
void set_ADC_flag(void);
void clear_ADC_flag(void);

boolean_t read_flag_save_adc(void);
void clear_flag_save_adc(void);

#define MIN_ADC_VALUE 2800
#define CONVERSION 3.3/4095

#endif /* ADC_H_ */
