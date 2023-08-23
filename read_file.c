#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * read_file- reads a bytecode file and runs commands
 * @filename: pathname to file
 * @stack: pointer to the top of the stack
 */
void read_file(char *filename, stack_t **stack)
{
	char *line = NULL;
	size_t len = 0;
	int line_count = 0;
	ssize_t nread;
	instruct_func func;
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while ((nread = getline(&line, &len, file)) != -1)
	{
		line_count++;
		line[strcspn(line, "\n")] = 0;
		if (line[0] == 0 || line[0] == '#')
			continue;

		func = get_op_func(line);

		if (func == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_count, line);
			exit(EXIT_FAILURE);
		}
		func(stack, line_count);
	}
	free(line);
	fclose(file);
}
/**
 * get_op_func -  checks opcode and returns the correct function
 * @str: the opcode
 * Return: returns a functions, or NULL on failure
 */
instruct_func get_op_func(char *str)
{
	int i;

	instruction_t instruct[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add},
		{"nop", _nop},
		{"sub", _sub},
		{"mul", _mul},
		{"div", _div},
		{"mod", _mod},
		{"pchar", _pchar},
		{"pstr", _pstr},
		{"rotl", _rotl},
		{"rotr", _rotr},
		{NULL, NULL},
	};

	i = 0;
	while (instruct[i].opcode != NULL)
	{
		if (strcmp(instruct[i].opcode, str) == 0)
			return (instruct[i].f);
		i++;
	}
	return (NULL);
}
