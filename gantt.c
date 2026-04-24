#include <stdio.h>
#include "scheduling.h"

// Agrega un bloque al Gantt. Si el proceso es el mismo y contiguo,
// extiende el bloque anterior en lugar de crear uno nuevo.
void add_gantt(GanttEntry* g, int* sz, int pid, int start, int end) {
    if (*sz > 0 && g[*sz-1].process_id == pid && g[*sz-1].end == start) {
        g[*sz-1].end = end;
        return;
    }
    g[*sz].process_id = pid;
    g[*sz].start      = start;
    g[*sz].end        = end;
    (*sz)++;
}

// Imprime el Gantt Chart en ASCII para un algoritmo dado
void print_gantt_chart(const char* label, GanttEntry* gantt, int gantt_size) {
    if (gantt_size == 0) return;

    printf("  %s\n", label);

    // Línea superior
    printf("  ");
    for (int i = 0; i < gantt_size; i++) {
        int w = gantt[i].end - gantt[i].start;
        if (w < 4) w = 4;
        printf("+");
        for (int j = 0; j < w + 1; j++) printf("-");
    }
    printf("+\n  ");

    // Etiquetas de proceso
    for (int i = 0; i < gantt_size; i++) {
        int w = gantt[i].end - gantt[i].start;
        if (w < 4) w = 4;
        if (gantt[i].process_id == -1)
            printf("| %-*s", w, "IDLE");
        else
            printf("| P%-*d", w - 1, gantt[i].process_id);
    }
    printf("|\n  ");

    // Línea inferior
    for (int i = 0; i < gantt_size; i++) {
        int w = gantt[i].end - gantt[i].start;
        if (w < 4) w = 4;
        printf("+");
        for (int j = 0; j < w + 1; j++) printf("-");
    }
    printf("+\n  ");

    // Marcas de tiempo debajo de cada bloque
    for (int i = 0; i < gantt_size; i++) {
        int w = gantt[i].end - gantt[i].start;
        if (w < 4) w = 4;
        printf("%-*d", w + 2, gantt[i].start);
    }
    printf("%d\n\n", gantt[gantt_size - 1].end);
}