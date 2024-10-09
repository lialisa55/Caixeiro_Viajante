CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -fsanitize=address
OBJS = main.c lista.c lista2D.c
DEPS = lista.h lista2D.h

all: $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) -o asw
run:
	./programa
clean:
	rm *.o programa