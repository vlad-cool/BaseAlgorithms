CXX = g++
CXXFLAGS = -Wall -O3 -std=c++26
SOURCES = $(wildcard task*/*.cpp)
COMMON = $(wildcard common/*)
TARGETS = $(SOURCES:.cpp=)

all: $(TARGETS)

%: %.cpp $(COMMON)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)