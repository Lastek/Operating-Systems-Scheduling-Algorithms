#include "util.h"

#ifdef DEBUG_SCHED
#include "debug.h"
#endif

void scheduler_fcfs(const std::vector<proc_data_t> &proc_store);

void scheduler_sjfp(const std::vector<proc_data_t> &proc_store);

void scheduler_priority(const std::vector<proc_data_t> &proc_store);