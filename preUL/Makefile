# Makefile for testing top tagging SFs in C++ with ROOT

CPP=g++
LD=g++

ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS =
LFLAGS =

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

SRC1= readScaleFactors.o test.o

%.o: %.cxx
	$(CPP) $(RCXX) -c $<

all: test

test: $(SRC1)
	$(LD) $(SRC1) $(RLXX) -o test
	@echo '-> test created!'

clean:
		@rm test
		@rm -f *~
		@rm -f *.o 
		@rm -f *.x
