CC=g++
#CFLAGS=-I./network/normal
# DEPS = simple_thread.h thread_incr.h thread_incr_mutex.h thread_call_classFun.h prod_no_condvar.h prod_condvar.h postFun2Thread.h
DEPS = *.h

#main: main.o
#	$(CC) -g -o main main.o -lpthread
#
#main.o: main.cpp $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

main: main.cpp $(DEPS)
	$(CC) -g -o main main.cpp -lpthread

clean:
	rm -rf *.o *.c~ *.c~~ *.c~~ *.h~ *.h~~ main