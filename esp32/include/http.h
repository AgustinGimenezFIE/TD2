/**
 * @file http.h
 * @brief Declaración de la tarea de consulta HTTP
 */

#ifndef HTTP_H
#define HTTP_H

/**
 * @brief Tarea que realiza una petición HTTP GET periódicamente
 * 
 * @param pvParameters Parámetro para FreeRTOS (sin uso)
 */
void http_get_task(void *pvParameters);

#endif // HTTP_H
