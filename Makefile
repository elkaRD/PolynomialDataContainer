C=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -std=c++11
LDFLAGS=
LDLIBS= -lm

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: poly
debug: CPPFLAGS+=-g
debug: LDFLAGS+=-g
debug: wielo

poly: $(OBJS)
	$(CXX) $(LDFLAGS)  $(OBJS) -o poly  $(LDLIBS) 

main.o: main.cpp Polynomial.h
Polynomial.o: Polynomial.h
Examples.o: Examples.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) poly
