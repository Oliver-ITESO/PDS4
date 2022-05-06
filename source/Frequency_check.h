/*
 * Frequency_check.h
 *
 *  Created on: 22 abr 2022
 *      Author: axel1
 */

#ifndef FREQUENCY_CHECK_H_
#define FREQUENCY_CHECK_H_

#include "fsl_ftm.h"
#include "fsl_port.h"
#define FTMTOUSE FTM2
#define FILTERVALUE 0
#define FTM0CH1PIN 18
#define TIMERVALUE 0xFFFF
#define MAXFREQ 10000
#define MINFREQ 1000
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

#endif /* FREQUENCY_CHECK_H_ */


void init_FTM_inputcapture(void);
uint16_t frequencyvalue();
