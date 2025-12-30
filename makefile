CC = gcc
CFLAGS = -Wall -g -Iobj -Isrc
PARSER = tpc-2025-2026
LEXER = projlexer

bin/tpcas: obj/$(LEXER).o obj/$(PARSER).o obj/tree.o obj/module1.o # ...
	$(CC) -o $@ $^

obj/tree.o: src/tree.c src/tree.h
obj/module1.o: src/module1.c src/module1.h src/tree.h

obj/$(PARSER).o: obj/$(PARSER).c src/tree.h src/module2.h
obj/$(LEXER).o: obj/$(LEXER).c obj/$(PARSER).h
# ...

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(LEXER).c: src/$(LEXER).l obj/$(PARSER).h
	flex -o $@ $<

obj/$(PARSER).c obj/$(PARSER).h &: src/$(PARSER).y
	bison -d -o obj/$(PARSER).c $<

clean:
	rm -rf obj bin