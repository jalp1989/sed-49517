/*
 * sequence.c
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#include "sequence.h"
#include <stdlib.h>

// Almacenamiento privado de la secuencia
static uint8_t sequence[MAX_SEQUENCE];

// Inicializar la secuencia
void Sequence_Init(void)
{
    Sequence_Generate();
}

// Generar una secuencia aleatoria de colores
void Sequence_Generate(void)
{
    for (uint8_t i = 0; i < MAX_SEQUENCE; i++)
    {
        sequence[i] = rand() % 4;
    }
}

// Obtener un color de la secuencia
uint8_t Sequence_Get(uint8_t index)
{
    if (index < MAX_SEQUENCE)
    {
        return sequence[index];
    }

    return 0;
}
