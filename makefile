CC = gcc
CFLAGS = -Wall -g -Iobj -Isrc 

LDFLAGS = -lfl 

PARSER = tpc-2025-2026
LEXER = projlexic

bin/tpcas: obj/lex.yy.o obj/$(PARSER).tab.o obj/tree.o
	mkdir -p bin
	$(CC) -o $@ $^ $(LDFLAGS)

obj/tree.o: src/tree.c src/tree.h
	mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(PARSER).tab.c obj/$(PARSER).tab.h: src/$(PARSER).y
	mkdir -p obj
	bison -d -o obj/$(PARSER).tab.c $<

obj/$(PARSER).tab.o: obj/$(PARSER).tab.c src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/lex.yy.c: src/$(LEXER).lex obj/$(PARSER).tab.h
	mkdir -p obj
	flex -o $@ $<

obj/lex.yy.o: obj/lex.yy.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf obj bin