# Proyecto de Respaldo Automático con ESP32 y Raspberry Pi

Este repositorio contiene dos partes:

- `/esp32`: Código en PlatformIO (C++) para ESP32 que chequea el estado de `https://imprenet.ar`.
- `/raspberry`: Script Python que ejecuta backups si el servidor está caído.
- `/docs`: Documentación generada con Doxygen o manual.

## Requisitos
- ESP32 DevKit
- Raspberry Pi Zero 2 W
- MicroSD Clase 10
- Fuente 5V 2A

## Cómo usar
1. Cargar `/esp32` en PlatformIO y flashear el ESP32
2. Ejecutar `/raspberry/monitor.py` en la Raspberry Pi
3. Asegurarse de tener instalados `mysqldump`, `lftp`, y Python 3

## Licencia
MIT