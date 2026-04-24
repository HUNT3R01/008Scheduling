#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "scheduling.h"

// SRTF (preemptivo): siempre ejecuta el proceso con menor tiempo restante.
// Si llega un proceso más corto, el actual es desalojado.
void run_srtf(Process* p, int n, GanttEntry* gantt, int* gantt_size) {
    printf("\n--- SRTF Scheduling ---\n");

    sort_by_arrival(p, n);

    int* rem  = malloc(n * sizeof(int));
    int* done = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) { rem[i] = p[i].burst_time; p[i].start_time = -1; }

    float total_wait = 0.0, total_turnaround = 0.0;
    int time = p[0].arrival_time, completed = 0;
    *gantt_size = 0;

    if (time > 0) add_gantt(gantt, gantt_size, -1, 0, time);

    while (completed < n) {
        // Seleccionar proceso con menor tiempo restante entre los llegados
        int sel = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].arrival_time <= time && rem[i] > 0)
                if (sel == -1 || rem[i] < rem[sel])
                    sel = i;

        // Si ninguno llegó aún, saltar al próximo arribo
        if (sel == -1) {
            int next = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!done[i] && p[i].arrival_time > time && p[i].arrival_time < next)
                    next = p[i].arrival_time;
            add_gantt(gantt, gantt_size, -1, time, next);
            time = next;
            continue;
        }

        // Correr hasta que termine o llegue un proceso con menor tiempo restante
        int run_until = time + rem[sel];
        for (int i = 0; i < n; i++)
            if (!done[i] && i != sel && p[i].arrival_time > time && p[i].arrival_time < run_until)
                run_until = p[i].arrival_time;

        if (p[sel].start_time == -1) {
            p[sel].start_time = time;
            printf("Process %d (Burst %d): Arrived at %d, Started\n",
                   p[sel].id, p[sel].burst_time, p[sel].arrival_time);
        }

        add_gantt(gantt, gantt_size, p[sel].id, time, run_until);
        rem[sel] -= run_until - time;
        time      = run_until;

        if (rem[sel] == 0) {
            p[sel].turnaround_time = time - p[sel].arrival_time;
            p[sel].wait_time       = p[sel].turnaround_time - p[sel].burst_time;
            done[sel] = 1;
            completed++;
            printf("Process %d (Burst %d): Completed (waited %d seconds)\n",
                   p[sel].id, p[sel].burst_time, p[sel].wait_time);
            total_wait       += p[sel].wait_time;
            total_turnaround += p[sel].turnaround_time;
        }
    }

    printf("Avg Waiting Time: %.2f seconds\n",    total_wait       / n);
    printf("Avg Turnaround Time: %.2f seconds\n", total_turnaround / n);
    free(rem); free(done);
}