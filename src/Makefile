# Makefile for splitfast.c
# Thu 3 sep 2020 23:39:31
# Johan.Nylander@{nrm|nbis}.se

CC     = gcc
GDB    = gdb
CFLAGS = -Wall -O3
SRC    = splitfast.c
OBJ    = $(SRC:%.c=%.o)
PROG   = splitfast
RM     = rm -f

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

.PHONY: all debug clean install uninstall

all: $(PROG)

$(OBJ): $(SRC)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

debug: CFLAGS += -g

debug: $(PROG)
	$(GDB) ./$(PROG)

install: $(PROG)
	install $(PROG) $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROG)

clean:
	@ $(RM) $(OBJ) $(PROG)


