# Makefile TP Flex et Bison
CC=gcc
CFLAGS=-Wall
LDFLAGS=-ll
PARSERFLAGS= -d
LEXERFLAGS=
EXEC=expr_arith
PARSER=$(EXEC)
ANLEX=$(EXEC)
#all: $(EXEC) clean
$(EXEC): $(PARSER).o  $(ANLEX).yy.o
	$(CC) -o $@ $^ $(LDFLAGS)
$(PARSER).c $(PARSER).h: $(PARSER).y
	bison $(PARSERFLAGS) -o $(PARSER).c $(PARSER).y
$(ANLEX).yy.c: $(ANLEX).lex
	flex $(LEXERFLAGS) -o $(ANLEX).yy.c $(ANLEX).lex
$(PARSER).o: $(PARSER).c $(PARSER).h
	$(CC) -o $(PARSER).o -c $(PARSER).c $(CFLAGS)
$(ANLEX).yy.o: $(ANLEX).yy.c $(PARSER).h
	$(CC) -o $(ANLEX).yy.o -c $(ANLEX).yy.c $(CFLAGS)

table: $(PARSER).y
	bison -v $(PARSER).y
automaton: $(PARSER).y
	bison -g $(PARSER).y
show_automaton: $(PARSER).gv
	xdot $(PARSER).gv
counterexample: $(PARSER).y
	bison -Wcex $(PARSER).y

clean:
	rm -f $(ANLEX).yy.* $(EXEC).[och] $(PARSER).[och] $(PARSER).tab.c $(EXEC)
