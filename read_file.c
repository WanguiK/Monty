#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
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

	var_global.file = fopen(filename, "r");

	if (var_global.file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while ((nread = getline(&var_global.buffer, &len, var_global.file)) != -1)
	{
		line = _parse_line(var_global.buffer, stack, line_count);
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
		line_count++;
	}
	free(var_global.buffer);
	fclose(var_global.file);
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
