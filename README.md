README
======
Builds with gcc tools in WSL 2 Ubuntu Jammy. Makefile included.
Will build with cmake.
Including vs2022 package as well.

To build with debugging:
- #define DEBUG_SCHED in Scheduler.h
- Pass -DDEBUG_SCHED=1 for make or =ON for cmake

This package includes implementations of three scheduling algorithms:
- FCFS: First Come First Serve
- SJF: Shortest Job First
- Priority: Highest priority job first

### Included files:
- Scheduler.cc [Contains the main entry and scheduler algorithms]
- Scheduler.h [header]
- pump.h [ProcessorPump class implementation] 
- util.cc [Utilities]
- util.h [Header]
- types.h [common type definitions]
- Makefile [Used for compilation]
- README.txt [This file]

#### Debugging:
- debug.h
- debug.cc

#### Misc files:
- quick.cc [Quicksort implementations. Not in use currently.]

### To compile:
make:
    make
cmake:
    cmake <path_to_sauce>

### Debugging:
make:
    make DEBUG_SCHED=1
cmake:
    cmake DEBUG_SCHED=ON <path_to_sauce>

### To run:
    ./Scheduler file.csv 

### Note: 
    make DEUBG_SCHED=1 requires debug.cc & debug.h which are not included in this package.
    
    csv file must be in the following format:
    <PID>,<Arrival_Time>,<Burst_Time>,<Priority [0-n] where n is lowest priority>
