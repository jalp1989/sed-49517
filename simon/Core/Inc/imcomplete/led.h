#ifndef LED_H
#define LED_H

#include <stdint.h>
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
 * @brief Gestiona las salidas GPIO/PWM de los LEDs.
 */
void LED_GPIO(void);

#endif /* LED_H */