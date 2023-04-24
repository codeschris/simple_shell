#include "shell.h"

/**
 * _print - function writes in STDOUT
 *
 * @str: ptr to array of char
 *
 * Return: number of bytes written. Otherwise, -1 is returned and errno is set
 * appropriately
 */

int _print(char *str)
{
	return (write(STDOUT_FILENO, str, str_length(str)));
}

/**
 * eprint - function writes in STDERR
 *
 * @str: ptr to array of char
 *
 * Return: number of bytes written. Otherwise, -1 is returned and errno is set
 * appropriately
 */

int eprint(char *str)
{
	return (write(STDERR_FILENO, str, str_length(str)));
}

/**
 * print_err - function writes in standard error
 *
 * @data: ptr to prog data
 * @err_code: error code to print
 *
 * Return: number of bytes written. Otherwise, -1 is returned and errno is set
 * appropriately
 */

int print_err(int err_code, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (err_code == 2 || err_code == 3)
	{
		eprint(data->program_name);
		eprint(": ");
		eprint(n_as_string);
		eprint(": ");
		eprint(data->tokens[0]);
		if (err_code == 2)
			eprint(": Illegal number: ");
		else
			eprint(": can't cd to ");
		eprint(data->tokens[1]);
		eprint("\n");
	}
	else if (err_code == 127)
	{
		eprint(data->program_name);
		eprint(": ");
		eprint(n_as_string);
		eprint(": ");
		eprint(data->command_name);
		eprint(": not found\n");
	}
	else if (err_code == 126)
	{
		eprint(data->program_name);
		eprint(": ");
		eprint(n_as_string);
		eprint(": ");
		eprint(data->command_name);
		eprint(": Permission denied\n");
	}
	return (0);
}
