#include <vector>
#include <queue>
#include "types.h"

class ProcessPump
{
private:
    std::vector<proc_data_t> processes; // the complete file
    std::vector<proc_data_t>::const_iterator iter;
    std::vector<proc_data_t>::const_iterator iter_end;
    std::queue<proc_data_t> que;
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
    // This will clear the queue and increment internal timer
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