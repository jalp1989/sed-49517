/*
 * hardware.h
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#ifndef INC_HARDWARE_H_
#define INC_HARDWARE_H_

#include <stdint.h>

void Hardware_Init(void);

uint32_t Hardware_Read_ADC(uint32_t channel);

uint32_t Hardware_Read_Potentiometer(void);
uint32_t Hardware_Read_LDR(void);

void Hardware_Set_Sound_Enabled(uint8_t enabled);

void Buzzer_On(void);
void Buzzer_Off(void);

#endif /* INC_HARDWARE_H_ */
