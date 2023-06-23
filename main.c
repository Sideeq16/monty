#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

#define MAX_LINE_LENGTH 1024


instruction_t instructions[] = {
	{"push", push},
	{"pall", pall},
	{NULL, NULL}
};


/**
 * push - push method
 * @stack: stack
 * @line_number: line
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node = malloc(sizeof(stack_t));
	(void)line_number;

	if (new_node == NULL)
	{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
	}

	new_node->n = 42;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
	(*stack)->prev = new_node;

	*stack = new_node;
}


/**
 * pall - pall
 * @stack: stack
 * @line_number: line number
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void)line_number;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}


/**
 * execute_instruction - instruction to follow
 * @opcode: count ags
 * @stack: value of arg
 * @line_number: line nummber
 */

void execute_instruction(char *opcode, stack_t **stack,
unsigned int line_number)
{
	int i = 0;

	while (instructions[i].opcode != NULL)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			return;
		}
	i++;
	}

	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

/**
 * process_file - process file
 * @file_path: value of arg
 */
void process_file(const char *file_path)
{
	FILE *file = fopen(file_path, "r");
	char line[MAX_LINE_LENGTH];
	char *opcode;
	unsigned int line_number = 1;
	stack_t *stack = NULL;

	if (file == NULL)
	{
	fprintf(stderr, "Error: Can't open file %s\n", file_path);
	exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
	opcode = strtok(line, " \t\n");

	if (opcode != NULL && opcode[0] != '#')
	execute_instruction(opcode, &stack, line_number);

	line_number++;
	}

	fclose(file);
}

/**
 * main - main file
 * @argc: count ags
 * @argv: value of arg
 * Return: int
 */
int main(int argc, char *argv[])
{

	const char *file_path;

	if (argc != 2)
	{
	fprintf(stderr, "USAGE: monty file\n");
	return (EXIT_FAILURE);
	}
	file_path = argv[1];
	process_file(file_path);
	return (EXIT_SUCCESS);
}
