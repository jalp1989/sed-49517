#include "simon.h"

/* Nivel máximo de la partida */
#define SIMON_MAX_LEVEL 100

/* Variables internas del módulo */
static SimonState currentState;
static uint8_t currentLevel;
static int8_t resultadoComparacion;


/**
 * @brief Inicializa el módulo Simon.
 *
 * Establece el estado inicial de la máquina de estados,
 * reinicia el nivel y el resultado de la comparación.
 */
void Simon_Init(void)
{
    currentState = SIMON_STATE_IDLE;
    currentLevel = 0;
    resultadoComparacion = 0;
}


/**
 * @brief Inicia una nueva partida.
 *
 * Establece el nivel inicial (nivel 1) y prepara
 * la máquina de estados para mostrar la secuencia.
 */
void Simon_StartGame(void)
{
    currentLevel = 1;
    resultadoComparacion = 0;

    //Simon_StateUpdater(true, SIMON_STATE_SHOWING_SEQUENCE);
}


/**
 * @brief Obtiene el estado actual de Simon.
 *
 * @return Estado actual de la máquina de estados.
 */
SimonState Simon_GetState(void)
{
    return currentState;
}


/**
 * @brief Obtiene el nivel actual de la partida.
 *
 * @return Nivel actual (1-100).
 */
uint8_t Simon_GetLevel(void)
{
    return currentLevel;
}


/**
 * @brief Obtiene la cantidad de colores que debe
 * reproducir el jugador en el nivel actual.
 *
 * Coincide con el número del nivel.
 *
 * @return Número de colores de la ronda actual.
 */
uint8_t Simon_GetSequenceLength(void)
{
    return currentLevel;
}


/**
 * @brief Almacena el resultado de la comparación.
 *
 * Guarda el resultado comunicado por Coordinator.
 *
 * Valores:
 * -1: comparación incorrecta (NOK).
 *  0: sin resultado.
 *  1: comparación correcta (OK).
 *
 * @param result Resultado de la comparación.
 */
void Simon_SetComparisonResult(int8_t result)
{
    if ((result >= -1) && (result <= 1))
    {
        resultadoComparacion = result;
    }
}


/**
 * @brief Actualiza el estado de la máquina de estados.
 *
 * Si changeState es true, cambia el estado actual
 * al estado indicado por targetState.
 *
 * Si changeState es false, mantiene el estado actual.
 *
 * @param changeState Indica si se debe cambiar de estado.
 * @param targetState Estado de destino.
 */
void Simon_StateUpdater(bool changeState, SimonState targetState)
{
    if (changeState == true)
    {
        currentState = targetState;
    }
}


/**
 * @brief Gestiona las transiciones de la máquina de estados
 * y el incremento del nivel.
 *
 * Evalúa el estado actual y las condiciones del juego
 * para determinar la siguiente transición.
 *
 * Transiciones:
 *
 * IDLE -> SHOWING_SEQUENCE.
 * SHOWING_SEQUENCE -> WAITING_INPUT.
 * ROUND_COMPLETED -> GAME_OVER si el resultado es -1.
 * ROUND_COMPLETED -> GAME_WON si el resultado es 1.
 * GAME_WON -> SHOWING_SEQUENCE si el nivel es inferior a 100.
 * GAME_WON -> IDLE si se ha completado el nivel 100.
 *
 * @param changeState Habilita o impide las transiciones.
 */
void Simon_StateIncreaser(bool changeState)
{
    if (changeState == false)
    {
        return;
    }

    /* Estado IDLE */
    if (currentState == SIMON_STATE_IDLE)
    {
        //if (currentLevel == 0)
        //{
        //    return;
        //}
    //currentLevel = 1;
    //resultadoComparacion = 0;
        Simon_StateUpdater(true, SIMON_STATE_SHOWING_SEQUENCE);
    }

    /* Estado SHOWING_SEQUENCE */
    else if (currentState == SIMON_STATE_SHOWING_SEQUENCE)
    {
        Simon_StateUpdater(true, SIMON_STATE_WAITING_INPUT);
    }

    /* Estado WAITING_INPUT */
    else if (currentState == SIMON_STATE_WAITING_INPUT)
    {
        /* Coordinator cambiará a ROUND_COMPLETED
         * cuando el jugador haya introducido todos
         * los colores correspondientes al nivel.
         */
         Simon_StateUpdater(true, SIMON_STATE_ROUND_COMPLETED);
    }

    /* Estado ROUND_COMPLETED */
    else if (currentState == SIMON_STATE_ROUND_COMPLETED)
    {
        if (resultadoComparacion == -1)
        {
            Simon_StateUpdater(true, SIMON_STATE_GAME_OVER);
        }
        else if (resultadoComparacion == 1)
        {
            Simon_StateUpdater(true, SIMON_STATE_GAME_WON);
        }
    }

    /* Estado GAME_WON */
    else if (currentState == SIMON_STATE_GAME_WON)
    {
        if (currentLevel < SIMON_MAX_LEVEL)
        {
            currentLevel++;
            resultadoComparacion = 0;

            Simon_StateUpdater(true, SIMON_STATE_SHOWING_SEQUENCE);
        }
        else
        {
            currentLevel = 0;
            resultadoComparacion = 0;

            Simon_StateUpdater(true, SIMON_STATE_IDLE);
        }
    }

    /* Estado GAME_OVER */
    else if (currentState == SIMON_STATE_GAME_OVER)
    {
        /* Estado terminal.
         * Coordinator gestionará una nueva partida.
         */
         currentLevel = 0;
        resultadoComparacion = 0;

        Simon_StateUpdater(true, SIMON_STATE_IDLE);
        //Simon_StartGame();
    }
}