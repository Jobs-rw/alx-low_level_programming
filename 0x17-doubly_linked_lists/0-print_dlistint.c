#include "lists.h"

/**
 * print_dlistint - prints all the elements of a dlistint_t list.
 * @h: pointer to the list.
 * Return: number of nodes.
 **/
size_t print_dlistint(const dlistint_t *h)
{
	size_t cont = 0;

	for (const dlistint_t *node = h; node != NULL; node = node->next)
	{
		printf("%i\n", node->n);
		cont++;
	}

	return cont;
}
