#include "main.h"
#include <stdlib.h>

/**
 * binary_to_uint - Converts a binary number to an unsigned int.
 * @b: A pointer to a string of 0 and 1 chars.
 *
 * Return: If b is NULL or contains chars not 0 or 1 - 0.
 *         Otherwise - the converted number.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int binary_to_uint(const char *b)
{
    if (b == NULL) {
        return 0;
    }

    int len = strlen(b);
    unsigned int num = 0;

    for (int i = 0; i < len; i++) {
        if (b[i] == '0') {
            num += 0;
        } else if (b[i] == '1') {
            num += pow(2, len - i - 1);
        } else {
            return 0;
        }
    }

    return num;
}
