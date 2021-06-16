CC=g++
MAKE=make
CCARGS=-Wall -Wextra -pedantic -g -c -fPIC -MMD -I ./inc/ -std=c++17
LDARGS=-shared
SRCS=$(shell find src/ -name '*.cpp')
OBJS=$(SRCS:src/%.cpp=obj/%.o)
DEPS=$(OBJS:.o=.d)
-include $(DEPS)

all: lib/libhsc++.so

empty:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)

examples:
	$(MAKE) -C ex/

tests:
	$(MAKE) -C test/

runtests:
	$(MAKE) tests
	export LD_LIBRARY_PATH=$(PWD)/lib/; test/bin/all

clean:
	rm -f lib/*
	rm -f obj/*

install: lib/libhsc++.so
	sudo cp lib/libhsc++.so /usr/lib
	if [ ! -d /usr/include/hsc/ ]; then sudo mkdir /usr/include/hsc/; fi
	sudo cp inc/* /usr/include/hsc/

lib/libhsc++.so: $(OBJS)
	$(CC) $(OBJS) $(LDARGS) -o $@

obj/%.o: src/%.cpp Makefile
	$(CC) $(CCARGS) $< -o $@

.PHONY: all examples tests runtests clean empty
