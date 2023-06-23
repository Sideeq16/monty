#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * main - Monty Byte code reader
 * @argv: argument values
 * @argc: count number of argument
 * Return: 0 or 1
 */
int main(int argc, char **argv)
{
	FILE *op_file;
	track_file init_tracker = {NULL,1};
	char *line = NULL;
	size_t len = 0;
	int read;
	(void)argv;

	tracker = &init_tracker;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
	}
	op_file = fopen(argv[1],"r");
	if(op_file == NULL)
	{
		log_err(401);	
	}

	tracker->fileName = argv[1];

	while(getline(&line, &len, op_file) != -1)
	{
		printf("Read %s", line);
	}

	fclose(op_file);
	
	return (0);
}
