/*
 * RGH.h
 *
 *  Created on: 6 may 2022
 *      Author: Oliver
 */

#ifndef RGB_H_
#define RGB_H_

#include "pin_mux.h"
#include "board.h"
#include "fsl_gpio.h"
#include "Bits.h"

typedef enum LEDCOLOR
{
	RED,
	GREEN,
	BLUE

} Led_color_t;

void configRGB(void);
void writeLED(Led_color_t color, boolean_t state);



#endif /* RGB_H_ */
