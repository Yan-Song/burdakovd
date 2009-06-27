G=g++ -g

all: server

clean:
	rm -f *.o server *~ *.bin

.PHONY: clean run test

server: table.o socket.o server.o fields.o grammar.o formatter.o
	$G table.o socket.o server.o fields.o grammar.o formatter.o -o server

test.bin: test.o table.o socket.o fields.o grammar.o formatter.o
	$G table.o socket.o test.o fields.o grammar.o formatter.o -o test.bin

table.o: table.cpp table.hpp fields.hpp macro.hpp exceptions.hpp
	$G -c table.cpp -o table.o

formatter.o: formatter.cpp formatter.hpp grammar.hpp macro.hpp
	$G -c formatter.cpp -o formatter.o

socket.o: socket.cpp socket.hpp exceptions.hpp macro.hpp
	$G -c socket.cpp -o socket.o

fields.o: fields.cpp fields.hpp exceptions.hpp
	$G -c fields.cpp -o fields.o

grammar.o: grammar.cpp grammar.hpp macro.hpp exceptions.hpp fields.hpp table.hpp
	$G -c grammar.cpp -o grammar.o

server.o: server.cpp table.hpp socket.hpp fields.hpp exceptions.hpp grammar.hpp macro.hpp formatter.hpp
	$G -c server.cpp -o server.o

test.o: test.cpp table.hpp macro.hpp fields.hpp socket.hpp exceptions.hpp grammar.hpp formatter.hpp
	$G -c test.cpp -o test.o

run: server
	./server

test: test.bin
	./test.bin
