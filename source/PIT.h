/*
 * PIT.h
 *
 *  Created on: 3 may 2022
 *      Author: axel1
 */

#ifndef PIT_H_
#define PIT_H_
#include "fsl_pit.h"
#include "Bits.h"

#define MSTOCOUNTINIT 34

#define ADC_MS 1
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

typedef enum PITCHANNEL
{
	PIT0,
	PIT1

} PIT_chn_t;

void PIT_callback_init(void *handler, PIT_chn_t PIT_chnl);

void configureTimer(void);

void setFlagTimer(void);

void clearFlagTimer(void);

boolean_t readFlagTimer(void);

#endif /* PIT_H_ */
