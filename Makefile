CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -fsanitize=address
OBJS = "main.c" list.c garfo.c
DEPS = list.h garfo.h

all: $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) -o asw
run:
	./programa
clean:
	rm *.o programa
