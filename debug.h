#include <queue>
#include <list>
#include <iostream>
// #ifndef __TYPES_H
#include "types.h"
// #endif

void print_queue(const std::queue<proc_data_t> &q);

/**
 * print_order: 0 arrival time first, 1 burst time first, 2 priority first, 3 pid first,
 */
void print_vector(const std::vector<proc_data_t> &q, int print_order=0);

int check_queue_sorted(const std::queue<proc_data_t> &q);

int check_list_sorted(const std::list<proc_data_t> &lst, int order=0);