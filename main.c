#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scheduling.h"

#define RR_QUANTUM 2

int main() {
    srand(time(NULL));

    // Generar entre 5 y 15 procesos aleatorios
    int count = (rand() % 11) + 5;

    printf("==========================================\n");
    printf("         SCHEDULING LAB 008        \n");
    printf("==========================================\n");
    printf("Total de procesos generados: %d\n", count);
    printf("Round Robin quantum      : %d\n\n", RR_QUANTUM);

    Process* master = malloc(count * sizeof(Process));
    generate_random_processes(master, count);

    printf("--- Initial Process List ---\n");
    printf("  %-5s %-14s %-10s\n", "PID", "Arrival Time", "Burst Time");
    for (int i = 0; i < count; i++)
        printf("  %-5d %-14d %-10d\n",
               master[i].id, master[i].arrival_time, master[i].burst_time);
    printf("----------------------------\n");

    // Calcular tamaño máximo del Gantt
    int total_burst = 0;
    for (int i = 0; i < count; i++) total_burst += master[i].burst_time;
    int gantt_max = total_burst * 4 + count * 4 + 64;

    // Un Gantt por algoritmo
    GanttEntry* g_fifo = malloc(gantt_max * sizeof(GanttEntry));
    GanttEntry* g_sjf  = malloc(gantt_max * sizeof(GanttEntry));
    GanttEntry* g_rr   = malloc(gantt_max * sizeof(GanttEntry));
    GanttEntry* g_srtf = malloc(gantt_max * sizeof(GanttEntry));
    int sz_fifo = 0, sz_sjf = 0, sz_rr = 0, sz_srtf = 0;

    Process* tmp;

    // Cada algoritmo recibe una copia del mismo dataset para comparación justa
    tmp = malloc(count * sizeof(Process));
    memcpy(tmp, master, count * sizeof(Process));
    run_fifo(tmp, count, g_fifo, &sz_fifo);
    free(tmp);

    tmp = malloc(count * sizeof(Process));
    memcpy(tmp, master, count * sizeof(Process));
    run_sjf(tmp, count, g_sjf, &sz_sjf);
    free(tmp);

    tmp = malloc(count * sizeof(Process));
    memcpy(tmp, master, count * sizeof(Process));
    run_rr(tmp, count, RR_QUANTUM, g_rr, &sz_rr);
    free(tmp);

    tmp = malloc(count * sizeof(Process));
    memcpy(tmp, master, count * sizeof(Process));
    run_srtf(tmp, count, g_srtf, &sz_srtf);
    free(tmp);

    // Mostrar todos los Gantt Charts al final
    printf("\n==========================================\n");
    printf("           PARTE GRAFICA         \n");
    printf("==========================================\n");
    print_gantt_chart("FIFO:",                    g_fifo, sz_fifo);
    print_gantt_chart("SJF:",                     g_sjf,  sz_sjf);
    print_gantt_chart("Round Robin (Quantum 2):", g_rr,   sz_rr);
    print_gantt_chart("SRTF:",                    g_srtf, sz_srtf);

    free(g_fifo); free(g_sjf); free(g_rr); free(g_srtf);
    free(master);
    return 0;
}