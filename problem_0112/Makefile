CXX     := g++
CXXFLAGS := -Wall -Wextra -Wno-unused-parameter -fno-strict-aliasing -std=c++11 -g

all: solution

solution: solution.o
	$(CXX) $(CXXFLAGS) -o $@ solution.o

.cpp.o:
	${CXX} -c ${CXXFLAGS} $<

clean:
	rm -f solution *.o a.out

