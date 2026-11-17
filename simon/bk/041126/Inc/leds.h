/*
 * leds.h
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#ifndef INC_LEDS_H_
#define INC_LEDS_H_

#include <stdint.h>

#define NUM_COLORS 4

#define ROJO    0
#define VERDE   1
#define AZUL    2
#define NARANJA 3

void LEDs_Init(void);
void LEDs_Off(void);
void LED_On(uint8_t color);


#endif /* INC_LEDS_H_ */
