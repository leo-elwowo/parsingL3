# Makefile TP Flex

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall -lfl -ly
FLEX=projlexic
BISON=exp-tpc
EXEC=analyseur

$(EXEC): lex.yy.o $(BISON).tab.o
	$(CC) -o $@ $^ $(LDFLAGS)

lex.yy.c: $(FLEX).lex
	flex $(FLEX).lex

$(BISON).tab.h: $(BISON).y
	bison -d $(BISON).y

$(BISON).tab.c: $(BISON).y
	bison -d $(BISON).y

%.o: %.c $(BISON).tab.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f lex.yy.*
	rm -f *.tab.*
	rm -f $(EXEC)
 