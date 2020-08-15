
SOURCE := $(wildcard *.cpp)

objects := $(patsubst %.cpp,%.o,$(SOURCE))
objects += cocontext.o

#obj = test_init.o coctx.o

CFLAGS := -std=c++11 -g -Wall
CC := g++
CXXFLAGS := $(CFLAGS)

main : $(objects)
	$(CC) $(CXXFLAGS) -o $@ $^

#test_init.o : coctx.h
main.o : uzcoroutine.h
uzcoroutine.o : uzcoroutine.h coctx.h
coctx.o : coctx.h
cocontext.o : cocontext.S
	as cocontext.S -o cocontext.o


.PHONY : clean
clean:
	rm -f *.o
