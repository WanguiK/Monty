#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * _pop- removes the top element of the stack
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void _pop(stack_t **stack, unsigned int line_number)
{
	stack_t *top;

	top = *stack;

	if (stack == NULL || top == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	*stack = top->next;
	if (*stack != NULL)
	{
		(*stack)->prev = NULL;
	}
	free(top);
}
