#include "main.h"

/**
 * binary_to_uint - converts a binary string to an unsigned int.
 * @binary_string: pointer to a string of 0 and 1 chars.
 *
 * Return: the converted number, or 0 if there is one
 * or more chars in the string
 * that is not 0 or 1 or if b is NULL.
 */
unsigned int binary_to_uint(const char *binary_string)
{
	unsigned int ihene = 0;

	if (!binary_string)
		return (0);

	while (*binary_string != '\0')
	{
		if (*binary_string == '0' || *binary_string == '1')
		{
			ihene <<= 1;
			ihene += (*binary_string - '0');
			binary_string++;
		}
		else
		{
			return (0);
		}
	}

	return (ihene);
}
