#include <iostream>
// #include <cmath>
#include <fstream>
// #include <cstdio>
#include <string>
#include <vector>
// #include <sstream>
#include <queue>
#include <list>

#include "Scheduler.h"
#include "types.h"
#include "pump.h"

using std::cout;
using std::endl;
using std::printf;
using std::string;

#define DEBUG_SCHED

int main(int argv, char **argc)
{
    if (argv != 2)
    {
        cout << "Please supply a csv file." << endl;
        return 1;
    }
    std::string file = argc[1];
    std::ifstream fin;
    fin.open(file);

    if (!fin)
    {
        std::cerr << "Cannot open file!" << endl;
        return 1;
    }
    std::vector<proc_data_t> proc_store;
    std::string line;
    // Figure out how long the file is for reserving vector. Avoids memory reallocation/copying when size exceeded.
    fin.seekg(0, fin.end);
    int len = fin.tellg() / 8;
    fin.seekg(0, fin.beg);
    cout << "file len: " << len << endl;
    proc_store.reserve(len + 10); // some extra just in case
                                  //
    // Read file and store data in vector
    while (std::getline(fin, line))
    {
        proc_data_t pdt;
        std::sscanf(line.c_str(),
                    "%i,%i,%i,%i",
                    &pdt.pid,
                    &pdt.arrival_time,
                    &pdt.burst_time,
                    &pdt.priority);
        proc_store.push_back(pdt);
    }
#ifdef DEBUG_SCHED
    // For debugging
    for (const proc_data_t &pdt : proc_store)
    {
        cout << "PID: " << pdt.pid
             << ", Arrival Time: " << pdt.arrival_time
             << ", Burst Time: " << pdt.burst_time
             << ", Priority: " << pdt.priority << endl;
    }
#endif
    fin.close();

    // std::vector<proc_data_t> sorted = lazysort_vec(proc_store);
    proc_store = lazysort_vec(proc_store);
    // Data has been sorted by time
#ifdef DEBUG_SCHED
    for (auto &pdt : proc_store)
    {

        cout << "PID: " << pdt.pid
             << ", Arrival Time: " << pdt.arrival_time
             << ", Burst Time: " << pdt.burst_time
             << ", Priority: " << pdt.priority << endl;
    }

    cout << proc_store.empty() << endl;
    cout << "========================" << endl;
    cout << "BEGIN SCHEDULER" << endl;
#endif
    scheduler_fcfs(proc_store);
    scheduler_sjfp(proc_store);
    return 0;
}

void scheduler_fcfs(const std::vector<proc_data_t> &proc_store)
{
    std::queue<proc_data_t> que;
    std::vector<proc_data_t>::const_iterator iter = proc_store.begin();
    std::vector<proc_data_t>::const_iterator iter_end = proc_store.end() - 1;

    ProcessPump pump(proc_store);
    int tick = 0;
    int waiting = 0;
    int n_pump = 0;
    do
    {
        n_pump = pump.check();
        if (n_pump > 0)
        {
            auto items = pump.retrieveProcesses();
            while (!items.empty())
            {
                que.push(items.front());
                items.pop();
            }
        }
        // There are processes waiting
        if (que.size() > 1)
        {
            waiting += (que.size() - 1);
        }
        // Let process do "work"
        int *cd = &que.front().burst_time;
        (*cd)--; // The "work"

        // Process has done all its work so remove it from queue
        if (*cd == 0)
        {
            cd = nullptr;
            que.pop();
        }

        pump.advance();
        ++tick;

        // Nothing left in queue and no more processes arriving
        if (que.empty() && n_pump == -1)
        {
            break;
        }
    } while (true);

    double processes = proc_store.size();
    double time = tick;
    bench_result_t results = {
        processes,
        static_cast<double>(waiting),
        time,
        (waiting + tick) / processes,
        waiting / processes,
        processes / tick};

    bench_result_t expected = {0.0, 0.0, 0.0, 1098.400, 1075.100, 0.043};

    benchmark_results(results, expected);
#ifdef DEBUG_SCHED
    test_fcfs_queue(que);
#endif
    // print test
}

void scheduler_sjfp(const std::vector<proc_data_t> &proc_store)
{
    std::list<proc_data_t> que;

    ProcessPump pump(proc_store);
    int tick = 0;
    int waiting = 0;
    int n_pump = 0;
    do
    {
        n_pump = pump.check();
        if (n_pump > 0)
        {
            auto items = pump.retrieveProcesses();
            while (!items.empty())
            {
                int new_burst = items.front().burst_time;
                bool found = 0; // is there any place we could insert an item?
                for (auto iter = que.begin(); iter != que.end(); ++iter)
                {
                    if (new_burst < iter->burst_time)
                    {
                        que.insert(iter, items.front());
                        found = true;
                        break;
                    }
                }
                if (!found)
                    que.push_back(items.front());
                items.pop();
            }
        }
        // There are processes waiting
        if (que.size() > 1)
        {
            waiting += (que.size() - 1);
        }
        // Let process do "work"
        int *cd = &que.front().burst_time;
        (*cd)--; // The "work"

        // Process has done all its work so remove it from queue
        if (*cd == 0)
        {
            cd = nullptr;
            que.erase(que.begin());
        }

        pump.advance();
        ++tick;

        // Nothing left in queue and no more processes arriving
        if (que.empty() && n_pump == -1)
        {
            break;
        }
    } while (true);

    double processes = proc_store.size();
    double time = tick;
    bench_result_t results = {
        processes,
        static_cast<double>(waiting),
        time,
        (waiting + tick) / processes,
        waiting / processes,
        processes / tick};

    // --- SJFP ---
    // Average Turnaround Time: 692.190
    // Average Waiting Time: 668.890
    // Throughput: 0.043
    bench_result_t expected = {0.0, 0.0, 0.0, 692.190, 668.890, 0.043};

    benchmark_results(results, expected);
    // test_sjfp
    // print test
}
