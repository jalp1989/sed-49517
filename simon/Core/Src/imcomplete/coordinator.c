#include "coordinator.h"

#include "simon.h"
#include "sequence.h"
#include "button_register.h"
#include "buttons.h"
#include "difficulty.h"
#include "light.h"
#include "led.h"
#include "sound.h"


/* Variables internas del coordinador */
static SimonColor sequence[SEQUENCE_MAX_LENGTH];
static bool sequence_obtained = false;


static const SimonColor *playerSequence = NULL;




/* Funciones privadas */
static void processSurvey(void);
//static void initSequence(void);
static void readInput(void);
static void dispatchEvents(void);

static int8_t compareSequences(const SimonColor *generatedSequence,
                               const SimonColor *playerSequence,
                               uint8_t length);


/**
 * @brief Inicializa el coordinador y los módulos.
 */
void Coordinator_Init(void)
{
    Simon_Init();
    Sequence_Init();
    ButtonRegister_Init();
    Buttons_Init();
    Difficulty_Init();
    Light_Init();
    LED_Init();
    Sound_Init();
}


/**
 * @brief Actualiza el coordinador.
 *
 * Ejecuta las operaciones de coordinación del juego.
 */
void Coordinator_Update(void)
{
    processSurvey();
    //initSequence();
    readInput();
    dispatchEvents();
}


/**
 * @brief Consulta el estado actual de Simon y gestiona
 * las acciones correspondientes a cada estado.
 */
static void processSurvey(void)
{
    SimonState currentState;
    SimonTiming timing;


    currentState = Simon_GetState();

    switch (currentState)
    {
        case SIMON_STATE_IDLE:
            Sequence_StartNewGame();
            ButtonRegister_Reset();
            Simon_StartGame();
            Simon_StateIncreaser(true);

            sequence_obtained = false;
            break;

        case SIMON_STATE_SHOWING_SEQUENCE:
            
            if (sequence_obtained == false)
            {
                if (Sequence_GetSequence(sequence,SEQUENCE_MAX_LENGTH) == true)
                {
                    sequence_obtained = true;
                }
            }

            if (sequence_obtained == true)
            {
                if (!LED_GetPlaying() && !LED_GetPlayed())
                {
                    Difficulty_GetTiming(&timing);
                    LED_PlayColors(sequence, Simon_GetLevel(),timing.onTimeMs,timing.offTimeMs);
                }

                if (!LED_GetPlaying() && LED_GetPlayed())
                {
                    Simon_StateIncreaser(true);

                    LED_SetPlayed(false);
                    sequence_obtained = false;
                }
            }

            break;


        case SIMON_STATE_WAITING_INPUT:

            if (!ButtonRegister_GetTakingData() &&
                !ButtonRegister_GetDataTaken())
            {
                ButtonRegister_TakeData(Simon_GetLevel());
            }

            if (!ButtonRegister_GetTakingData() &&
                ButtonRegister_GetDataTaken())
            {
                playerSequence = ButtonRegister_GetData();

                Simon_StateIncreaser(true);
            }

            break;

        case SIMON_STATE_ROUND_COMPLETED:
            /* Pendiente de implementar */
            break;

        case SIMON_STATE_GAME_OVER:
            /* Pendiente de implementar */

            break;

        case SIMON_STATE_GAME_WON:
            /* Pendiente de implementar */
 
            break;

        default:
            break;
    }
}

static int8_t compareSequences(const SimonColor *generatedSequence,
                               const SimonColor *playerSequence,
                               uint8_t length){
    uint8_t i;
    if (generatedSequence == NULL || playerSequence == NULL)
    {
        return -1;
    }
    for (i = 0; i < length; i++)
    {
        if (generatedSequence[i] != playerSequence[i])
        {
            return -1;
        }
    }

    return 1;
}