/*
 * sequence.h
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#ifndef INC_SEQUENCE_H_
#define INC_SEQUENCE_H_

#include <stdint.h>

#define MAX_SEQUENCE 100

void Sequence_Init(void);
void Sequence_Generate(void);
uint8_t Sequence_Get(uint8_t index);

#endif /* INC_SEQUENCE_H_ */
