#include "shell.h"

/**
 * execute - program executes a command with its entire path variables
 *
 * @data: ptr to prog data
 *
 * Return: 0 Success, -1 otherwise
 */

int execute(data_of_program *data)
{
	int r = 0, status;
	pid_t pidd;

	r = builtins_list(data);
	if (r != -1)
		return (r);

	r = find_program(data);
	if (r)
	{
		return (r);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			r = execve(data->tokens[0], data->tokens, data->env);
			if (r == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
