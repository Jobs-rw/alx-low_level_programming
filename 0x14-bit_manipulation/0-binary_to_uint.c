#include "main.h"
#include <stdlib.h>

/**
 * binary_to_uint - Converting the binary number to an unsigned int.
 * @b: A pointer to a string of 0 and 1 chars.
 *
 * Return: If b is NULL or contains chars not 0 or 1 - 0.
 *         Otherwise - the converted number.
 */
unsigned int binary_to_uint(const char *b) {
  if (b == NULL) {
    return 0;
  }

  unsigned int result = 0;
  for (; *b != '\0'; b++) {
    if (*b != '0' && *b != '1') {
      return 0;
    }
    result = result * 2 + (*b - '0');
  }
  return result;
}
