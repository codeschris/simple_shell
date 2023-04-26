#include "shell.h"

/**
 * str_length - function returns len of a string
 *
 * @string: ptr to string
 *
 * Return: len of string
 */

int str_length(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
		return (--len);
}

/**
 * str_duplicate - function duplicates a string
 *
 * @string: string to be copied
 *
 * Return: ptr to the arr
 */

char *str_duplicate(char *string)
{
	char *result;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = str_length(string) + 1;

	result = malloc(sizeof(char) * len);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len; i++)
	{
		result[i] = string[i];
	}

	return (result);
}

/**
 * str_compare - function compares two strings
 *
 * @string1: first string
 * @string2: second string
 * @number: number of characters to be compared, 0 if infinite
 *
 * Return: 1 is equal, 0 if not equal
 */

int str_compare(char *string1, char *string2, int number)
{
	int iterator;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (iterator = 0; string1[iterator]; iterator++)
		{
			if (string1[iterator] != string2[iterator])
				return (0);
		}
		return (1);
	}
	else
	{
		for (iterator = 0; iterator < number; iterator++)
		{
			if (string1[iterator] != string2[iterator])
				return (0);
		}
		return (1);
	}
}

/**
 * str_concat - function concatenates two strings
 *
 * @string1: first string
 * @string2: second string
 *
 * Return: ptr to arr
 */

char *str_concat(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = str_length(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (length1 = 0; string1[length1] != '\0'; length1++)
		result[length1] = string1[length1];
	free(string1);

	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		result[length1] = string2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}

/**
 * str_reverse - function reverses a string
 *
 * @string: ptr to string
 *
 * Return: Nothing
 */

void str_reverse(char *string)
{
	int i = 0, length = str_length(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}
