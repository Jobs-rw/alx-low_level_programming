#include "lists.h"

/**
 * get_dnodeint_at_index - returns the nth node of a dlistint_t linked list.
 * @head: pointer to the head of the list.
 * @index: index of the node to retrieve.
 * Return: pointer to the nth node or NULL if it doesn't exist.
 **/
dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
	dlistint_t *node;

	for (node = head; node != NULL && index > 0; node = node->next, index--)
		;

	return node;
}

