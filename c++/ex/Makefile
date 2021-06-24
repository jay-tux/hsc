CC=g++
MAKE=make
CCARGS=-Wall -Wextra -pedantic -g -I ../inc/ -std=c++17 -MMD
LDARGS=-L../lib/ -l hsc++ -Wl,--no-undefined
EXAMPLES=list maybe either

all: ../lib/libhsc++.so $(EXAMPLES:%=bin/%)

clean:
	rm -f bin/*

../lib/libhsc++.so: $(OBJS)
	$(MAKE) -c ..

-include $(EXAMPLES:%=bin/%.d)
bin/%: src/%.cpp Makefile ../lib/libhsc++.so
	$(CC) $(CCARGS) $(LDARGS) $< $(LDARGS) -o $@

.PHONY: all examples tests runtests clean empty
