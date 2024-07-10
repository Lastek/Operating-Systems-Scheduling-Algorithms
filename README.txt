README
======

This package includes the following files.

|-- Scheduler.cc [Contains the main entry and scheduler algorithms]
|-- Scheduler.h [header]
|-- pump.h [ProcessorPump class implementation] 
|-- util.cc [Utilities]
|-- util.h [Header]
|-- types.h [common type definitions]
|-- Makefile [Used for compilation]
|-- README.txt [This file]

To compile:
    make

To run:
    ./Scheduler file.csv 

Note: 
    make DEUBG_SCHED=1 requires debug.cc & debug.h which are not included in this package.