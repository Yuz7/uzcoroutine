
objects = main.o uzcoroutine.o coctx.o cocontext.o

#obj = test_init.o coctx.o

main : $(objects)
	g++ -g -o main $(objects)

#test_init.o : coctx.h
main.o : uzcoroutine.h
uzcoroutine.o : uzcoroutine.h coctx.h
coctx.o : coctx.h
cocontext.o : cocontext.S
	as cocontext.S -o cocontext.o


.PHONY : clean
clean:
	rm -f *.o
