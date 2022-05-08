/*
 * Correlacion.c
 *
 *  Created on: 5 may 2022
 *      Author: Oliver
 */
#include <Correlacion.h>
boolean_t flag_cor;
boolean_t flag_frec;

boolean_t readCorrelacionFlag(void)
{
	return flag_cor;
}

void setCorrelacionFlag(void)
{
	flag_cor = TRUE;
}

void clearCorrelacionFlag(void)
{
	flag_cor = FALSE;
}

boolean_t readFrecuenciaFlag(void)
{
	return flag_frec;
}

void clearFrecuenciaFlag(void)
{
	flag_frec = FALSE;
}

void setFrecuenciaFlag(void)
{
	flag_frec = TRUE;
}
