/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN PV */
//process variables = variables globales
// Estados del juego
typedef enum {
    GAME_SHOW,
    GAME_INPUT,
    GAME_WIN,
    GAME_LOSE
} GameState;

volatile GameState gameState = GAME_SHOW;

// Secuencia de colores
#define MAX_SEQUENCE 100

uint8_t sequence[MAX_SEQUENCE];

uint8_t level = 1;
uint8_t showIndex = 0;
uint8_t inputIndex = 0;

// Temporización
uint32_t nextTime = 0;
uint32_t lastPressTime = 0;

uint32_t ledTime = 400;
uint32_t pauseTime = 200;

// Control de reproducción
uint8_t ledIsOn = 0;

// Botón pulsado desde interrupción
volatile int8_t pendingButton = -1;

// Variables ADC
uint32_t potValue = 0;
uint32_t ldrValue = 0;

// Control del buzzer
uint8_t soundEnabled = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Pines de los cuatro LEDs
GPIO_TypeDef* ledPorts[4] = {
    GPIOA, GPIOA, GPIOA, GPIOA
};

uint16_t ledPins[4] = {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3
};

// Apagar todos los LEDs
void LEDs_Off(void)
{
    for(int i = 0; i < 4; i++)
    {
        HAL_GPIO_WritePin(
            ledPorts[i],
            ledPins[i],
            GPIO_PIN_RESET
        );
    }
}

// Encender un LED
void LED_On(uint8_t color)
{
    LEDs_Off();

    if(color < 4)
    {
        HAL_GPIO_WritePin(
            ledPorts[color],
            ledPins[color],
            GPIO_PIN_SET
        );
    }
}

// Leer un canal ADC
uint32_t Read_ADC(uint32_t channel)
{
    ADC_ChannelConfTypeDef config = {0};

    config.Channel = channel;
    config.Rank = 1;//solo se ejecuta 1 a la vez
    config.SamplingTime = ADC_SAMPLETIME_84CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &config);//cargamos la configuracion

    HAL_ADC_Start(&hadc1); //empezar a tomar valores

    if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) //conversion exitosa dentro de 10ms
    {
        uint32_t value = HAL_ADC_GetValue(&hadc1); //guarda el valor digital de la conversion realizada

        HAL_ADC_Stop(&hadc1); //detiene la conversion

        return value;
    }

    HAL_ADC_Stop(&hadc1); // sino es exitosa lo va parar tambien y devuelve un cero sin embargo quiza cuando haya error habra que meter una excepcion

    return 0;
}

// Sonido del buzzer
void Buzzer_On(void)
{
    if(soundEnabled)
    {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    }
}

void Buzzer_Off(void)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}

// Generar una secuencia aleatoria
void Generate_Sequence(void)
{
    for(uint8_t i = 0; i < MAX_SEQUENCE; i++)
    {
        sequence[i] = rand() % 4;
    }
}

// Iniciar un nivel
// Inicializacion de las variables del juego => CAMBIO DE ESTADO A "GAME_SHOW"
void Start_Level(void)
{
    potValue = Read_ADC(ADC_CHANNEL_10);
    ldrValue = Read_ADC(ADC_CHANNEL_11);

    // El potenciómetro regula la velocidad
    ledTime = 200 + ((4095 - potValue) * 500) / 4095;

    pauseTime = ledTime / 2;

    // En oscuridad desactivamos los sonidos
    soundEnabled = (ldrValue > 1500);

    showIndex = 0; //indice del vector sequence[] que contiene los colores
    inputIndex = 0;

    ledIsOn = 0;

    LEDs_Off();

    gameState = GAME_SHOW;

    nextTime = HAL_GetTick() + 500; //inicializacion del turno
}

// Finalizar partida => CAMBIO DE ESTADO A "GAME_LOSE"
void Game_Over(void)
{
    LEDs_Off();

    Buzzer_On();

    gameState = GAME_LOSE; //cambia estado

    nextTime = HAL_GetTick() + 1000;//actualiza tiempo
}

// Interrupciones de botones
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    if(now - lastPressTime < 150)
        return;

    lastPressTime = now;

    if(gameState != GAME_INPUT)
        return;

    if(GPIO_Pin == GPIO_PIN_0)
        pendingButton = 0;

    else if(GPIO_Pin == GPIO_PIN_1)
        pendingButton = 1;

    else if(GPIO_Pin == GPIO_PIN_2)
        pendingButton = 2;

    else if(GPIO_Pin == GPIO_PIN_3)
        pendingButton = 3;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  srand(Read_ADC(ADC_CHANNEL_10) ^ HAL_GetTick());//generador de semillas nuevo para producir nuevas secuencias

  LEDs_Off();

  Buzzer_Off();

  Generate_Sequence();//generador del vector de secuencias con colores al azar representados por numero 0,1,2,3

  Start_Level();// inicializacion del juego
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  uint32_t now = HAL_GetTick(); //coger el tiempo actual

	  switch(gameState)
	  {
	      // REPRODUCIR SECUENCIA
	      case GAME_SHOW:

	          if(now >= nextTime)
	          {
	              if(showIndex < level)//muestra colores, gradualmente, siempre que aciertes level se incrementara y habilitara mas
	              {
	                  if(!ledIsOn)//enciendo el led indicado por showindex
	                  {
	                      LED_On(sequence[showIndex]);

	                      Buzzer_On();

	                      ledIsOn = 1;

	                      nextTime = now + ledTime; //actualizo el tiempo durante el cual el led ilumina
	                  }
	                  else
	                  {
	                      LEDs_Off();

	                      Buzzer_Off();

	                      ledIsOn = 0;

	                      showIndex++; //actualizo indice

	                      nextTime = now + pauseTime; //actualizo el tiempo de pausa entre colores
	                  }
	              }
	              else //al asertar la secuencia previa pasamos a estado game-input donde buscamos los pulsadores
	              {
	                  LEDs_Off();

	                  Buzzer_Off();

	                  gameState = GAME_INPUT; //=> CAMBIO DE ESTADO A " GAME_INPUT"
	              }
	          }

	          break;


	      // ESPERAR RESPUESTA DEL JUGADOR
	      case GAME_INPUT:

	          if(pendingButton >= 0)
	          {
	              uint8_t button = pendingButton;

	              pendingButton = -1;

	              if(button == sequence[inputIndex])
	              {
	                  LED_On(button);

	                  Buzzer_On();

	                  nextTime = now + 150;

	                  inputIndex++;

	                  if(inputIndex >= level)
	                  {
	                      gameState = GAME_WIN;//=> CAMBIO DE ESTADO A "GAME_WIN"
	                  }
	              }
	              else
	              {
	                  Game_Over();//=> CAMBIO DE ESTADO A "GAME_LOSE"
	              }
	          }

	          // Apagar LED después de confirmar
	          if(ledIsOn && now >= nextTime)
	          {
	              LEDs_Off();

	              Buzzer_Off();

	              ledIsOn = 0;
	          }

	          break;


	      // NIVEL SUPERADO
	      case GAME_WIN:

	          LEDs_Off();

	          Buzzer_Off();

	          level++;

	          //incrementa nivel cuando ganas
	          if(level > MAX_SEQUENCE)
	              level = 1;
	          //para mostrar toda la secuencia desde el incio necesito hacer una inicializacion del juego
	          Start_Level();//=> CAMBIO DE ESTADO A "GAME_SHOWN"

	          break;


	      // PARTIDA PERDIDA
	      case GAME_LOSE:

	          if(now >= nextTime)
	          {
	              Buzzer_Off();

	              level = 1;

	              Generate_Sequence();//OJO si pierdo genero una secuencia nueva para que no se repita la anterior

	              Start_Level();//=> CAMBIO DE ESTADO A "GAME_SHOWN"
	          }

	          break;
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_verde_Pin|LED_naranja_Pin|LED_rojo_Pin|LED_azul_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : reserva_Pin */
  GPIO_InitStruct.Pin = reserva_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(reserva_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Boton_rojo_Pin Boton_verde_Pin boton_azul_Pin Boton_naranja_Pin */
  GPIO_InitStruct.Pin = Boton_rojo_Pin|Boton_verde_Pin|boton_azul_Pin|Boton_naranja_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_verde_Pin LED_naranja_Pin LED_rojo_Pin LED_azul_Pin */
  GPIO_InitStruct.Pin = LED_verde_Pin|LED_naranja_Pin|LED_rojo_Pin|LED_azul_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : Bocina_Pin */
  GPIO_InitStruct.Pin = Bocina_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
  HAL_GPIO_Init(Bocina_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
