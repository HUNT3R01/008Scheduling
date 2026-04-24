#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "scheduling.h"

// SJF (no preemptivo): cuando la CPU queda libre, selecciona el proceso
// con el menor burst_time entre los que ya han llegado.
void run_sjf(Process* p, int n, GanttEntry* gantt, int* gantt_size) {
    printf("\n--- SJF Scheduling ---\n");

    sort_by_arrival(p, n);

    int* done = calloc(n, sizeof(int));
    int  time = 0, completed = 0;
    float total_wait = 0.0, total_turnaround = 0.0;
    *gantt_size = 0;

    while (completed < n) {
        // Buscar proceso disponible con menor burst time
        int sel = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].arrival_time <= time)
                if (sel == -1 || p[i].burst_time < p[sel].burst_time)
                    sel = i;

        // Si ninguno llegó aún, saltar al próximo arribo
        if (sel == -1) {
            int next = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!done[i] && p[i].arrival_time < next)
                    next = p[i].arrival_time;
            add_gantt(gantt, gantt_size, -1, time, next);
            time = next;
            continue;
        }

        p[sel].wait_time = time - p[sel].arrival_time;
        printf("Process %d (Burst %d): Arrived at %d, Started (waited %d seconds)\n",
               p[sel].id, p[sel].burst_time, p[sel].arrival_time, p[sel].wait_time);

        add_gantt(gantt, gantt_size, p[sel].id, time, time + p[sel].burst_time);
        time += p[sel].burst_time;

        p[sel].turnaround_time = p[sel].wait_time + p[sel].burst_time;
        printf("Process %d (Burst %d): Completed\n", p[sel].id, p[sel].burst_time);

        total_wait       += p[sel].wait_time;
        total_turnaround += p[sel].turnaround_time;
        done[sel] = 1;
        completed++;
    }

    printf("Avg Waiting Time: %.2f seconds\n",    total_wait       / n);
    printf("Avg Turnaround Time: %.2f seconds\n", total_turnaround / n);
    free(done);
}