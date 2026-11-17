#ifndef SIMON_H
#define SIMON_H

#include <stdbool.h>
#include <stdint.h>
#include "project_types.h"


/**
 * @brief Inicializa el módulo Simon.
 *
 * Establece el estado inicial de la máquina de estados,
 * reinicia el nivel y el resultado de la comparación.
 */
void Simon_Init(void);


/**
 * @brief Inicia una nueva partida.
 *
 * Establece el nivel inicial (nivel 1) y prepara
 * la máquina de estados para mostrar la secuencia.
 */
void Simon_StartGame(void);


/**
 * @brief Obtiene el estado actual de Simon.
 *
 * @return Estado actual de la máquina de estados.
 */
SimonState Simon_GetState(void);


/**
 * @brief Obtiene el nivel actual de la partida.
 *
 * @return Nivel actual (1-100).
 */
uint8_t Simon_GetLevel(void);


/**
 * @brief Obtiene la cantidad de colores que debe
 * reproducir el jugador en el nivel actual.
 *
 * Coincide con el número del nivel.
 *
 * @return Número de colores de la ronda actual.
 */
uint8_t Simon_GetSequenceLength(void);


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
void Simon_SetComparisonResult(int8_t result);


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
void Simon_StateUpdater(bool changeState, SimonState targetState);


/**
 * @brief Gestiona el incremento y las transiciones
 * de la máquina de estados.
 *
 * Evalúa el estado actual y el resultado de la comparación
 * para determinar la siguiente transición.
 *
 * @param changeState Habilita o impide la transición.
 */
void Simon_StateIncreaser(bool changeState);


#endif /* SIMON_H */