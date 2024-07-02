#include "debug.h"

using std::cout;
using std::endl;

void test_fcfs_queue(const std::queue<proc_data_t> &q){
    cout << "BEGIN: test_fcfs_queue" << endl 
    << "PURPOSE: Check if elements are present in queue" << endl;

    std::queue<proc_data_t> copy(q) ;
      while (!copy.empty()) {
        cout << "PID: " << copy.front().pid
             << ", Arrival Time: " << copy.front().arrival_time
             << ", Burst Time: " << copy.front().burst_time
             << ", Priority: " << copy.front().priority << endl;
      copy.pop();
   }
}