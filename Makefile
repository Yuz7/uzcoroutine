
SOURCE := $(wildcard *.cpp)

objects := $(patsubst %.cpp,%.o,$(SOURCE))
objects += cocontext.o

#obj = test_init.o coctx.o

CFLAGS := -std=c++11 -g -Wall
CC := g++
CXXFLAGS := $(CFLAGS)

main : $(objects)
	$(CC) $(CXXFLAGS) -o $@ $^

.PHONY : clean
clean:
	rm -f *.o
