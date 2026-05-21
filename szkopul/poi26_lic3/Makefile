CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2 -g -fsanitize=address,undefined -DLOCAL

# Użyj instrukcji 'make all' by zbudować wszystkie programy, lub 'make clean' by usunąć pliki wykonywalne.

debug: CXXFLAGS += -DDEBUG
debug: all

all: licsoc.e lic.e

licsoc.e: licsoc.cpp
	$(CXX) $(CXXFLAGS) -o licsoc.e licsoc.cpp

lic.e: solution.cpp
	$(CXX) $(CXXFLAGS) -o lic.e solution.cpp

clean:
	rm -f licsoc.e lic.e

