
#include "led.h"
#include "main.h"

/* Variables internas del módulo LED */

/* Estado de reproducción */
typedef enum
{
    LED_IDLE,
    LED_ON,
    LED_OFF,
    LED_FINISHED

} LEDState;

/* Variables de control de reproducción */
static LEDState currentState = LED_IDLE;

static const SimonColor *ledSequence = NULL;

static uint8_t sequenceLength = 0;
static uint8_t currentIndex = 0;

static uint32_t previousTime = 0;

static uint32_t onTime = 0;
static uint32_t offTime = 0;

/* Indicadores de reproducción */
static bool playing = false;
static bool played = false;

/* Variables de control hardware */
static Brightness ledBrightness = 100;

static SimonColor currentColor;
static bool colorActive = false;


/* Funciones privadas */
static uint32_t LED_GetDutyCycle(void);
static void LED_SetColorPWM(SimonColor color);


/**
 * @brief Inicializa el módulo LED.
 */
void LED_Init(void)
{
    ledBrightness = 100;

    playing = false;
    played = false;

    currentState = LED_IDLE;

    ledSequence = NULL;
    sequenceLength = 0;
    currentIndex = 0;

    colorActive = false;

    /* Inicializar los cuatro canales PWM de TIM4 */

    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

    LED_AllOff();
}


/**
 * @brief Configura el brillo de los LEDs.
 *
 * @param brightness Brillo expresado entre 0 y 100.
 */
void LED_SetBrightness(Brightness brightness)
{
    if (brightness > 100)
    {
        brightness = 100;
    }

    ledBrightness = brightness;

    LED_GPIO();
}


/**
 * @brief Enciende el LED correspondiente al color indicado.
 *
 * @param color Color que se desea mostrar.
 */
void LED_ShowColor(SimonColor color)
{
    switch (color)
    {
        case SIMON_COLOR_RED:
        case SIMON_COLOR_GREEN:
        case SIMON_COLOR_BLUE:
        case SIMON_COLOR_YELLOW:

            currentColor = color;
            colorActive = true;

            LED_GPIO();

            break;

        default:
            LED_AllOff();
            break;
    }
}


/**
 * @brief Apaga todos los LEDs.
 */
void LED_AllOff(void)
{
    colorActive = false;

    LED_GPIO();
}


/**
 * @brief Inicia la reproducción no bloqueante de una secuencia.
 *
 * @param sequence Puntero a la secuencia de colores.
 * @param length Número de colores que contiene la secuencia.
 * @param onTimeMs Tiempo de encendido en milisegundos.
 * @param offTimeMs Tiempo de apagado en milisegundos.
 */
void LED_PlayColors(const SimonColor *sequence,
                    uint8_t length,
                    uint32_t onTimeMs,
                    uint32_t offTimeMs)
{
    /* Comprobar parámetros y evitar iniciar otra reproducción */
    if (sequence == NULL || length == 0 || playing)
    {
        return;
    }

    ledSequence = sequence;

    sequenceLength = length;
    currentIndex = 0;

    onTime = onTimeMs;
    offTime = offTimeMs;

    previousTime = HAL_GetTick();

    playing = true;
    played = false;

    currentState = LED_ON;

    /* Mostrar el primer color */
    LED_ShowColor(ledSequence[currentIndex]);
}


/**
 * @brief Actualiza la reproducción de la secuencia de LEDs.
 *
 * Gestiona los estados internos de reproducción y controla
 * los tiempos de encendido y apagado sin bloquear la ejecución.
 */
void LED_Update(void)
{
    uint32_t currentTime = HAL_GetTick();

    if (!playing)
    {
        return;
    }

    switch (currentState)
    {
        case LED_ON:

            if ((currentTime - previousTime) >= onTime)
            {
                LED_AllOff();

                previousTime = currentTime;

                currentState = LED_OFF;
            }

            break;


        case LED_OFF:

            if ((currentTime - previousTime) >= offTime)
            {
                currentIndex++;

                previousTime = currentTime;

                if (currentIndex < sequenceLength)
                {
                    LED_ShowColor(ledSequence[currentIndex]);

                    currentState = LED_ON;
                }
                else
                {
                    currentState = LED_FINISHED;
                }
            }

            break;


        case LED_FINISHED:

            playing = false;
            played = true;

            currentState = LED_IDLE;

            ledSequence = NULL;
            sequenceLength = 0;
            currentIndex = 0;

            break;


        case LED_IDLE:

        default:

            break;
    }
}


/**
 * @brief Consulta si el módulo LED está reproduciendo una secuencia.
 *
 * @return true si está reproduciendo, false en caso contrario.
 */
bool LED_GetPlaying(void)
{
    return playing;
}


/**
 * @brief Consulta si la reproducción de la secuencia ha finalizado.
 *
 * @return true si la reproducción ha terminado, false en caso contrario.
 */
bool LED_GetPlayed(void)
{
    return played;
}


/**
 * @brief Modifica el indicador de reproducción finalizada.
 *
 * @param state Nuevo estado del indicador.
 */
void LED_SetPlayed(bool state)
{
    played = state;
}


/**
 * @brief Gestiona las salidas GPIO/PWM de los LEDs.
 */
void LED_GPIO(void)
{
    uint32_t duty;

    duty = LED_GetDutyCycle();

    /* Apagar inicialmente los cuatro canales */

    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);

    if (colorActive)
    {
        LED_SetColorPWM(currentColor);
        
        switch (currentColor)
        {
            case SIMON_COLOR_GREEN:
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, duty);
                break;

            case SIMON_COLOR_YELLOW:
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, duty);
                break;

            case SIMON_COLOR_RED:
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, duty);
                break;

            case SIMON_COLOR_BLUE:
                __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, duty);
                break;

            default:
                break;
        }
    }
}


/*----------------------------------------------------------
                    FUNCIONES PRIVADAS
----------------------------------------------------------*/


/**
 * @brief Calcula el ciclo de trabajo PWM según el brillo.
 *
 * @return Valor del ciclo de trabajo.
 */
static uint32_t LED_GetDutyCycle(void)
{
    uint32_t period;

    period = __HAL_TIM_GET_AUTORELOAD(&htim4);

    return (period * ledBrightness) / 100U;
}


/**
 * @brief Configura el canal PWM correspondiente al color.
 *
 * @param color Color que se desea activar.
 */
static void LED_SetColorPWM(SimonColor color)
{
    /*
     * La selección del canal PWM se realiza en LED_GPIO().
     * Esta función queda disponible para futuras modificaciones
     * del control hardware.
     */
    (void)color;
}
