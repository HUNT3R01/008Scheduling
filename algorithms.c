#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "scheduling.h"

void generate_random_processes(Process* processes, int count){
    for (int i = 0; i < count; i++) {
        processes[i].id = i;
        processes[i].burst_time = (rand() % 10) + 1; 
        processes[i].arrival_time = rand() % 101;     //
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].wait_time = 0;
        processes[i].turnaround_time = 0;
    }
}

void sort_by_arrival(Process* processes, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}


void run_fifo(Process* processes, int count) {
    printf("\n--- FIFO Scheduling ---\n");
    
    sort_by_arrival(processes, count);

    int current_time = 0;
    float total_wait = 0.0, total_turnaround = 0.0;

    for (int i = 0; i < count; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time; 
        }

        processes[i].wait_time = current_time - processes[i].arrival_time;
        printf("Process %d (Burst %d): Arrived at %d, Started (waited %d seconds)\n",
               processes[i].id, processes[i].burst_time, processes[i].arrival_time, processes[i].wait_time);

        current_time += processes[i].burst_time;
        processes[i].turnaround_time = processes[i].wait_time + processes[i].burst_time;
        printf("Process %d (Burst %d): Completed\n", processes[i].id, processes[i].burst_time);
        total_wait += processes[i].wait_time;
        total_turnaround += processes[i].turnaround_time;
    }

    printf("Avg Waiting Time: %.2f seconds\n", total_wait / count);
    printf("Avg Turnaround Time: %.2f seconds\n", total_turnaround / count);
}