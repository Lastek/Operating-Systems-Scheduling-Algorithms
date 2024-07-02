#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "Scheduler.h"
#include <algorithm>

using std::cout;
using std::endl;
using std::printf;
using std::string;

void scheduler_fcfs(const std::vector<proc_data_t> &proc_store);
std::vector<proc_data_t> lazysort_vec(const std::vector<proc_data_t> &v);
/**
 * Usage: Call check() then retrieveProcesses() if check returned a number > 0
 *  Call advance() to clear the process queue and advance to next timestep
 */
class ProcessPump
{
private:
    std::vector<proc_data_t> processes; // the complete file
    std::vector<proc_data_t>::const_iterator iter;
    std::vector<proc_data_t>::const_iterator iter_end;
    std::queue<proc_data_t> que; // to do
    int offset = 0;
    int time = 0;
    int loc = 0;
    int list_exhausted = 0;

    // check what processes have come in at this time
    //  add them to the queue
    int queueProcesses()
    {
        // Recursion guard clause
        if (list_exhausted)
            return 0; // could return -1

        if (time == (*iter).arrival_time)
        {
            // Last element
            if (iter == iter_end)
            {
                list_exhausted = 1;
            }
            que.push(*iter); // Push an item to the queue
            ++iter;
            queueProcesses();
        }
        return que.size();
    }

public:
    ProcessPump(const std::vector<proc_data_t> &sorted_vec)
    {
        processes = sorted_vec; // Make a copy
        iter = processes.cbegin();
        iter_end = processes.cend() - 1;
        time = 0;
    }
    ~ProcessPump()
    {
    }

    // ### Are there processes ready?
    // -1 if processes have been exhausted
    // 0 if nothing available at this time
    // int > 0 if something was queued up
    //
    int check()
    {
        if (list_exhausted == 1)
            return -1;
        else
        {
            int check = queueProcesses();
            return check;
        }
    }
    std::queue<proc_data_t> retrieveProcesses()
    {
        return que;
    }

    // Call once per tick
    // This will clear the queue
    void advance()
    {
        if (list_exhausted)
            return;
        while (!que.empty())
        {
            que.pop();
        }
        time++;
    }
    
    // ProcessPump operator++(){
    //     advance();
    // }
};
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

int main()
{
    std::ifstream fin;
    fin.open("sample_data.csv");

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

    int tick = 0;
    tick = 1;
    cout << "ignore" << tick << endl;
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
    do
    {
        tick++;
        if (tick > 10)
        {
            cout << "Error" << endl;
            break;
        }
    } while (iter != proc_store.cend());
    test_fcfs_queue(que);
    // print test
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