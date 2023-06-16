#include "lists.h"

/**
 * free_dlistint - frees a dlistint_t list.
 * @head: pointer to the head of the list.
 **/
void free_dlistint(dlistint_t *head)
{
	dlistint_t *current;

	for (current = head; current != NULL; current = head)
	{
		head = head->next;
		free(current);
	}
}
