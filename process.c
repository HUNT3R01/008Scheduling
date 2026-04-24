#include <stdio.h>
#include <stdlib.h>
#include "scheduling.h"

// Genera procesos con burst (1-10s) y arrival time (0-100s) aleatorios
void generate_random_processes(Process* processes, int count) {
    for (int i = 0; i < count; i++) {
        processes[i].id              = i;
        processes[i].burst_time      = (rand() % 10) + 1;
        processes[i].arrival_time    = rand() % 101;
        processes[i].remaining_time  = processes[i].burst_time;
        processes[i].wait_time       = 0;
        processes[i].turnaround_time = 0;
        processes[i].start_time      = -1;
        processes[i].completion_time = 0;
    }
}

// Ordena los procesos por arrival_time de menor a mayor
void sort_by_arrival(Process* p, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].arrival_time > p[j+1].arrival_time) {
                Process tmp = p[j];
                p[j]        = p[j+1];
                p[j+1]      = tmp;
            }
}

// Imprime tabla de resultados y promedios de waiting/turnaround time
void print_stats(Process* p, int n) {
    float total_wt = 0, total_tat = 0;

    printf("  %-5s %-12s %-10s %-12s %-14s\n",
           "PID", "Arrival", "Burst", "Wait", "Turnaround");

    for (int i = 0; i < n; i++) {
        printf("  %-5d %-12d %-10d %-12d %-14d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].wait_time, p[i].turnaround_time);
        total_wt  += p[i].wait_time;
        total_tat += p[i].turnaround_time;
    }

    printf("  Avg Waiting Time:    %.2f seconds\n", total_wt  / n);
    printf("  Avg Turnaround Time: %.2f seconds\n", total_tat / n);
}