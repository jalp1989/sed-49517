
#ifndef PROJECT_TYPES_H
#define PROJECT_TYPES_H

#include <stdint.h>

/* Colores disponibles en el juego */
typedef enum
{
    SIMON_COLOR_RED = 0,
    SIMON_COLOR_GREEN =1,
    SIMON_COLOR_BLUE =2,
    SIMON_COLOR_YELLOW =3,
} SimonColor;


/* Estados posibles de la partida */
typedef enum
{
    SIMON_STATE_IDLE = 0,
    SIMON_STATE_SHOWING_SEQUENCE,
    SIMON_STATE_WAITING_INPUT,
    SIMON_STATE_ROUND_COMPLETED,
    SIMON_STATE_GAME_OVER,
    SIMON_STATE_GAME_WON,
} SimonState;


/* Resultado de una pulsación del jugador */
typedef enum
{
    SIMON_RESULT_CORRECT = 0,
    SIMON_RESULT_ROUND_COMPLETED,
    SIMON_RESULT_INCORRECT
} SimonResult;


/* Tiempos utilizados para mostrar la secuencia */
typedef struct
{
    uint32_t onTimeMs;
    uint32_t offTimeMs;
} SimonTiming;


/* Brillo de los LED: rango de 0 a 100 % */
typedef uint8_t Brightness;

#endif /* PROJECT_TYPES_H */
