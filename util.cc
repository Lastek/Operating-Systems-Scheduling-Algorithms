#include <iomanip>
#include "util.h"
/**
 * return 1 if match, 0 otherwise
 */
int double_cmp(double x, double y, double precision)
{
    x *= precision;
    y *= precision;
    x = std::round(x);
    y = std::round(y);
    if (x == y)
    {
        return 1;
    }
    else
        return 0;
}

// sort by arrival time
std::vector<proc_data_t> lazysort_vec(const std::vector<proc_data_t> &v)
{
    std::vector<proc_data_t> sorted;
    int i = 0;
    int max = 0;
    for (auto &x : v)
    {
        if (max < x.arrival_time)
            max = x.arrival_time;
    }
    while (i <= max)
    {
        for (auto &x : v)
        {
            if (x.arrival_time == i)
            {
                sorted.push_back(x);
            }
        }
        i++;
    }
    return sorted;
}

void benchmark_results(bench_result_t &actual, bench_result_t &expected)
{
    // proc_data_t pdt;
    using std::cout;
    using std::endl;
    using std::string;
    string s;
    bench_result_t *a;
    bench_result_t *e;
    a = &actual;
    e = &expected;
    std::cout.precision(3);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);

        s = "DOES NOT MATCH EXPECTED";
    cout << "Average Turnaround Time: " << a->avg_turn << endl;
    if (double_cmp(a->avg_turn, e->avg_turn))
        s = "MATCHES EXPECTED";
    cout << s << endl;

    s = "DOES NOT MATCH EXPECTED";
    cout << "Average Waiting Time: " << a->avg_wait << endl;
    if (double_cmp(a->avg_wait, e->avg_wait))
        s = "MATCHES EXPECTED";
    cout << s << endl;

    s = "DOES NOT MATCH EXPECTED";
    cout << "Throughput: " << a->thru << endl;
    if (double_cmp(a->thru, e->thru))
        s = "MATCHES EXPECTED";
    cout << s << endl;
}