#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * free_stack - print error out
 * @stack: type of error
 */
void free_stack(stack_t *stack)
{
	stack_t *current = stack;
	stack_t *temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}
