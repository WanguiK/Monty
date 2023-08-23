#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * _pint- prints the value at the top of the stack
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void _pint(stack_t **stack, unsigned int line_number)
{
	stack_t *top;

	top = *stack;

	if (top == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%d\n", top->n);
	}
}
