CC=g++
MAKE=make
CCARGS=-Wall -Wextra -pedantic -g -c -fPIC -MMD
LDARGS=-shared

SRCDIR=./src/
INCDIR=./inc/
OBJDIR=./obj/
LIBDIR=./lib/
EXDIR=./ex/
TESTDIR=./test/

all: $(LIBDIR)/libhsc++.so

examples:
	$(MAKE) -c $(EXDIR)

tests:
	$(MAKE) -c $(TESTDIR)

runtests:
	$(MAKE) tests
	$(TESTDIR)/bin/all

$(LIBDIR)/libhsc++.so: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDARGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile
	$(CC) $(CCARGS) $< -o $@
