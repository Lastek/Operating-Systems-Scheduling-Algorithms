# C++ Makefile for HW5
#
# Replace the LastName-FirstName in the package section with
# your actual first and last name.

CXX=g++
CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option

FILES=Scheduler.cc util.cc debug.cc 
OUT_EXE = Scheduler 

all: $(FILES)
	$(CXX) $(CXXFLAGS) -o $(OUT_EXE) $(FILES)
clean:
	rm -f *.o $(OUT_EXE) *.zip
run:
	 ./$(OUT_EXE) sample_data.csv
package:
	zip LastName-FirstName-HW5.zip README.txt Makefile Scheduler.cc
