
/**
 * @file http.c
 * @brief Implementación del cliente HTTP para el ESP32
 *
 * Este archivo contiene funciones que permiten conectarse a un servidor HTTP
 * y analizar el estado remoto (ON, OFF o desconocido).
 */


#include "http.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

#define URL "http://imprenet.ar/TECNICASDIGITALES2/status.txt"
static const char *TAG = "HTTP_STATUS";

/**
 * @brief Manejador de eventos HTTP que analiza la respuesta del servidor
 * 
 * @param evt Evento HTTP recibido
 * @return esp_err_t Código de error (ESP_OK si fue exitoso)
 */
esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG, "📦 Respuesta: %.*s", evt->data_len, (char *)evt->data);
            if (strstr((char *)evt->data, "ON")) {
                ESP_LOGI(TAG, "✅ Estado: ON");
            } else if (strstr((char *)evt->data, "OFF")) {
                ESP_LOGI(TAG, "⚠️ Estado: OFF");
            } else {
                ESP_LOGI(TAG, "❓ Estado desconocido");
            }
            break;
        default:
            break;
    }
    return ESP_OK;
}

/**
 * @brief Tarea que consulta el estado del servidor cada 10 segundos
 * 
 * @param pvParameters Parámetro sin uso
 */
void http_get_task(void *pvParameters)
{
    esp_http_client_config_t config = {
        .url = URL,
        .event_handler = _http_event_handler
    };

    while (1) {
        esp_http_client_handle_t client = esp_http_client_init(&config);
        esp_http_client_perform(client);
        esp_http_client_cleanup(client);

        vTaskDelay(pdMS_TO_TICKS(10000)); // cada 10 segundos
    }
}
