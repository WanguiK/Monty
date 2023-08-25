#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * swap- swaps the top two elements of the stack
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *top;
	int temp;

	top = *stack;
	if (top == NULL || top->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = top->n;
	top->n = top->next->n;
	top->next->n = temp;
}
