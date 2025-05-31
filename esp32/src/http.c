#include "http.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

#define URL "http://imprenet.ar/TECNICASDIGITALES2/status.txt"
static const char *TAG = "HTTP_STATUS";

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    // No necesitamos procesar nada en los eventos por ahora
    return ESP_OK;
}

void http_get_task(void *pvParameters)
{
    esp_http_client_config_t config = {
        .url = URL,
        .event_handler = _http_event_handler
    };

    while (1) {
        esp_http_client_handle_t client = esp_http_client_init(&config);
        esp_err_t err = esp_http_client_perform(client);

        if (err == ESP_OK) {
            int status_code = esp_http_client_get_status_code(client);
            ESP_LOGI(TAG, "🌐 Código HTTP: %d", status_code);

            if (status_code == 200) {
                ESP_LOGI(TAG, "✅ Estado: ON");
            } else {
                ESP_LOGI(TAG, "❌ Servidor caído");
            }
        } else {
            ESP_LOGE(TAG, "❌ Error en la solicitud HTTP: %s", esp_err_to_name(err));
            ESP_LOGI(TAG, "❌ Servidor caído");
        }

        esp_http_client_cleanup(client);
        vTaskDelay(pdMS_TO_TICKS(10000)); // cada 10 segundos
    }
}
