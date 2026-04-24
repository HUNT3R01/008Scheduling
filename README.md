# Laboratorio 008: Simulación de Scheduling de CPU y Despliegue Bare-Metal

Este repositorio contiene nuestra implementación para el Laboratorio 008 de Sistemas Operativos. El proyecto se divide en dos fases principales: la simulación en software de algoritmos de planificación de CPU (Scheduling) y la migración de un proyecto *bare-metal* a hardware real (BeagleBone Black) como parte de los objetivos extra.

## 🚀 Parte I: Simulación de Scheduling (Software)

En esta fase, construimos un simulador para evaluar y comparar el rendimiento de distintos algoritmos de planificación del procesador. 

* **Definición de Arquitectura:** Diseñamos un archivo de cabecera (`scheduling.h`) con la estructura `Process` para registrar los metadatos de cada hilo, incluyendo ID, tiempo de ráfaga (*Burst Time*), tiempo de llegada (*Arrival Time*) y métricas de rendimiento (*Waiting* y *Turnaround Time*).
* **Generador de Entornos:** Implementamos una función para instanciar dinámicamente entre 5 y 15 procesos aleatorios, con ráfagas de 1-10 segundos y tiempos de llegada de 0-100 segundos.
* **Algoritmo FIFO:** Desarrollamos la lógica central del algoritmo *First-In-First-Out*, integrando un ordenamiento previo por tiempo de llegada y el cálculo preciso de los promedios de espera.
* **Sistema de Aislamiento de Datos:** Para garantizar una comparación justa entre todos los algoritmos (FIFO, SJF, RR, SRTF), implementamos un sistema "maestro-copia" en el `main.c` utilizando `memcpy`. Esto nos asegura que cada algoritmo procese exactamente el mismo conjunto de datos iniciales sin sufrir contaminación por modificaciones previas.

## 🛠️ Parte II: Puntos Extra - Portabilidad a BeagleBone Black 

Como parte del primer objetivo de puntos extra, logramos migrar nuestro proyecto anterior (Calculadora Bare-Metal del Lab 2) desde el emulador QEMU hacia el hardware físico de una BeagleBone Black (procesador AM335x), sin utilizar ningún sistema operativo.

* **Reconfiguración de Memoria:** Modificamos el *Linker Script* (`linker.ld`) para direccionar la ejecución hacia la RAM DDR3 física de la placa en la dirección `0x82000000`, y ajustamos el *Stack Pointer* en nuestro archivo de ensamblador (`root.s`).
* **Control de Periféricos (UART0):** Reescribimos los controladores de comunicación serial para que apuntaran a la dirección física correcta del AM335x (`0x44E09000`). Además, corregimos el acceso a los registros para leer/escribir exactamente 8 bits, evitando la corrupción de caracteres en la terminal.
* **Manejo del Hardware Crítico:** Implementamos rutinas para desactivar el *Watchdog Timer* (Perro Guardián) de la placa, evitando reinicios automáticos cada 60 segundos durante la ejecución.
* **Depuración de Entrada:** Optimizamos la lectura de datos por serial para ignorar los saltos de línea residuales dejados por el gestor de arranque (U-Boot), logrando una interacción estable y fluida con el usuario.
