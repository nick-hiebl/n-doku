CC=gcc
CFLAGS=-Wall -Werror

converter: converter.c
	$(CC) -o converter converter.c $(CFLAGS)

solver: solver.c
	$(CC) -o solver solver.c $(CFLAGS)

clean:
	rm converter
