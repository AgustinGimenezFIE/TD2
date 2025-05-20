#include <WiFi.h>
#include <HTTPClient.h>

/** @brief SSID de la red WiFi */
const char* ssid = "TU_SSID";
/** @brief Contraseña de la red WiFi */
const char* password = "TU_PASSWORD";

/** @brief URL del servidor a monitorear */
const char* serverURL = "https://imprenet.ar";

/** @brief Intervalo de chequeo en milisegundos (5 minutos) */
const unsigned long CHECK_INTERVAL = 5 * 60 * 1000;
unsigned long lastCheckTime = 0;

/**
 * @brief Inicializa la conexión WiFi
 */
void conectarWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
}

/**
 * @brief Verifica el estado del servidor remoto
 * 
 * @return true si el servidor respondió con código 200
 * @return false si hubo error o no respondió correctamente
 */
bool chequearServidor() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    int httpCode = http.GET();
    http.end();
    return (httpCode == 200);
  }
  return false;
}

/**
 * @brief Configuración inicial de hardware
 */
void setup() {
  Serial.begin(115200);
  conectarWiFi();
}

/**
 * @brief Bucle principal que chequea el servidor periódicamente
 */
void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastCheckTime >= CHECK_INTERVAL || lastCheckTime == 0) {
    bool serverActivo = chequearServidor();
    if (serverActivo) {
      Serial.println("OK");
    } else {
      Serial.println("DOWN");
    }
    lastCheckTime = currentTime;
  }
}