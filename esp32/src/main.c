#include "wifi.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "http.h"


/**
 * @brief Inicializa y conecta el ESP32 a la red WiFi en modo estación
 */
void wifi_init_sta(void)
{
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "ubuntu24",
            .password = "notfiewifi",
        },
    };

    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
    esp_wifi_connect();
}


void app_main(void)
{
    // Inicializa almacenamiento NVS
    nvs_flash_init();
    
    // Conecta a la red WiFi
    wifi_init_sta();

    // Inicia la tarea que consulta el servidor HTTP
    xTaskCreate(&http_get_task, "http_get_task", 8192, NULL, 5, NULL);
}
