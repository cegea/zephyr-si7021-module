# Zephyr Si7021 Module

This repo is intended for learning Zephyr as part of the Embedded Platforms course of the Master IoT from UPM.

## Arquitectura del repo

Esta arquitectura permite a zephyr importar este repo como el sensor.
```
zephyr-si7021-module/           # Raíz de tu repositorio Git
├── README.md                   # Documentación y guía de uso
├── zephyr/                     # Carpeta de integración obligatoria para Zephyr
│   ├── module.yml              # El "DNI" del módulo para Zephyr
│   ├── Kconfig                 # Punto de entrada de configuración del módulo
│   ├── dts/
│   │   └── bindings/
│   │       └── sensor/
│   │           └── adafruit,si7021.yaml # Devicetree binding (identifica al sensor)
│   └── drivers/
│       └── sensor/
│           ├── CMakeLists.txt  # Instrucciones de compilación de CMake
│           ├── Kconfig         # Definición de las variables Kconfig del driver
│           ├── si7021.h        # Cabecera privada (direcciones I2C, registros, comandos)
│           └── si7021.c        # Implementación del driver (API de Zephyr)
└── samples/                    # Opcional: Ejemplo didáctico de cómo usar tu driver
    └── si7021_polling/
        ├── CMakeLists.txt
        ├── prj.conf
        ├── app.overlay         # Mapeo del sensor al bus I2C de la placa
        └── src/
            └── main.c          # Tu aplicación usando sensor_sample_fetch()
```

## Doc de referencia
- zephyrproject-rtos/example-application en GitHub:
    - Ejemplo: `drivers/sensor/examplesensor` contiene `module.yml`, bindings y Kconfig.

## Ficheros involucrados y su función

### zephyr/module.yml 

### adafruit,si7021.yml

El DT (`app.overlay`) declara que hay un dispositivo `compatible = "adafruit,si7021"` en una dirección I2C.

El binding es el esquema de ese nodo: qué propiedades admite, cuales son obligatorias y de qué tipo. Al configurar, el build busca un binding cuyo `compatible` coincida con el del nodo. Si no lo encuentra, el nodo no recibe macros`DT_*` útiles, no genera`DT_HAS_ADAFRUIT_SI7021_ENABLED` y el driver nunca se compila.
 
