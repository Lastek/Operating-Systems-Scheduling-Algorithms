#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include "types.h"
int double_cmp(double x, double y, double precision=1000);

std::vector<proc_data_t> lazysort_vec(const std::vector<proc_data_t> &v);

void benchmark_results(bench_result_t &actual, bench_result_t &expected);