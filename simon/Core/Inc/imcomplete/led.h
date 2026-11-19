
#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stdbool.h>
#include "project_types.h"

/**
 * @brief Inicializa el módulo LED.
 */
void LED_Init(void);

/**
 * @brief Configura el brillo de los LEDs.
 *
 * @param brightness Brillo expresado entre 0 y 100.
 */
void LED_SetBrightness(Brightness brightness);

/**
 * @brief Enciende el LED correspondiente al color indicado.
 *
 * @param color Color que se desea mostrar.
 */
void LED_ShowColor(SimonColor color);

/**
 * @brief Apaga todos los LEDs.
 */
void LED_AllOff(void);

/**
 * @brief Inicia la reproducción no bloqueante de una secuencia
 *        de colores.
 *
 * @param sequence Puntero a la secuencia de colores.
 * @param length Número de colores que contiene la secuencia.
 * @param onTimeMs Tiempo de encendido de cada color en milisegundos.
 * @param offTimeMs Tiempo de apagado entre colores en milisegundos.
 */
void LED_PlayColors(const SimonColor *sequence,
                    uint8_t length,
                    uint32_t onTimeMs,
                    uint32_t offTimeMs);

/**
 * @brief Actualiza la reproducción de la secuencia de LEDs.
 *
 * Gestiona los estados internos de reproducción y controla
 * los tiempos de encendido y apagado sin bloquear la ejecución.
 */
void LED_Update(void);

/**
 * @brief Consulta si el módulo LED está reproduciendo una secuencia.
 *
 * @return true si está reproduciendo, false en caso contrario.
 */
bool LED_GetPlaying(void);

/**
 * @brief Consulta si la reproducción de la secuencia ha finalizado.
 *
 * @return true si la reproducción ha terminado, false en caso contrario.
 */
bool LED_GetPlayed(void);

/**
 * @brief Modifica el indicador de reproducción finalizada.
 *
 * @param state Nuevo estado del indicador.
 */
void LED_SetPlayed(bool state);

/**
 * @brief Gestiona las salidas GPIO/PWM de los LEDs.
 */
void LED_GPIO(void);

#endif /* LED_H */
