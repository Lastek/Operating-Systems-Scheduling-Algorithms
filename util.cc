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