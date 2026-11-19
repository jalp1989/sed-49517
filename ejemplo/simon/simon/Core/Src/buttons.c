/*
 * buttons.c
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#include "main.h"
#include "buttons.h"

// Número de pulsadores
#define NUM_BUTTONS 4

// Tiempo antirrebote
#define DEBOUNCE_TIME 50

// Puerto GPIO de cada pulsador
static GPIO_TypeDef * const buttonPorts[NUM_BUTTONS] =
{
    GPIOB,  // ROJO
    GPIOB,  // VERDE
    GPIOB,  // AZUL
    GPIOB   // NARANJA
};

// Pin de cada pulsador
static const uint16_t buttonPins[NUM_BUTTONS] =
{
    GPIO_PIN_0,  // ROJO
    GPIO_PIN_1,  // VERDE
    GPIO_PIN_2,  // AZUL
    GPIO_PIN_5   // NARANJA
};

// Variables privadas del módulo
static volatile int8_t pendingButton = -1;

static volatile uint32_t lastPressTime = 0;

static volatile uint8_t buttonsEnabled = 0;


// Inicializar módulo de pulsadores
void Buttons_Init(void)
{
    Buttons_Reset();

    buttonsEnabled = 0;
}


// Habilitar o deshabilitar la recepción de pulsaciones
void Buttons_Set_Enabled(uint8_t enabled)
{
    buttonsEnabled = enabled;
}


// Reiniciar las variables de pulsadores
void Buttons_Reset(void)
{
    pendingButton = -1;
    lastPressTime = 0;
}


// Obtener el botón pendiente
int8_t Buttons_Get_Pending(void)
{
    int8_t button = pendingButton;

    pendingButton = -1;

    return button;
}


// Callback de interrupciones EXTI
void Buttons_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    // Solo aceptar pulsaciones cuando el juego espera al jugador
    if (!buttonsEnabled)
    {
        return;
    }

    // Evitar almacenar otra pulsación si ya existe una pendiente
    if (pendingButton >= 0)
    {
        return;
    }

    // Identificar el pulsador
    for (uint8_t i = 0; i < NUM_BUTTONS; i++)
    {
        if (GPIO_Pin == buttonPins[i])
        {
            // Antirrebote de 50 ms
            if ((now - lastPressTime) < DEBOUNCE_TIME)
            {
                return;
            }

            lastPressTime = now;

            // Guardar índice lógico del color
            pendingButton = (int8_t)i;

            break;
        }
    }
}
