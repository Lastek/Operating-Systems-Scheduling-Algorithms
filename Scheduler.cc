#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>

#include "Scheduler.h"
#include "types.h"
#include "pump.h"

using std::cout;
using std::endl;
using std::printf;
using std::string;

void scheduler_fcfs(const std::vector<proc_data_t> &proc_store);
/**
 * Usage: Call check() then retrieveProcesses() if check returned a number > 0
 *  Call advance() to clear the process queue and advance to next timestep
 */
void benchmark_results(bench_result_t &actual, bench_result_t &expected)
{
    // proc_data_t pdt;

    string s;
    expected.avg_turn = 4.200;
    expected.avg_wait = 1.200;
    expected.thru = 0.333;
    bench_result_t *a;
    bench_result_t *e;
    a = &actual;
    e = &expected;

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
    // if()
}
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

    for (const proc_data_t &pdt : proc_store)
    {
        cout << "PID: " << pdt.pid
             << ", Arrival Time: " << pdt.arrival_time
             << ", Burst Time: " << pdt.burst_time
             << ", Priority: " << pdt.priority << endl;
    }
    fin.close();

    // std::vector<proc_data_t> sorted = lazysort_vec(proc_store);
    proc_store = lazysort_vec(proc_store);
    // Data has been sorted by time

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
    scheduler_fcfs(proc_store);
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
        tick++;
        
        // Nothing left in queue and no more processes arriving
        if (que.empty() && n_pump == -1)
        {
            break;
        }
    } while (true);
    double w = waiting;
    double p = proc_store.size();
    double t = tick;
    cout << "wait time: " << w << endl
         << "ticks:     " << t << endl
         << "avg wait time:  " << w / p << endl
         << "avg turnaround: " << (w + t) / p << endl
         << "throughput:     " << (p / t) << endl;
    test_fcfs_queue(que);
    // print test
}
