# Makefile TP Flex

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall -lfl
EXEC=ex1

# all: $(EXEC) clean

$(EXEC): lex.yy.o
	$(CC) -o $@ $^ $(LDFLAGS)

lex.yy.c: $(EXEC).lex
	  flex $(EXEC).lex

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f lex.yy.*
