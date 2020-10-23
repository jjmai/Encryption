CFLAGS = -Wall -std=c99
CC = clang $(CFLAGS)

all		:	encode 

encode		:	encode.o trie.o io.o
		$(CC) -o encode encode.o trie.o io.o -lm -g

encode.o	:	encode.c
		$(CC) -c encode.c

trie.o		:	trie.c
		$(CC) -c trie.c

io.o		:	io.c
		$(CC) -c io.c

clean		:
		rm -rf *.o encode infer-out

format		:
		clang-format -i -style=file *.c *.h
