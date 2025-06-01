/**
 * @file led.c
 * @brief Implementación del control de LEDs en ESP32.
 */

#include "led.h"

/**
 * @brief Inicializa los pines GPIO asignados a los LEDs como salidas.
 */
void configurar_leds(void)
{
    gpio_reset_pin(LED_VERDE);
    gpio_set_direction(LED_VERDE, GPIO_MODE_OUTPUT);
    gpio_reset_pin(LED_ROJO);
    gpio_set_direction(LED_ROJO, GPIO_MODE_OUTPUT);
}

/**
 * @brief Enciende el LED verde y apaga el rojo.
 */
void led_estado_ok(void)
{
    gpio_set_level(LED_VERDE, 1);
    gpio_set_level(LED_ROJO, 0);
}

/**
 * @brief Enciende el LED rojo y apaga el verde.
 */
void led_estado_error(void)
{
    gpio_set_level(LED_VERDE, 0);
    gpio_set_level(LED_ROJO, 1);
}
