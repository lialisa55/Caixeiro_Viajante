CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -fsanitize=address
OBJS = da_good_shit.c lista.c matriz.c
DEPS = lista.h matriz.h

all: $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) -o asw
run:
	./programa
clean:
	rm *.o programa
