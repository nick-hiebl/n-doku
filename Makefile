CC=gcc
CFLAGS=-Wall -Werror

converter: converter.c
	$(CC) -o converter converter.c $(CFLAGS)

clean:
	rm converter
