#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * pall- prints all the values on the stack
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void pall(stack_t **stack, __attribute__ ((unused))unsigned int line_number)
{
	stack_t *all;

	all = *stack;
	while (all != NULL)
	{
		printf("%d\n", all->n);
		all = all->next;
	}
}
