#include "shell.h"

/**
 * long_to_string - function converts a number to a string
 *
 * @num: number to be converted
 * @str: string to save the num as string
 * @base: base to convert number
 *
 * Return: Nothing
 */

void long_to_string(long num, char *str, int base)
{
	int index = 0, inNegative = 0;
	long coi = num;
	char letters[] = {"0123456789abcdef"};

	if (coi == 0)
		str[index++] = '0';

	if (str[0] == '-')
		inNegative = 1;

	while (coi)
	{
		if (coi < 0)
			str[index++] = letters[-(coi % base)];
		else
			str[index++] = letters[coi % base];
		coi /= base;
	}
	if (inNegative)
		str[index++] = '-';

	str[index] = '\0';
	str_reverse(str);
}

/**
 * _atoi - function converts string to an int
 *
 * @s: ptr to str origen
 *
 * Return: int of str or 0
 */

int _atoi(char *s)
{
	int z = 1;
	unsigned int num = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			z *= -1;
		if (*s == '+')
			z *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * z);
}

/**
 * count_characters - function counts coincidences of character in string
 *
 * @string: ptr to str origen
 * @character: string with chars to be counted
 *
 * Return: int of str or 0
 */

int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
