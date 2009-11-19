PROG=./RayTracingDemo

CPP=g++

OPTIMIZATIONFLAGS= -O3 -funit-at-a-time -funswitch-loops -Wdisabled-optimization

WARNINGFLAGS= -W -Wall -Wextra -pedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy \
	-Wnon-virtual-dtor -Wold-style-cast -Wconversion -Wsign-conversion -Winit-self \
	-Werror 

COMMONFLAGS= $(OPTIMIZATIONFLAGS) $(WARNINGFLAGS)
CPPFLAGS= $(COMMONFLAGS) -I/usr/include/SDL -I.. -I../RayTracing -DTR1_PREFIX
LINKFLAGS= $(COMMONFLAGS) -lSDL -lpthread 

SOURCES := $(wildcard *.cpp) $(wildcard ../sdlapplication/*.cpp) $(wildcard ../RayTracing/*.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPS := $(patsubst %.o, %.d, $(OBJS))

.PHONY: all clean

all: $(PROG)

run: $(PROG)
	$(PROG)
 
$(PROG): $(OBJS) $(DEPS)
	$(CPP) $(LINKFLAGS) $(OBJS) -o $@
 
%.o: %.cpp %.d
	$(CPP) $(CPPFLAGS) -c $< -o $@
 
%.d: %.cpp Makefile
	@set -e; $(CPP) -M $(CPPFLAGS) $< | \
		sed -e 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
		[ -s $@ ] || rm -f $@
	@echo create $@
 
clean:
	rm -f $(PROG) $(OBJS) $(DEPS)
 
-include $(DEPS)
