#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
#include <string.h>

/**
 * main - Monty Byte code reader
 * @argv: argument values
 * @argc: count number of argument
 * Return: 0 or 1
 */
int main(int argc, char **argv)
{
	FILE *op_file;
	char *line = NULL;
	size_t len = 0;
	int read;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
	}
	op_file = fopen(argv[1],"r");
	if(op_file == NULL)
	{
		printf("error found");	
	}

	while((read = getline(&line, &len, stdin)) != -1)
	{
		printf("Read %s", line);
	}

	fclose(op_file);
	
	return (0);
}
