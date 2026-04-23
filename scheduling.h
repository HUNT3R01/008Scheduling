#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <pthread.h>

// Estructura que representa a cada proceso
typedef struct {
    int id;
    int burst_time;      // Tiempo total de CPU que necesita
    int arrival_time;    // En qué momento llega a la cola
    int remaining_time;  // Cuánto tiempo le falta (útil para RR y SRTF)
    int wait_time;       // Tiempo de espera
    int turnaround_time; // Tiempo desde que llega hasta que termina
    
    // Variables para el control de hilos
    pthread_t thread;
} Process;

// Funciones que yo implemente
void generate_random_processes(Process* processes, int count);
void run_fifo(Process* processes, int count);
void run_sjf(Process* processes, int count);

// Funciones que faltan por implementar
void run_rr(Process* processes, int count, int quantum);
void run_srtf(Process* processes, int count);
void print_gantt_chart(Process* processes, int count);

#endif