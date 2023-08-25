#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void file_error(char *argv);
void error_usage(void);
int status = 0;
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

	stack = NULL;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	read_file(argv[1], &stack);
	free_dlistint(stack);
	return (0);
}
/**
 * read_file- reads a bytecode file and runs commands
 * @filename: pathname to file
 * @stack: pointer to the top of the stack
 */
void read_file(char *filename, stack_t **stack)
{
	char *line;
	size_t len = 0;
	int line_count = 0;
	ssize_t nread;
	instruct_func func;
	int j;

	var_global.file = fopen(filename, "r");

	if (var_global.file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while ((nread = getline(&var_global.buffer, &len, var_global.file)) != -1)
	{
		line = parse_line(var_global.buffer, stack, line_count);
		if (line[0] == 0 || line[0] == '#')
		{
			line_count++;
			continue;
		}
		func = get_op_func(line);

		if (func == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_count, line);
			exit(EXIT_FAILURE);
		}
		func(stack, line_count);
		line_count++;
	}
	free(var_global.buffer);
	j = fclose(var_global.file);
	if (j == -1)
		exit(-1);
}
/**
 * get_op_func -  checks opcode and returns the correct function
 * @str: the opcode
 * Return: returns a functions, or NULL on failure
 */
instruct_func get_op_func(char *str)
{
	int i;
	char *opcode;

	instruction_t instruct[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"sub", sub},
		{"mul", mul},
		{"div", _div},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL},
	};

	opcode = strtok(str, " ");
	i = 0;
	while (instruct[i].opcode != NULL)
	{
		if (strcmp(instruct[i].opcode, opcode) == 0)
			return (instruct[i].f);
		i++;
	}
	return (NULL);
}
/**
 * is_number - checks if a string is a number
 * @str: string being passed
 * Return: returns 1 if string is a number, 0 otherwise
 */
int is_number(char *str)
{
	unsigned int i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[0] == '-')
		{
			i++;
			continue;
		}
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
