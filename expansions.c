#include "shell.h"

/**
 * expand_var - function expands variables
 *
 * @data: ptr to struct of progdata
 *
 * Return: Nothing
 */

void expand_var(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			tmp = env_get_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			tmp ? buffer_add(line, tmp) : 1;
			buffer_add(line, expansion);
		}
	}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - function expands aliases
 *
 * @data: ptr to struct of progdata
 *
 * Return: nothing
 */

void expand_alias(data_of_program *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		tmp = get_alias(data, expansion);
		if (tmp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			line[i] = '\0';
			buffer_add(line, tmp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - function appends string to the end of the buffer
 *
 * @buffer: buffer to be filled
 * @str: string to be cp to the buffer
 *
 * Return: Nothing
 */

int buffer_add(char *buffer, char *str)
{
	int len, i;

	len = str_length(buffer);
	for (i = 0; str[i]; i++)
	{
		buffer[len + i] = str[i];
	}
	buffer[len + i] = '\0';
	return (len + i);
}
