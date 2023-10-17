# Ejemplos de Programación para ARM Cortex-M3 LPC1769

Este repositorio contiene ejemplos de código en C para programar el ARM Cortex-M3 LPC1769, centrándose en varias características y periféricos comunes. Los ejemplos proporcionan una base para desarrolladores que deseen trabajar con este microcontrolador y aprender a programar sus periféricos.

## Periféricos y Temas Cubiertos

Los ejemplos de código en este repositorio cubren los siguientes periféricos y temas:

- **ADC (Convertidor Analógico-Digital):** Ejemplos de lectura de señales analógicas y conversión a valores digitales.

- **DAC (Convertidor Digital-Analógico):** Ejemplos de generación de señales analógicas a partir de valores digitales.

- **DMA (Acceso Directo a Memoria):** Ejemplos que muestran cómo utilizar el DMA para transferir datos entre: P2P, M2M, P2M M2P.

- **Timers:** Ejemplos de modulos temporizadores en su modo timer o capture, para generar intervalos de tiempo precisos en el control de eventos y su modo capture para demodular señales.

- **Systick:** Ejemplos que muestran cómo usar el temporizador SysTick integrado en el core para generar interrupciones periódicas de 10ms.

- **Interrupciones:** Ejemplos que demuestran cómo configurar y manejar interrupciones.

- **GPIO (Entrada/Salida de Propósito General):** Ejemplos que ilustran cómo configurar y utilizar pines GPIO.

## Estructura del Repositorio

La estructura del repositorio es la siguiente:

- `1era_parte/`: Ejemplos relacionados con GPIO, Interrupciones y Systick
- `2da_parte/`: Ejemplos relacionados con el ADC, DAC, Timers y DMA.

## Requisitos y Configuración

Para utilizar los ejemplos, asegúrate de tener las librerias de los drivers necesarios del CMSIS adecuadas, un ide como puede ser MCU_expresso y obviamente la placa de desarrollo LPC1769.

## Contribuciones

¡Las contribuciones son bienvenidas! Si tienes ejemplos adicionales o mejoras a los ejemplos existentes, no dudes en crear una solicitud de extracción (pull request). Asegúrate de seguir las pautas de contribución del repositorio.

## Contacto

- [Facundo Lorenzo] - [faculorern7@gmail.com | florenzo@mi.unc.edu.ar]
- Enlace al [https://github.com/Facu-hub-code]

¡Esperamos que estos ejemplos te sean útiles para aprender y trabajar con el ARM Cortex-M3 LPC1769!


