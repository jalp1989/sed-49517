#include "coordinator.h"

#include "simon.h"
#include "sequence.h"
#include "button_register.h"
//#include "buttons.h"
#include "difficulty.h"
#include "light.h"
#include "led.h"
#include "sound.h"


/* Variables internas del coordinador */
static SimonColor sequence[SEQUENCE_MAX_LENGTH];
static bool sequence_obtained = false;


static const SimonColor *playerSequence = NULL;




/* Funciones privadas */
static void processGame(void);

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
    //Buttons_Init(); //esta es inicializada por ButtonRegister
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
    processGame();

}


/**
 * @brief Consulta el estado actual de Simon y gestiona
 * las acciones correspondientes a cada estado.
 */
static void processGame(void)
{
    SimonState currentState;
    SimonTiming timing;
    int8_t comparisonResult;

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
            
            comparisonResult = compareSequences(sequence,playerSequence,Simon_GetLevel());

            if (comparisonResult == -1 || comparisonResult == 1)
            {
                Simon_SetComparisonResult(comparisonResult);
                Simon_StateIncreaser(true);
            }   

            break;

        case SIMON_STATE_GAME_OVER:

        if (!Sound_GetPlaying() && !Sound_GetPlayed())
        {
            Sound_Play_GameOver();
        }

        if (!Sound_GetPlaying() && Sound_GetPlayed())
        {
            Simon_StateIncreaser(true);
            Sound_SetPlayed(false);
        }

            break;

        case SIMON_STATE_GAME_WON:
 
        if (!Sound_GetPlaying() && !Sound_GetPlayed())
        {
            Sound_Play_Won();
        }

        if (!Sound_GetPlaying() && Sound_GetPlayed())
        {
            Simon_StateIncreaser(true);
            Sound_SetPlayed(false);
        }
            
            break;

        default:
            break;
    }
}

static int8_t compareSequences(const SimonColor *generatedSequence,
                               const SimonColor *playerSequence,
                               uint8_t length){
    uint8_t i;
    if (generatedSequence == NULL || playerSequence == NULL || length == 0)
    {
        return -99;//error
    }
    for (i = 0; i < length; i++)
    {
        if (generatedSequence[i] != playerSequence[i])
        {
            return -1;//nok
        }
    }

    return 1;//ok
}