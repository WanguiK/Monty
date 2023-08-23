#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "monty.h"

/**
 * push-  pushes an element to the stack
 * @stack: linked lists for monty stack
 * @line_number: number of line opcode occurs on
 * @value_str: integer value to be pushed onto the stack
 */
void push(stack_t **stack, unsigned int line_number, char *value_str)
{
	stack_t *top;
	int value = 0;
	int i;

	for (i = 0; value_str[i] != 0; i++)
	{
		if (!_isdigit(value_str[i]))
		{
			fprintf(stderr, "Error: L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}

	value = atoi(value_str);

	top = malloc(sizeof(stack_t));
	if (top == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	top->n = value;
	top->next = *stack;
	top->prev = NULL;

	if (*stack != NULL)
	{
		(*stack)->prev = top;
	}
	*stack = top;
}
/**
 *_isdigit- checks for digits from 0 to 9
 *@c: character to print
 *Return: 1 if character is a digit and 0 for otherwise
 */
int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
	return (1);
	}
	else
	{
	return (0);
	}
}

/**
 * read_file- reads a bytecode file and runs commands
 * @filename: pathname to file
 * @stack: pointer to the top of the stack
 */
void read_file(const char *filename, stack_t **stack)
{
	FILE *file = fopen(filename, "r");
	char line[256];
	char value_str[100];
	int opcode;
	unsigned int line_number = 0;

	if (file == NULL)
	{
		fprintf(stderr, "Error opening file: %s\n", filename);
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof(line), file))
	{
		line_number++;
		if (sscanf(line, "%d %s", &opcode, value_str) == 2)
		{
			switch (opcode)
			{
				case 1:
					push(stack, line_number, value_str);
					break;
				case 2:
					pall(stack, line_number);
					break;
				case 3:
					pop(stack, line_number);
					break;
				case 4:
					pint(stack, line_number);
					break;
				case 5:
					fclose(file);
					exit(EXIT_SUCCESS);
				default:
					printf("\nInvalid choice!!\n");
			}
		}
	}
	fclose(file);
}

/**
 * free_dlistint - free a list
 * @head: pointer to first node
 *
 */
void free_dlistint(stack_t *head)
{
	stack_t *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
