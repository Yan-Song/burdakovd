G=g++ -g

all: server

clean:
	rm -f *.o server *~ *.bin

.PHONY: clean run test

server: table.o socket.o server.o fields.o grammar.o
	$G table.o socket.o server.o fields.o grammar.o -o server

test.bin: test.o table.o socket.o fields.o grammar.o
	$G table.o socket.o test.o fields.o grammar.o -o test.bin

table.o: table.cpp table.hpp fields.hpp macro.hpp exceptions.hpp
	$G -c table.cpp -o table.o

socket.o: socket.cpp socket.hpp exceptions.hpp
	$G -c socket.cpp -o socket.o

fields.o: fields.cpp fields.hpp exceptions.hpp
	$G -c fields.cpp -o fields.o

grammar.o: grammar.cpp grammar.hpp macro.hpp exceptions.hpp
	$G -c grammar.cpp -o grammar.o

server.o: server.cpp table.hpp socket.hpp fields.hpp exceptions.hpp grammar.hpp macro.hpp
	$G -c server.cpp -o server.o

test.o: test.cpp table.hpp macro.hpp fields.hpp socket.hpp exceptions.hpp grammar.hpp
	$G -c test.cpp -o test.o

run: server
	exec ./server

test: test.bin
	exec ./test.bin
