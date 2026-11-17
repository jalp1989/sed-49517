#ifndef LIGHT_H
#define LIGHT_H

#include "project_types.h"

/**
 * @brief Inicializa el módulo Light.
 */
void Light_Init(void);

/**
 * @brief Lee el sensor LDR y actualiza el brillo.
 */
void Light_Update(void);

/**
 * @brief Obtiene el brillo calculado a partir de la LDR.
 *
 * @return Brillo expresado entre 0 y 100.
 */
Brightness Light_GetBrightness(void);

/**
 * @brief Gestiona la lectura del sensor mediante ADC.
 */
void Light_GetGPIO(void);

#endif /* LIGHT_H */