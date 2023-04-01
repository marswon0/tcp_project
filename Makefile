all: server client

server: main_server.o server.o
	g++ main_server.o server.o -o server

client: main_client.o client.o
	g++ main_client.o client.o -o client

main_server.o: main_server.cpp
	g++ -c main_server.cpp

server.o: server.cpp server.h
	g++ -c server.cpp

main_client.o: main_client.cpp
	g++ -c main_client.cpp

client.o: client.cpp client.h
	g++ -c client.cpp

clean:
	rm -f *.o server client
