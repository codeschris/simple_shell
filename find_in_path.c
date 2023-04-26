#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - function finds a program in PATH
 *
 * @data: ptr to struct of progdata
 *
 * Return: 0 Success, errcode otherwise
 */

int find_program(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **dir;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dir = tokenize_path(data);

	if (!dir || !dir[0])
	{
		errno = 127;
		return (errno);
	}
	for (i = 0; dir[i]; i++)
	{
		dir[i] = str_concat(dir[i], data->tokens[0]);
		ret_code = check_file(dir[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(dir[i]);
			free_array_of_pointers(dir);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(dir);
	return (ret_code);
}

/**
 * tokenize_path - function tokenizes the PATH in dir
 *
 * @data: ptr to struct of progdata
 *
 * Return: arr of PATH directories
 */

char **tokenize_path(data_of_program *data)
{
	int i = 0;
	int dir_count = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
		return (NULL);

	PATH = str_duplicate(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			dir_count++;
	}

	tokens = malloc(sizeof(char *) * dir_count);

	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
		tokens[i] = str_duplicate(_strtok(NULL, ":"));

	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * check_file - function checks if a file exists, if its a dir and its
 * exec permissions
 *
 * @full_path: ptr to full file name
 *
 * Return: 0 Success, errcode if file exists
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (errno);
		}
		return (0);
	}
	errno = 127;
	return (errno);
}
