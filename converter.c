#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024

#define STDOUT 1

#define FALSE 0
#define TRUE !FALSE

// Convert a file given in plaintext format into a binary file
void convert_to_binary(char *filename);

// Convert a file given in binary format into a plaintext file
void convert_to_plaintext(char *filename);

// Display error output when a file cannot be opened
void error_loading_file(char *filename);

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Correct usage: %s <flag> <filename>\n"
            "\tUse -b to convert to binary format\n"
            "\tUse -t to convert to plaintext format\n",
            argv[0]);

        exit(EXIT_FAILURE);
    }

    int to_binary = !strcmp(argv[1], "-b");
    int to_plaintext = !strcmp(argv[1], "-t");

    if (!to_binary && !to_plaintext) {
        fprintf(stderr, "Must choose an appropriate flag.\n"
            "%s is an invalid flag.\n"
            "\tUse -b to convert to binary format\n"
            "\tUse -t to convert to plaintext format\n", argv[1]);

        exit(EXIT_FAILURE);
    }

    if (to_binary) {
        convert_to_binary(argv[2]);
    } else {
        convert_to_plaintext(argv[2]);
    }

    return EXIT_SUCCESS;
}

void convert_to_binary(char *filename) {
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        error_loading_file(filename);
    }

    int m = -1, n = -1;
    fscanf(f, "%d %d", &m, &n);

    if (m <= 0 || n <= 0) {
        fprintf(stderr,
            "Error loading file: m, n >= 0 in valid file.\n");
        fclose(f);

        exit(EXIT_FAILURE);
    }

    int buffer[BUFSIZE];
    buffer[0] = m;
    buffer[1] = n;
    write(STDOUT, buffer, sizeof(int) * 2);

    int i = 0, index = 0;
    while (i < m * m * n * n) {
        fscanf(f, "%d", &(buffer[index]));
        i++;
        index++;
        if (index == BUFSIZE) {
            // Buffer totally filled, so write buffer to output
            write(STDOUT, buffer, sizeof(int) * index);
            index = 0;
        }
    }
    if (index > 0) {
        // Write remaining buffer contents out
        write(STDOUT, buffer, sizeof(int) * index);
    }

    fclose(f);
}

void convert_to_plaintext(char *filename) {
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        error_loading_file(filename);
    }

    int buffer[BUFSIZE];
    int num_read = read(fd, buffer, BUFSIZE);

    int m = buffer[0];
    int n = buffer[1];

    printf("%d %d\n", m, n);

    // Start initially after m, n
    int index = 2;
    int i = 0;
    while (i < m * m * n * n && num_read) {
        // Out of data in current buffer, read in more
        if (index == num_read) {
            num_read = read(fd, buffer, BUFSIZE);
            index = 0;
            continue;
        }

        i++;
        if (i % (m * n)) {
            printf("%d ", buffer[index]);
        } else {
            printf("%d\n", buffer[index]);
        }
        index++;
    }

    close(fd);
}

void error_loading_file(char *filename) {
    fprintf(stderr, "File %s could not be opened.\n", filename);

    exit(EXIT_FAILURE);
}
