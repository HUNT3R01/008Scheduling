#include <stdio.h>
#include "scheduling.h"

// FIFO: ejecuta los procesos en orden de llegada.
// Cada proceso corre hasta completarse antes de que el siguiente inicie.
void run_fifo(Process* p, int n, GanttEntry* gantt, int* gantt_size) {
    printf("\n--- FIFO Scheduling ---\n");

    sort_by_arrival(p, n);

    int time = 0;
    float total_wait = 0.0, total_turnaround = 0.0;
    *gantt_size = 0;

    for (int i = 0; i < n; i++) {
        // Si la CPU está libre antes de que llegue el proceso, registrar IDLE
        if (time < p[i].arrival_time) {
            add_gantt(gantt, gantt_size, -1, time, p[i].arrival_time);
            time = p[i].arrival_time;
        }

        p[i].wait_time = time - p[i].arrival_time;
        printf("Process %d (Burst %d): Arrived at %d, Started (waited %d seconds)\n",
               p[i].id, p[i].burst_time, p[i].arrival_time, p[i].wait_time);

        add_gantt(gantt, gantt_size, p[i].id, time, time + p[i].burst_time);
        time += p[i].burst_time;

        p[i].turnaround_time = p[i].wait_time + p[i].burst_time;
        printf("Process %d (Burst %d): Completed\n", p[i].id, p[i].burst_time);

        total_wait       += p[i].wait_time;
        total_turnaround += p[i].turnaround_time;
    }

    printf("Avg Waiting Time: %.2f seconds\n",    total_wait       / n);
    printf("Avg Turnaround Time: %.2f seconds\n", total_turnaround / n);
}