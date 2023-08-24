#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

global_var var_global;

/**
 * main - driver function for monty program
 * @argc: argument count
 * @argv: opcode file
 * Return: 0
 */
int main(int argc, char **argv)
{
	stack_t *stack;
	FILE *file;

	stack = NULL;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	read_file(argv[1], &stack);
	free_dlistint(stack);
	return (0);
}
