#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

#define MAX_LINE_LENGTH 1024

void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);

instruction_t instructions[] = {
    {"push", push},
    {"pall", pall},
    /* Add more instructions here */
    {NULL, NULL} // Null terminator for the instructions array
};

void push(stack_t **stack, unsigned int line_number)
{
    // Example implementation of the push instruction
    // You'll need to modify this according to your needs
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    // Set the value of the new node
    new_node->n = 42; // Example value, modify according to your needs

    // Update the pointers of the new node
    new_node->prev = NULL;
    new_node->next = *stack;

    // Update the previous pointer of the existing top node (if any)
    if (*stack != NULL)
        (*stack)->prev = new_node;

    // Update the stack pointer to point to the new node
    *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number)
{
    // Example implementation of the pall instruction
    // You'll need to modify this according to your needs
    stack_t *current = *stack;
    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

void execute_instruction(char *opcode, stack_t **stack, unsigned int line_number)
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

void process_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    char *opcode;
    unsigned int line_number = 1;
    stack_t *stack = NULL;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        opcode = strtok(line, " \t\n");

        if (opcode != NULL && opcode[0] != '#') // Ignore empty lines and comments
            execute_instruction(opcode, &stack, line_number);

        line_number++;
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    process_file(file_path);

    return EXIT_SUCCESS;
}
