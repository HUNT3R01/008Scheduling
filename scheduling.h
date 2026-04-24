#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <pthread.h>

typedef struct {
    int id;
    int burst_time;       // Tiempo total de CPU que necesita
    int arrival_time;     // Momento en que llega a la cola
    int remaining_time;   // Tiempo restante (usado en SRTF)
    int wait_time;        // Tiempo esperando en la cola
    int turnaround_time;  // Tiempo total desde llegada hasta completarse
    int start_time;       // Primer momento en que ejecuta
    int completion_time;  // Momento en que termina
    pthread_t thread;
} Process;

// Representa un bloque en el Gantt: qué proceso corrió y en qué intervalo
typedef struct {
    int process_id;  // -1 = CPU idle
    int start;
    int end;
} GanttEntry;

// Utilidades
void generate_random_processes(Process* processes, int count);
void sort_by_arrival(Process* p, int n);
void print_stats(Process* p, int n);

// Algoritmos — retornan el Gantt generado y su tamaño
void run_fifo(Process* p, int n, GanttEntry* gantt, int* gantt_size);
void run_sjf (Process* p, int n, GanttEntry* gantt, int* gantt_size);
void run_rr  (Process* p, int n, int quantum, GanttEntry* gantt, int* gantt_size);
void run_srtf(Process* p, int n, GanttEntry* gantt, int* gantt_size);

// Gantt Chart
void add_gantt(GanttEntry* g, int* sz, int pid, int start, int end);
void print_gantt_chart(const char* label, GanttEntry* gantt, int gantt_size);

#endif