#include <vector>
#include <queue>
#include "types.h"

class ProcessPump
{
private:
    std::vector<proc_data_t> processes; 
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
    /// @brief Constructor
    /// @param sorted_vec sorted vector of processes
    ProcessPump(const std::vector<proc_data_t> &sorted_vec)
    {
        processes = sorted_vec; // Make a copy
        iter = processes.cbegin();
        iter_end = processes.cend() - 1;
        time = 0;
    }
    
    /// @brief ### Are there processes ready?
    /// @returns -1 if processes have been exhausted |
    /// @returns 0 if nothing available |
    /// @returns > 0 if there are processes waititing 
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
    /// @brief Return processes waiting to be scheduled
    /// @return std::queue<proc_data_t>
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