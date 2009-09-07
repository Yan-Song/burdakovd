sdlappdir=../sdlapplication
sdlapph=$(sdlappdir)/sdlapplication.h
sdlappcpp=$(sdlappdir)/sdlapplication.cpp
sdlappobj=$(sdlappdir)/sdlapplication.o

# sdl-config
cflags= -I$(sdlappdir) -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
ldflags= -lSDL 
cpp=g++ $(cflags)
ld=g++ $(ldflags)


all: life

life: main.o life.o $(sdlappobj)
	$(ld) main.o life.o $(sdlappobj) -o life

life.o: life.cpp life.h $(sdlapph)
	$(cpp) -c life.cpp -o life.o

main.o: main.cpp life.h $(sdlapph)
	$(cpp) -c main.cpp -o main.o

$(sdlappobj): $(sdlappcpp) $(sdlapph)
	$(cpp) -c $(sdlappcpp) -o $(sdlappobj)

run: life
	./life

clean:
	rm -f life $(sdlappobj) *.o



