/*
 * PIT.c
 *
 *  Created on: 3 may 2022
 *      Author: axel1
 */
#include "PIT.h"

static void (*PIT_0_callback)(void) = 0;
static void (*PIT_1_callback)(void) = 0;

boolean_t timer_status = FALSE;

void PIT0_IRQHandler(void)
{
	if(PIT_0_callback)
	{
		PIT_0_callback();
	}
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
}
void PIT1_IRQHandler(void)
{
	if(PIT_1_callback)
	{
		PIT_1_callback();
	}
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);
}
void PIT_callback_init(void *handler, PIT_chn_t PIT_chnl)
{
	if(PIT0 == PIT_chnl)
	{
		PIT_0_callback = handler;
	}
	else
	{
		PIT_1_callback = handler;
	}

}

void configureTimer(void)
{
	//Inicializamos el PIT canal 0 para el segundo de incialización

	pit_config_t pitConfig;
	PIT_Init(PIT, &pitConfig);
	// Definimos un periodo de 1 segundo

	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, MSEC_TO_COUNT(MSTOCOUNTINIT, PIT_SOURCE_CLOCK));
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	EnableIRQ(PIT0_IRQn);
	//PIT_StartTimer(PIT, kPIT_Chnl_0);

	//Para el ADC
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_1, 1000);
	PIT_EnableInterrupts(PIT, kPIT_Chnl_1, kPIT_TimerInterruptEnable);
	PIT_StartTimer(PIT, kPIT_Chnl_1);
	//EnableIRQ(PIT1_IRQn);
	//PIT_StartTimer(PIT, kPIT_Chnl_1);

}

void setFlagTimer (void)
{
	timer_status = TRUE;
}
void clearFlagTimer(void)
{
	timer_status = FALSE;
}

boolean_t readFlagTimer(void)
{
	return timer_status;
}

