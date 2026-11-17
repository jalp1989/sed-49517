#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdbool.h>
#include <stdint.h>
#include "project_types.h"

#define SEQUENCE_MAX_LENGTH 100

/**
 * @brief Inicializa el módulo Sequence.
 *
 * Reinicia la secuencia almacenada y establece
 * su longitud a cero.
 */
void Sequence_Init(void);

/**
 * @brief Genera una nueva secuencia para una nueva partida.
 *
 * Inicializa la semilla del generador aleatorio,
 * reinicia la secuencia anterior y genera una nueva
 * secuencia de SEQUENCE_MAX_LENGTH colores.
 *
 * @return true si la secuencia se ha generado correctamente,
 *         false en caso contrario.
 */
bool Sequence_StartNewGame(void);

/**
 * @brief Reinicia la secuencia almacenada.
 *
 * Establece todos los colores a su valor inicial
 * y establece la longitud de la secuencia a cero.
 */
void Sequence_Reset(void);

/**
 * @brief Copia la secuencia completa en un array externo.
 *
 * Comprueba que el destino no sea NULL y que tenga
 * capacidad suficiente para almacenar la secuencia.
 *
 * @param destination Array donde se copiará la secuencia.
 * @param maxLength Capacidad máxima del array de destino.
 *
 * @return true si la copia se realiza correctamente,
 *         false si los parámetros no son válidos
 *         o el destino no tiene capacidad suficiente.
 */
bool Sequence_GetSequence(SimonColor *destination,
                          uint8_t maxLength);

/**
 * @brief Obtiene la longitud actual de la secuencia.
 *
 * @return Número de colores almacenados en la secuencia.
 */
uint8_t Sequence_GetLength(void);

/**
 * @brief Obtiene el color almacenado en una posición.
 *
 * Comprueba que la posición indicada se encuentre
 * dentro de los límites de la secuencia.
 *
 * @param position Posición del color que se desea obtener.
 *
 * @return Color correspondiente a la posición indicada.
 *         Si la posición no es válida, devuelve SIMON_COLOR_RED.
 */
SimonColor Sequence_GetColor(uint8_t position);

#endif /* SEQUENCE_H */