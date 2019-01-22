CC=g++
CFLAGS=-I./network/normal
DEPS = network/normal/net_normal_client.h network/normal/net_normal_server.h

main: network/main.o
	$(CC) -g -o main network/main.o  -lpthread

network/main.o: network/main.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf *.o *.c~ *.c~~ *.c~~ *.h~ *.h~~ main