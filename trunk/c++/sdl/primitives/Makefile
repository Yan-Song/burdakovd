PROG=./primitives

CPP=g++
COMMONFLAGS= -O3 -funroll-loops
CPPFLAGS= $(COMMONFLAGS) -W -Wall -I/usr/include/SDL -I../sdlapplication 
LINKFLAGS= $(COMMONFLAGS) -lSDL -lpthread 

SOURCES := $(wildcard *.cpp) $(wildcard ../sdlapplication/*.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPS := $(patsubst %.o,%.d,$(OBJS))

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
