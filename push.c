#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "monty.h"

/**
 * _push-  pushes an element to the stack
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void _push(stack_t **stack, unsigned int line_number)
{
	stack_t *top;

	(void)line_number;

	top = malloc(sizeof(stack_t));
	if (top == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	top->n = var_global.push_argv;
	top->next = *stack;
	top->prev = NULL;

	if (*stack != NULL)
	{
		(*stack)->prev = top;
	}
	*stack = top;
}
/**
 * _parse_line - parses a line for an opcode and arguments
 * @line: the line to be parsed
 * @stack: pointer to the head of the stack
 * @line_number: the current line number
 * Return: returns the opcode or null on failure
 */
char *_parse_line(char *line, stack_t **stack, unsigned int line_number)
{
	char *op_code, *push, *argv;
	(void)stack;

	push = "push";
	op_code = strtok(line, "\n ");
	if (op_code == NULL)
		return (NULL);

	if (strcmp(op_code, push) == 0)
	{
		argv = strtok(NULL, "\n ");
		if (argv != NULL && is_number(argv) == 1)
		{
			var_global.push_argv = atoi(argv);
		}
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}
	return (op_code);
}
