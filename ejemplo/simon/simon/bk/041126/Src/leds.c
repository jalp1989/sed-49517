/*
 * leds.c
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#include "main.h"
#include "leds.h"

// Puerto GPIO de cada LED
static GPIO_TypeDef * const ledPorts[NUM_COLORS] =
{
    GPIOD,  // ROJO
    GPIOD,  // VERDE
    GPIOD,  // AZUL
    GPIOD   // NARANJA
};

// Pin de cada LED
static const uint16_t ledPins[NUM_COLORS] =
{
    GPIO_PIN_14,  // ROJO
    GPIO_PIN_12,  // VERDE
    GPIO_PIN_15,  // AZUL
    GPIO_PIN_13   // NARANJA
};

// Inicializar LEDs
void LEDs_Init(void)
{
    LEDs_Off();
}

// Apagar todos los LEDs
void LEDs_Off(void)
{
    for (uint8_t i = 0; i < NUM_COLORS; i++)
    {
        HAL_GPIO_WritePin(
            ledPorts[i],
            ledPins[i],
            GPIO_PIN_RESET
        );
    }
}

// Encender un LED según su índice
void LED_On(uint8_t color)
{
    LEDs_Off();

    if (color < NUM_COLORS)
    {
        HAL_GPIO_WritePin(
            ledPorts[color],
            ledPins[color],
            GPIO_PIN_SET
        );
    }
}
