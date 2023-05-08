#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * read_textfile - reads a text file and prints it to standard output
 * @filename: the name of the file to read
 * @letters: the number of letters to read and print
 *
 * Return: the number of letters printed to standard output,
 * or 0 if the operation fails.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	ssize_t file_desc, num_read, num_written;
	char *buf;

	buf = malloc(letters);
	if (buf == NULL)
		return (0);

	if (filename == NULL)
		return (0);

	file_desc = open(filename, O_RDONLY);

	if (file_desc == -1)
	{
		free(buf);
		return (0);
	}

	num_read = read(file_desc, buf, letters);

	num_written = write(STDOUT_FILENO, buf, num_read);

	close(file_desc);

	return (num_written);
}
