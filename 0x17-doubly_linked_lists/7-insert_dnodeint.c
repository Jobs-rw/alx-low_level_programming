#include "lists.h"

/**
 * insert_dnodeint_at_index - inserts a new node at a given position.
 * @h: pointer to a pointer to the head of the list.
 * @idx: index of the node where the new node should be inserted.
 * @n: value to be assigned to the new node.
 * Return: pointer to the inserted node or NULL if it failed.
 **/
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *aux_node = *h, *new_node;
	unsigned int cont;

	/* create node */
	new_node = malloc(sizeof(dlistint_t));
	if (new_node == NULL)
		return (NULL);
	new_node->n = n;

	/* border case for insert at the beginning */
	if (idx == 0)
	{
		new_node->prev = NULL;
		new_node->next = *h;
		if (*h != NULL)
			(*h)->prev = new_node;
		*h = new_node;
		return (*h);
	}

	/* search of position to insert */
	for (cont = 0; aux_node != NULL && cont < idx - 1; cont++)
		aux_node = aux_node->next;

	/* general case */
	if (cont == idx - 1 && aux_node != NULL)
	{
		new_node->prev = aux_node;
		new_node->next = aux_node->next;
		if (aux_node->next != NULL)
			aux_node->next->prev = new_node;
		aux_node->next = new_node;
		return (new_node);
	}

	free(new_node);
	return (NULL);
}
