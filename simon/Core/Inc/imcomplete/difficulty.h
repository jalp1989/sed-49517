#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <stdint.h>
#include "project_types.h"

/**
 * @brief Inicializa el módulo Difficulty.
 */
void Difficulty_Init(void);

/**
 * @brief Lee el potenciómetro y selecciona la dificultad.
 */
void Difficulty_SelectDifficulty(void);

/**
 * @brief Obtiene la dificultad seleccionada.
 *
 * @return Valor de dificultad.
 */
uint8_t Difficulty_GetDifficulty(void);

/**
 * @brief Obtiene los tiempos de encendido y apagado
 * correspondientes a la dificultad seleccionada.
 *
 * @param timing Estructura donde se guardarán los tiempos.
 */
void Difficulty_GetTiming(SimonTiming *timing);

#endif /* DIFFICULTY_H */