#include "lists.h"

/**
 * add_dnodeint_end - adds a new node at the end of a dlistint_t list.
 * @head: pointer to a pointer to the head of the list.
 * @n: value to be assigned to the new node.
 * Return: address of the new element or NULL if it failed.
 **/
dlistint_t *add_dnodeint_end(dlistint_t **head, const int n)
{
	dlistint_t *new_node, *aux;

	new_node = malloc(sizeof(dlistint_t));
	if (new_node == NULL)
		return (NULL);

	new_node->n = n;
	new_node->next = NULL;

	if (*head)
	{
		aux = *head;
		for (; aux->next != NULL; aux = aux->next)
			;

		new_node->prev = aux;
		aux->next = new_node;
	}
	else
	{
		*head = new_node;
		new_node->prev = NULL;
	}

	return (new_node);
}
