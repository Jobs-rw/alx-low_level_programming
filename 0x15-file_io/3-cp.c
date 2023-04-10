#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
        exit(97);
    }

    int file_from_fd = open(argv[1], O_RDONLY);
    if (file_from_fd == -1) {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    int file_to_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_to_fd == -1) {
        dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
        exit(99);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(file_from_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(file_to_fd, buffer, bytes_read) != bytes_read) {
            dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
            exit(99);
        }
    }
    if (bytes_read == -1) {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    if (close(file_from_fd) == -1) {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_from_fd);
        exit(100);
    }

    if (close(file_to_fd) == -1) {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_to_fd);
        exit(100);
    }

    return 0;
}
