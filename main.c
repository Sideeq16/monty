#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

#define MAX_LINE_LENGTH 1024


/* instruction_t instructions[] = { */
/*	{"push", push}, */
/*	{"pall", pall}, */
/*	{NULL, NULL} */
/* }; */


/**
 * push - push method
 * @stack: stack
 * @value: value
 */
void push(stack_t **stack, unsigned int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));
	/* (void)line_number; */

	if (new_node == NULL)
	{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
	}

	new_node->n = value;
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
 * @instructions: what to do
 * @argument: param
 */

void execute_instruction(instruction_t *instructions,
char *opcode, char *argument, stack_t **stack,
unsigned int line_number)
{
	int i = 0;
	(void)argument;

	/* if (strcmp(opcode, "push") == 0) */
	/* { */
	/*	int value = atoi(argument); */
	/*	push(stack, value); */
	/* } */

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
 * @instructions: what to do
 */
void process_file(instruction_t *instructions, const char *file_path)
{
	FILE *file = fopen(file_path, "r");
	char line[MAX_LINE_LENGTH];
	char *opcode;
	char *argument;
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
	argument = strtok(NULL, " \t\n");

	if (opcode != NULL && opcode[0] != '#')
	execute_instruction(instructions, opcode, argument, &stack, line_number);

	line_number++;
	}

	fclose(file);
	free_stack(stack);
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
	instruction_t instructions[] = {
	{"push", push},
	{"pall", pall},
	{NULL, NULL}
	};

	if (argc != 2)
	{
	fprintf(stderr, "USAGE: monty file\n");
	return (EXIT_FAILURE);
	}
	file_path = argv[1];
	process_file(instructions, file_path);
	return (EXIT_SUCCESS);
}
