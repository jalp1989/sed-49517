/*
 * buttons.h
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <stdint.h>

void Buttons_Init(void);

void Buttons_Set_Enabled(uint8_t enabled);

void Buttons_EXTI_Callback(uint16_t GPIO_Pin);

int8_t Buttons_Get_Pending(void);

void Buttons_Reset(void);


#endif /* INC_BUTTONS_H_ */
