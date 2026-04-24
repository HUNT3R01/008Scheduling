#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "scheduling.h"

// Round Robin: cada proceso recibe un máximo de 'quantum' unidades de CPU.
// Si no termina en ese tiempo, vuelve al final de la cola circular.
void run_rr(Process* p, int n, int quantum, GanttEntry* gantt, int* gantt_size) {
    printf("\n--- Round Robin Scheduling (Quantum %d) ---\n", quantum);

    sort_by_arrival(p, n);

    int* rem      = malloc(n * sizeof(int));   // tiempo restante por proceso
    int* enqueued = calloc(n, sizeof(int));    // indica si ya entró a la cola

    // Capacidad máxima de la cola (worst case: cada unidad de burst es un turno)
    int q_cap = 0;
    for (int i = 0; i < n; i++) { rem[i] = p[i].burst_time; q_cap += p[i].burst_time + 2; }
    q_cap += n * 4;

    int* queue  = malloc(q_cap * sizeof(int));
    int  q_head = 0, q_tail = 0;
    float total_wait = 0.0, total_turnaround = 0.0;
    *gantt_size = 0;

    // Iniciar en el primer arribo y encolar los procesos disponibles
    int time = p[0].arrival_time;
    if (time > 0) add_gantt(gantt, gantt_size, -1, 0, time);
    for (int i = 0; i < n; i++)
        if (p[i].arrival_time <= time && !enqueued[i])
            { queue[q_tail++ % q_cap] = i; enqueued[i] = 1; }

    int completed = 0;

    while (completed < n) {
        // Si la cola está vacía, avanzar al próximo proceso no encolado
        while (q_head % q_cap == q_tail % q_cap) {
            int next = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!enqueued[i] && rem[i] > 0 && p[i].arrival_time < next)
                    next = p[i].arrival_time;
            if (next == INT_MAX) break;
            add_gantt(gantt, gantt_size, -1, time, next);
            time = next;
            for (int i = 0; i < n; i++)
                if (!enqueued[i] && rem[i] > 0 && p[i].arrival_time <= time)
                    { queue[q_tail++ % q_cap] = i; enqueued[i] = 1; }
        }
        if (q_head % q_cap == q_tail % q_cap) break;

        int idx   = queue[q_head++ % q_cap];
        int slice = (rem[idx] < quantum) ? rem[idx] : quantum;

        add_gantt(gantt, gantt_size, p[idx].id, time, time + slice);
        time     += slice;
        rem[idx] -= slice;

        // Encolar procesos que llegaron mientras corría este slice
        for (int i = 0; i < n; i++)
            if (!enqueued[i] && rem[i] > 0 && p[i].arrival_time <= time)
                { queue[q_tail++ % q_cap] = i; enqueued[i] = 1; }

        if (rem[idx] == 0) {
            p[idx].turnaround_time = time - p[idx].arrival_time;
            p[idx].wait_time       = p[idx].turnaround_time - p[idx].burst_time;
            completed++;
            printf("Process %d (Burst %d): Completed (waited %d seconds)\n",
                   p[idx].id, p[idx].burst_time, p[idx].wait_time);
            total_wait       += p[idx].wait_time;
            total_turnaround += p[idx].turnaround_time;
        } else {
            // No terminó: vuelve al final de la cola
            queue[q_tail++ % q_cap] = idx;
        }
    }

    printf("Avg Waiting Time: %.2f seconds\n",    total_wait       / n);
    printf("Avg Turnaround Time: %.2f seconds\n", total_turnaround / n);
    free(rem); free(queue); free(enqueued);
}