
#include "sequence.h"
#include "main.h"
#include <stdlib.h>

#include <stddef.h>

/* Almacenamiento privado de la secuencia */
static SimonColor colors[SEQUENCE_MAX_LENGTH];
static uint8_t length = 0;

/* Contador para variar la semilla entre partidas */
static uint32_t gameCounter = 0;


/* Inicializa el generador pseudoaleatorio */
static void initializeRandomSeed(void)
{
    uint32_t seed;

    gameCounter++;

    seed = HAL_GetTick() ^ (gameCounter * 2654435761U);

    srand((unsigned int)seed);
}


/* Genera un color aleatorio */
static SimonColor generateRandomColor(void)
{
    return (SimonColor)(rand() % 4);
}


/* Genera los 100 colores */
static void generateSequence(void)
{
    uint8_t i;

    for (i = 0; i < SEQUENCE_MAX_LENGTH; i++)
    {
        colors[i] = generateRandomColor();
    }

    length = SEQUENCE_MAX_LENGTH;
}


/* Inicializa el módulo */
void Sequence_Init(void)
{
    Sequence_Reset();
}


/* Inicia una nueva partida y genera otra secuencia */
bool Sequence_StartNewGame(void)
{
    initializeRandomSeed();

    Sequence_Reset();

    generateSequence();

    return (length == SEQUENCE_MAX_LENGTH);
}


/* Reinicia la secuencia */
void Sequence_Reset(void)
{
    uint8_t i;

    for (i = 0; i < SEQUENCE_MAX_LENGTH; i++)
    {
        colors[i] = SIMON_COLOR_RED;
    }

    length = 0;
}


/* Copia la secuencia completa */
bool Sequence_GetSequence(SimonColor *destination,
                          uint8_t maxLength)
{
    uint8_t i;

    if (destination == NULL)
    {
        return false;
    }

    if (maxLength < length)
    {
        return false;
    }

    for (i = 0; i < length; i++)
    {
        destination[i] = colors[i];
    }

    return true;
}


/* Devuelve la longitud actual */
uint8_t Sequence_GetLength(void)
{
    return length;
}


/* Devuelve un color de la secuencia */
SimonColor Sequence_GetColor(uint8_t position)
{
    if (position >= length)
    {
        return SIMON_COLOR_RED;
    }

    return colors[position];
}
