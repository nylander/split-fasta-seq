# Makefile for splitfast.c

CC     = gcc
GDB    = gdb
CFLAGS = -Wall -O2
SRC    = splitfast.c
OBJ    = $(SRC:%.c=%.o)
PROG   = splitfast
RM     = rm -f

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

.PHONY: all debug clean install uninstall

all: $(PROG)

$(OBJ): $(SRC) splitfast.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

debug: CFLAGS += -g

debug: $(PROG)
	$(GDB) ./$(PROG)

install: $(PROG)
	install $(PROG) $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROG)

test:
	./$(PROG) -m 40 -w 20 ../data/fasta.fas
	./$(PROG) -s ../data/longer.fas | grep '>'

clean:
	@ $(RM) $(OBJ) $(PROG)


