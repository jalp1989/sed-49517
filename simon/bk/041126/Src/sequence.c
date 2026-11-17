/*
 * sequence.c
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#include "sequence.h"
#include <stdlib.h>

static uint8_t sequence[MAX_SEQUENCE];

void Sequence_Init(void)
{
    Sequence_Generate();
}

void Sequence_Generate(void)
{
    for (uint8_t i = 0; i < MAX_SEQUENCE; i++)
    {
        sequence[i] = rand() % 4;
    }
}

uint8_t Sequence_Get(uint8_t index)
{
    if (index < MAX_SEQUENCE)
    {
        return sequence[index];
    }

    return 0;
}
