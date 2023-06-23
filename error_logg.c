#include <stdio.h>
#include "monty.h"

/**
 * log_err - print error out
 * @err_pos: type of error
 * Return:
 */
void log_err(int err_pos)
{
	if (err_pos == 401)
		fprintf(stderr, "Error: Can't open file %s\n", tracker->fileName);

}
