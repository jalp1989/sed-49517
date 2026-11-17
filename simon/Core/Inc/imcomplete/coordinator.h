#ifndef COORDINATOR_H
#define COORDINATOR_H

/**
 * @brief Inicializa el módulo Coordinator
 * y los módulos necesarios para el juego.
 */
void Coordinator_Init(void);

/**
 * @brief Actualiza y coordina el funcionamiento del juego.
 *
 * Se ejecuta periódicamente desde el bucle principal.
 */
void Coordinator_Update(void);

/**
 * @brief Procesa el estado actual de la partida.
 */
void Coordinator_ProcessGame(void);

/**
 * @brief Inicializa una nueva secuencia.
 */
void Coordinator_InitSequence(void);

/**
 * @brief Lee y procesa las entradas del jugador.
 */
void Coordinator_ReadInput(void);

/**
 * @brief Distribuye y procesa los eventos recibidos.
 */
void Coordinator_DispatchEvents(void);

/**
 * @brief Gestiona las interrupciones externas de los botones.
 *
 * @param GPIO_Pin Pin que ha generado la interrupción.
 */
void Coordinator_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* COORDINATOR_H */