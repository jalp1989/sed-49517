/*
 * hardware.c
 *
 *  Created on: 4 nov 2026
 *      Author: JP
 */

#include "main.h"
#include "hardware.h"

// Periféricos definidos en main.c
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;

// Control del sonido
static uint8_t soundEnabled = 1;


// Inicializar módulo de hardware
void Hardware_Init(void)
{
    soundEnabled = 1;

    Buzzer_Off();
}


// Leer un canal ADC
uint32_t Hardware_Read_ADC(uint32_t channel)
{
    ADC_ChannelConfTypeDef config = {0};

    config.Channel = channel;
    config.Rank = 1;
    config.SamplingTime = ADC_SAMPLETIME_84CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &config);

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        uint32_t value = HAL_ADC_GetValue(&hadc1);

        HAL_ADC_Stop(&hadc1);

        return value;
    }

    HAL_ADC_Stop(&hadc1);

    return 0;
}


// Leer potenciómetro: ADC_CHANNEL_10
uint32_t Hardware_Read_Potentiometer(void)
{
    return Hardware_Read_ADC(ADC_CHANNEL_10);
}


// Leer LDR: ADC_CHANNEL_11
uint32_t Hardware_Read_LDR(void)
{
    return Hardware_Read_ADC(ADC_CHANNEL_11);
}


// Activar o desactivar el sonido
void Hardware_Set_Sound_Enabled(uint8_t enabled)
{
    soundEnabled = enabled;
}


// Encender buzzer mediante PWM
void Buzzer_On(void)
{
    if (soundEnabled)
    {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    }
}


// Apagar buzzer
void Buzzer_Off(void)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}
