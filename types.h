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
    double avg_turn;
    double avg_wait;
    double thru;
} bench_result_t;
#endif