#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

/**
 * @brief Inicializa el módulo Sound.
 */
void Sound_Init(void);

/**
 * @brief Gestiona la reproducción de sonidos.
 */
void Sound_Update(void);

/**
 * @brief Reproduce un sonido.
 *
 * @param frequency Frecuencia del sonido en Hz.
 * @param duration Duración del sonido en milisegundos.
 */
void Sound_Play(uint16_t frequency, uint32_t duration);

/**
 * @brief Reproduce el sonido de victoria.
 */
void Sound_PlayWin(void);

/**
 * @brief Reproduce el sonido de derrota.
 */
void Sound_PlayLose(void);

/**
 * @brief Detiene la reproducción del sonido.
 */
void Sound_Stop(void);

#endif /* SOUND_H */