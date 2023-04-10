#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * binary_to_uint - Converting binary number to unsigned int.
 * @b: A pointer to a string of 0 and 1 chars.
 *
 * Return: when b is NULL  0 or 1 - 0.
 *         Otherwise - the converted number.
 */

unsigned int binary_to_uint(const char *b)
{
    if (b == NULL)
        return 0;

    size_t len = strlen(b);
    unsigned int result = 0;

    for (size_t i = 0; i < len; i++)
    {
        char c = b[i];
        if (c != '0' && c != '1')
            return 0;

        result = result << 1;
        if (c == '1')
            result = result | 1;
    }

    return result;
}
