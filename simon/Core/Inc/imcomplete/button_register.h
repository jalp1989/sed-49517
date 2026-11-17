#ifndef BUTTON_REGISTER_H
#define BUTTON_REGISTER_H

#include <stdbool.h>
#include <stdint.h>
#include "project_types.h"

#define BUTTON_REGISTER_MAX_LENGTH 100

/**
 * @brief Inicializa el módulo ButtonRegister.
 */
void ButtonRegister_Init(void);

/**
 * @brief Reinicia el registro de colores del jugador.
 */
void ButtonRegister_Reset(void);

/**
 * @brief Almacena un color introducido por el jugador.
 *
 * @param color Color recibido desde Coordinator.
 * @return true si se almacena correctamente.
 *         false si el color no es válido o el registro está lleno.
 */
bool ButtonRegister_AddColor(SimonColor color);

/**
 * @brief Obtiene la cantidad de colores almacenados.
 *
 * @return Número de colores registrados.
 */
uint8_t ButtonRegister_GetLength(void);

/**
 * @brief Obtiene un color almacenado.
 *
 * @param position Posición del color.
 * @param color Puntero donde se guardará el color.
 * @return true si la operación es correcta.
 */
bool ButtonRegister_GetColor(uint8_t position, SimonColor *color);

#endif /* BUTTON_REGISTER_H */