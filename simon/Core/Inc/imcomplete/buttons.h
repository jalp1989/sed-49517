#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>
#include "project_types.h"

/**
 * @brief Inicializa el módulo Buttons.
 */
void Buttons_Init(void);

/**
 * @brief Configura el modo de funcionamiento de los botones.
 */
void Buttons_SelectMode(void);

/**
 * @brief Comprueba si se ha pulsado algún botón.
 *
 * @param color Puntero donde se almacenará el color detectado.
 * @return true si se ha detectado una pulsación válida.
 */
bool Buttons_IsPressed(SimonColor *color);

/**
 * @brief Obtiene el estado de las entradas GPIO.
 */
void Buttons_GetGPIO(void);

/**
 * @brief Procesa una interrupción externa de un botón.
 *
 * @param GPIO_Pin Pin que ha generado la interrupción.
 */
void Buttons_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* BUTTONS_H */