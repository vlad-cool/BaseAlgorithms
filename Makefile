CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
SOURCES = $(wildcard *.cpp)
TARGETS = $(SOURCES:.cpp=)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)