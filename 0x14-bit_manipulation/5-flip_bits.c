#include "main.h"

/**
 * flip_bits - calculates the number of bits that need to be flipped
 * to convert one number to another.
 *
 * @num1: the first number.
 * @num2: the second number.
 *
 * Return: the number of bits that need to be flipped.
 */
unsigned int flip_bits(unsigned long int num1, unsigned long int num2)
{
	unsigned long int xor_val = num1 ^ num2, bit_count = 0;

	while (xor_val > 0)
	{
		bit_count += (xor_val & 1);
		xor_val >>= 1;
	}

	return (bit_count);
}
