#include "debug.h"

void print_queue(const std::queue<proc_data_t> &q)
{
    using std::cout;
    using std::endl;

    std::queue<proc_data_t> copy(q);
    while (!copy.empty())
    {
        cout << "PID: " << copy.front().pid
             << ", Arrival Time: " << copy.front().arrival_time
             << ", Burst Time: " << copy.front().burst_time
             << ", Priority: " << copy.front().priority << endl;
        copy.pop();
    }
    cout << "END TEST" << endl;
}

void print_vector(const std::vector<proc_data_t> &q, int print_order)
{
    switch (print_order)
    {
    case 0:
        for (const proc_data_t &pdt : q)
        {
            std::cout
                << " at: " << pdt.arrival_time
                << " bt: " << pdt.burst_time
                << " pr: " << pdt.priority
                << " pid:" << pdt.pid
                << std::endl;
        }
        break;
    case 1:
        for (const proc_data_t &pdt : q)
        {
            std::cout
                << " bt: " << pdt.burst_time
                << " at: " << pdt.arrival_time
                << " pr: " << pdt.priority
                << " pid:" << pdt.pid
                << std::endl;
        }
        break;
    case 2:
        for (const proc_data_t &pdt : q)
        {
            std::cout
                << " pr: " << pdt.priority
                << " bt: " << pdt.burst_time
                << " at: " << pdt.arrival_time
                << " pid:" << pdt.pid
                << std::endl;
        }
        break;
    case 3:
        for (const proc_data_t &pdt : q)
        {
            std::cout
                << " pid:" << pdt.pid
                << " at: " << pdt.arrival_time
                << " bt: " << pdt.burst_time
                << " pr: " << pdt.priority
                << std::endl;
        }
        break;
    default:
        break;
    }
}

int check_queue_sorted(const std::queue<proc_data_t> &q)
{
    std::queue<proc_data_t> cp(q);
    proc_data_t nx;
    int ret = 1;
    while (!cp.empty())
    {
        nx.pid = cp.front().pid;
        nx.arrival_time = cp.front().arrival_time;
        nx.burst_time = cp.front().burst_time;
        nx.priority = cp.front().priority;
        cp.pop();
        if (cp.empty())
            break;
        if (nx.arrival_time > cp.front().arrival_time)
        {
            std::cout << "que out of order\n";
            ret = 0;
        }
    }
    return ret;
}

int check_list_sorted(const std::list<proc_data_t> &lst, int order)
{
    int ret = 1;
    switch (order)
    {
    case 0:
        for (auto iter = lst.begin(); iter != --(lst.end()); ++iter)
        {
            auto nx = std::next(iter);
            if (nx->arrival_time < iter->arrival_time)
            {
                std::cout << "que out of order\n";
                ret = 0;
            }
        }
        break;
    case 1:
        for (auto iter = lst.begin(); iter != --(lst.end()); ++iter)
        {
            auto nx = std::next(iter);
            if (nx->burst_time < iter->burst_time)
            {
                std::cout << "que out of order\n";
                ret = 0;
            }
        }
        break;
    case 2:
        for (auto iter = lst.begin(); iter != --(lst.end()); ++iter)
        {
            auto nx = std::next(iter);
            if (nx->priority < iter->priority)
            {
                std::cout << "que out of order\n";
                ret = 0;
            }
        }
        break;
    case 3:
        for (auto iter = lst.begin(); iter != --(lst.end()); ++iter)
        {
            auto nx = std::next(iter);
            if (nx->pid < iter->pid)
            {
                std::cout << "que out of order\n";
                ret = 0;
            }
        }
        break;
    default:
        break;
    }
    return ret;
}