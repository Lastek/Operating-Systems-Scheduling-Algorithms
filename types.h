#ifndef __TYPES_H
#define __TYPES_H
typedef struct process_data_s
{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
} proc_data_t;

enum PROC_DATA_ENUM
{
    PID,
    ARIVL_T,
    BURST_T,
    PRI
};

typedef struct bench_result_s
{
    double n_processes; // Total number of processes handled
    double total_wait;  // Sum total each process spent waiting
    double time;        // How many ticks to complete
    double avg_turn;    // Average turnaround time: (total_wait + time) / n_processes
    double avg_wait;    // Average waiting time: total_wait / n_processes
    double thru;        // Throughput: n_processes / time
} bench_result_t;
#endif