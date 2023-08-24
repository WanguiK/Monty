#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * _add- adds the top two elements of the stack
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void _add(stack_t **stack, unsigned int line_number)
{
	int sum =0;
	stack_t *temp;

	temp = *stack;

	if (temp == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	while (temp)
	{
		temp = temp->next;
	}

	if (stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	sum = (*stack)->next->n + (*stack)->n;
	_pop(stack, line_number);

	(*stack)->n = sum;
}

/**
 * _sub- doesn’t do anything
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void _sub(stack_t **stack, unsigned int line_number)
{
	int sub = 0;

	if (stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	sub = (*stack)->next->n - (*stack)->n;
	_pop(stack, line_number);

	(*stack)->n = sub;
}


/**
 * _mul - mult the second top element of stack by the top element of stack
 * @stack: pointer to lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void _mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	(*stack)->next->n *= (*stack)->n;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * _mod - computes the rest of the division of the second top element
 *        of the stack by the top element of the stack.
 * @stack: pointer to lists for monty stack
 * @line_number: number of line opcode occurs on
 */
void _mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	(*stack)->next->n %= (*stack)->n;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}
