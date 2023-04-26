#include "shell.h"

/**
 * free_recurrent_data - function frees the fields needed each loop
 *
 * @data: ptr to struct of progdata
 *
 * Return: Nothing
 */

void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all - function frees all fields of data
 *
 * @data: ptr to struct of progdata
 *
 * Return: Nothing
 */

void free_all(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - function frees each ptr of an array
 * of ptrs and the array too
 *
 * @arr: array of ptrs
 *
 * Return: Nothing
 */

void free_array_of_pointers(char **arr)
{
	int i;

	if (arr != NULL)
	{
		for (i = 0; arr[i]; i++)
			free(arr[i]);

		free(arr);
		arr = NULL;
	}
}
