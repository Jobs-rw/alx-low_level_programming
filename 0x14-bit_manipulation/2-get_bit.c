#include "main.h"

/**
 * get_bit - Gets the value of a bit at a given index.
 * @num: The number containing the bit.
 * @index: The index to get the value at - indices start at 0.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - The value of the bit at index.
 */
int get_bit(unsigned long int num, unsigned int index)
{
	if (index >= (sizeof(unsigned long int) * 8))
		return (-1);

	if ((num & (1ul << index)) == 0)
		return (0);

	return (1);
}
