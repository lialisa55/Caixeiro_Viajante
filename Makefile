all: fila.o item.o main.o
	gcc fila.o item.o coisa.o -o programa
run: programa
	./programa
fila.o: fila.c
	gcc fila.c -c
item.o: item.c
	gcc item.c -c
main.o:
	gcc coisa.c -c 
clean:
	rm *.o
