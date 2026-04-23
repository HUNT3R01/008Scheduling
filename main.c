#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "scheduling.h"

int main() {
    srand(time(NULL));
    int count = (rand() % 11) + 5; 
    
    printf("==========================================\n");
    printf("   CPU SCHEDULING SIMULATION (LAB 008)    \n");
    printf("==========================================\n");
    printf("Total processes generated: %d\n\n", count);

    // Arreglo MAESTRO de procesos en memoria dinámica
    Process* master_processes = (Process*)malloc(count * sizeof(Process));
    generate_random_processes(master_processes, count);

    printf("--- Initial Process List ---\n");
    printf("ID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t\t%d\n", master_processes[i].id, 
               master_processes[i].arrival_time, 
               master_processes[i].burst_time);
    }
    printf("----------------------------\n");

    // ALGORITMO 1: FIFO
    // Hacemos una copia del arreglo para no contaminarlo
    Process* fifo_processes = (Process*)malloc(count * sizeof(Process));
    memcpy(fifo_processes, master_processes, count * sizeof(Process));
    run_fifo(fifo_processes, count);


    // ALGORITMO 2: SJF
    // Hacemos una copia del arreglo para no contaminarlo
    Process* sjf_processes = (Process*)malloc(count * sizeof(Process));
    memcpy(sjf_processes, master_processes, count * sizeof(Process));


    // ALGORITMO 3 & 4:

    // Limpieza de memoria
    free(fifo_processes);
    free(sjf_processes);
    free(master_processes);

    return 0;
}