CC = gcc
CFLAGS = -Wall -g -Iobj -Isrc 

LDFLAGS = -lfl 

PARSER = tpc-2025-2026
LEXER = projlexic

BINARY = compiled

bin/tpcc: obj/lex.yy.o obj/$(PARSER).tab.o obj/tree.o obj/symb.o obj/sem.o obj/struct_info.o
	mkdir -p bin
	$(CC) -o $@ $^ $(LDFLAGS)

obj/tree.o: src/tree.c src/tree.h
	mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

obj/symb.o: src/symb.c src/symb.h
	mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

obj/sem.o: src/sem.c src/sem.h src/symb.h src/tree.h src/struct_info.h
	mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

obj/struct_info.o: src/struct_info.c src/struct_info.h src/tree.h
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
	rm -rf obj bin compiled _anonymous.*

test_asm: bin/tpcc
	./bin/tpcc < iftest.tpc
	nasm -f elf64 anonymous.asm
	ld -o $(BINARY) anonymous.o
	-./$(BINARY) ; echo "ret = $$?"
	
