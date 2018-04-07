C=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -std=c++11
LDFLAGS=
LDLIBS= -lm

SRCS=main.cpp Polynomial.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: wielo
debug: CPPFLAGS+=-g
debug: LDFLAGS+=-g
debug: wielo

wielo: $(OBJS)
	$(CXX) $(LDFLAGS)  $(OBJS) -o wielo  $(LDLIBS) 

main.o: main.cpp Polynomial.h

Polynomial.o: Polynomial.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) wielo
