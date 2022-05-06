/*
 * Frequency_check.c
 *
 *  Created on: 22 abr 2022
 *      Author: axel1
 */

#include "Frequency_check.h"
#include "fsl_ftm.h"
#include <stdbool.h>
#include <stdint.h>
uint16_t g_frequency = 0;
void FTM2_IRQHandler(void)
{
	static uint16_t captureVal = 0;
	static uint16_t prevValue = 0;
	static uint8_t cnt = 0;
	static float freq = 0;
	if ((FTM_GetStatusFlags(FTMTOUSE) & kFTM_Chnl0Flag) == kFTM_Chnl0Flag)
	    {
	        /* Clear interrupt flag.*/
	        FTM_ClearStatusFlags(FTMTOUSE, kFTM_Chnl0Flag);
	    }
	prevValue = captureVal;
	captureVal = FTM_GetInputCaptureValue(FTMTOUSE, kFTM_Chnl_0);
	cnt++;
	if(cnt == 2)
	{
		if (captureVal<prevValue)
		{
			freq = 1.0/((float)((0xFFFF+captureVal)-prevValue) / (float)(FTM_SOURCE_CLOCK/2));
		}
		else
		{
			freq = 1.0/((float)(captureVal-prevValue) / (float)(FTM_SOURCE_CLOCK/2));
		}
		if(MAXFREQ<freq)
		{
			g_frequency = MAXFREQ;
		}
		else if(MINFREQ>freq)
		{
			g_frequency = MINFREQ;
		}
		else
		{
			g_frequency = freq;
		}
		cnt = 0;
	}

	__DSB();
}
uint16_t frequencyvalue(void)
{
	return g_frequency;
}
void init_FTM_inputcapture(void)
{
	CLOCK_EnableClock(kCLOCK_PortB);
	PORT_SetPinMux(PORTB, FTM0CH1PIN, kPORT_MuxAlt3);
	ftm_config_t InputConfig;
	FTM_GetDefaultConfig(&InputConfig);
	InputConfig.prescale = kFTM_Prescale_Divide_1;
	FTM_Init(FTMTOUSE, &InputConfig);
	FTM_SetupInputCapture(FTMTOUSE, kFTM_Chnl_0, kFTM_RiseAndFallEdge, FILTERVALUE);

	FTM_SetTimerPeriod(FTMTOUSE, TIMERVALUE);

	FTM_EnableInterrupts(FTMTOUSE, kFTM_Chnl0InterruptEnable);
	EnableIRQ(FTM2_IRQn);

	FTM_StartTimer(FTMTOUSE, kFTM_SystemClock);
}
