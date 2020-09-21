CFLAGS = -Wpedantic -Werror -Wall -Wextra -std=c99
CC = clang $(CFLAGS)

all		:	encode 

encode		:	encode.o
		%(CC) -o encode encode.o -lm -g

encode.o	:	encode.c
		%(CC) -c encode.c

clean		:
		rm -rf *.o encode infer-out

format		:
		clang-format -i -style=file *.c *.h
