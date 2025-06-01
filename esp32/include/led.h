/**
 * @file led.h
 * @brief Control de LEDs de estado en ESP32.
 *
 * Este módulo permite configurar y manejar LEDs conectados a los pines GPIO del ESP32
 * para indicar estados como "OK" o "Error".
 */

#ifndef LED_H
#define LED_H

#include "driver/gpio.h"

/// GPIO usado para el LED verde (estado OK)
#define LED_VERDE GPIO_NUM_25

/// GPIO usado para el LED rojo (estado de error)
#define LED_ROJO  GPIO_NUM_32

/**
 * @brief Configura los pines de los LEDs como salida.
 */
void configurar_leds(void);

/**
 * @brief Enciende el LED verde y apaga el rojo (estado OK).
 */
void led_estado_ok(void);

/**
 * @brief Enciende el LED rojo y apaga el verde (estado de error).
 */
void led_estado_error(void);

#endif
