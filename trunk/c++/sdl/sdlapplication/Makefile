CPP=g++
CPPFLAGS= -W -Wall -I/usr/include/SDL
LINKFLAGS= -lSDL -lpthread 

SOURCES := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPS := $(patsubst %.o,%.d,$(OBJS))

.PHONY: all clean

all: $(OBJS)
 
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
