CC=g++
MAKE=make
CCARGS=-Wall -Wextra -pedantic -g -I ../inc/ -std=c++17
LDARGS=-L../lib/ -l hsc++
EXAMPLES=list maybe

all: ../lib/libhsc++.so $(EXAMPLES:%=bin/%)

clean:
	rm -f bin/*

../lib/libhsc++.so: $(OBJS)
	$(MAKE) -c ..

bin/%: src/%.cpp Makefile ../lib/libhsc++.so
	$(CC) $(CCARGS) $(LDARGS) $< -o $@

.PHONY: all examples tests runtests clean empty
