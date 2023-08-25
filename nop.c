#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * nop- doesn’t do anything
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
