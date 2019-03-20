CC=g++
CFLAGS=-I./network/normal
DEPS = network/normal/net_normal_client.h network/normal/net_normal_server.h \
	   network/select/net_select_client.h network/select/net_select_server.h \
	   network/poll/net_poll_client.h network/poll/net_poll_server.h \
	   network/epoll/net_epoll_client.h network/epoll/net_epoll_server.h

main: network/main.o
	$(CC) -g -o main network/main.o  -lpthread

network/main.o: network/main.cpp $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

clean:
	rm -rf *.o *.c~ *.c~~ *.c~~ *.h~ *.h~~ main network/main.o