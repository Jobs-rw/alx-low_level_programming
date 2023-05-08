#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * create_file - creates a new file and writes text to it
 * @filename: the name of the new file to create
 * @text_content: the text to write to the new file
 *
 * Return: 1 on success, -1 on failure.
 */
int create_file(const char *filename, char *text_content)
{
	int i, file;

	if (filename == NULL)
		return (-1);

	if (text_content == NULL)
		text_content = "";

	for (i = 0; text_content[i] != '\0'; i++)
		;

	file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);

	if (file == -1)
		return (-1);

	if (write(file, text_content, i) == -1)
		return (-1);

	close(file);

	return (1);
}
