#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * append_text_to_file - Appends text to a file.
 *
 * @filename: Name of the file to append to.
 * @text_content: The text to append to the file.
 *
 * Return: 1 on success, or -1 on failure.
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int i, file;

	if (filename == NULL)
		return (-1);

	if (text_content == NULL)
		text_content = "";

	for (i = 0; text_content[i] != '\0'; i++)
		;

	file = open(filename, O_WRONLY | O_APPEND);

	if (file == -1)
		return (-1);

	if (write(file, text_content, i) == -1)
		return (-1);

	close(file);

	return (1);
}
