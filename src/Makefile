# Makefile for splitfast.c
# Tue 26 Mar 2019 09:21:21 AM CET
# Johan.Nylander@{nrm|nbis}.se

CC     = gcc
GDB    = gdb
CFLAGS = -Wall -O3
SRC    = splitfast.c
OBJ    = $(SRC:%.c=%.o)
PROG   = splitfast
RM     = rm -f

.PHONY: all debug clean

all: $(PROG)

$(OBJ): $(SRC)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

debug: CFLAGS += -g

debug: $(PROG)
	$(GDB) ./$(PROG)

clean:
	@ $(RM) $(OBJ) $(PROG)


