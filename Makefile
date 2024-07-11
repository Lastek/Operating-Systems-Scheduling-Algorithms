# C++ Makefile for project

CXX=g++
CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option
# CXXFLAGS=-g -O0

BASE_FILES=Scheduler.cc util.cc 
DEBUG_FILES=debug.cc
OUT_EXE = Scheduler 
HEADERS=Scheduler.h util.h pump.h types.h

ifdef DEBUG_SCHED
    FILES=$(BASE_FILES) $(DEBUG_FILES)
	HEADERS=$(HEADERS) debug.h
    CXXFLAGS += -DDEBUG_SCHED
else
    FILES=$(BASE_FILES)
endif

all: $(FILES)
	$(CXX) $(CXXFLAGS) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o $(OUT_EXE) *.zip
	
run:
	./Scheduler proc_data.csv

package:
	zip package.zip README.txt Makefile $(FILES) $(HEADERS)
