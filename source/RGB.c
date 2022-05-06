/*
 * RGB.c
 *
 *  Created on: 6 may 2022
 *      Author: Oliver
 */
#include "RGB.h"

void configRGB(void)
{
	BOARD_InitLEDsPins();
}

void writeLED(Led_color_t color, boolean_t state)
{
	if(RED == color)
	{
		GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, state);
	}
	else if(BLUE == color)
	{
		GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, state);
	}
	else if(GREEN == color)
	{
		GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, state);
	}
	else
	{

	}
}

