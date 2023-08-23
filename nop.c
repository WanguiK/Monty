#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * _nop- doesn’t do anything
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void _nop(__attribute__ ((unused))stack_t **stack,
		__attribute__ ((unused)) unsigned int line_number)
{
	;
}
