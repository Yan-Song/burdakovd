all: server

clean:
	rm -f *.o server *~ *.bin

.PHONY: clean run test

server: table.o socket.o server.o fields.o
	g++ table.o socket.o server.o fields.o -o server

test.bin: test.o table.o socket.o fields.o
	g++ table.o socket.o test.o fields.o -o test.bin

table.o: table.cpp table.hpp fields.hpp macro.hpp
	g++ -c table.cpp -o table.o

socket.o: socket.cpp socket.hpp
	g++ -c socket.cpp -o socket.o

fields.o: fields.cpp fields.hpp exceptions.hpp
	g++ -c fields.cpp -o fields.o

server.o: server.cpp table.hpp socket.hpp fields.hpp
	g++ -c server.cpp -o server.o

test.o: test.cpp table.hpp macro.hpp fields.hpp socket.hpp exceptions.hpp
	g++ -c test.cpp -o test.o

run: server
	./server

test: test.bin
	./test.bin