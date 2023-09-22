#include "shell.h"

/**
 * splitString - splits input into separate commands
 * based on spaces and semicolons
 * @build: input build
 * Return: true if able to split, false if not
 */
_bool splitString(config *build)
{
	register unsigned int i = 0;
	char *tok, *cpy, *trimmed;

	if (countWords(build->buffer) == 0)
	{
		build->args = NULL;
		free(build->buffer);
		return (false);
	}

	build->args = malloc((countWords(build->buffer) + 1) * sizeof(char *));
	cpy = _strdup(build->buffer);
	tok = _strtok(cpy, " ;");

	while (tok)
	{
		trimmed = _strdup(tok);
		if (trimmed)
		{
			trimLeadingTrailingSpaces(trimmed);
			if (_strlen(trimmed) > 0)
			{
				build->args[i] = trimmed;
				i++;
			}
			else
			{
				free(trimmed);
			}
		}

		tok = _strtok(NULL, " ;"); /* Continue splitting */
	}

	build->args[i] = NULL;
	free(cpy);
	return (true);
}

/**
 * trimLeadingTrailingSpaces - trims leading and trailing spaces from a string
 * @str: input string
 */
void trimLeadingTrailingSpaces(char *str)
{
	char *start = str;
	char *end = str + _strlen(str) - 1;

	/* Trim leading spaces */
	while (start <= end && isSpace(*start))
	{
		start++;
	}

	/* Trim trailing spaces */
	while (end >= start && isSpace(*end))
	{
		end--;
	}

	/* Move null terminator to the end of the trimmed string */
	*(end + 1) = '\0';

	/* Shift the trimmed part to the beginning of the string */
	if (start != str)
	{
		while (*start)
		{
			*str++ = *start++;
		}
		*str = '\0';
	}
}

/**
 * countWords - count number of words in a string
 * @str: input string
 * Return: number of words
 */
unsigned int countWords(char *str)
{
	register int words = 0;
	_bool wordOn = false;

	while (*str)
	{
		if (isSpace(*str) && wordOn)
			wordOn = false;
		else if (!isSpace(*str) && !wordOn)
		{
			wordOn = true;
			words++;
		}
		str++;
	}
	return (words);
}

/**
 * isSpace - determines if char is a space
 * @c: input char
 * Return: true or false
 */
_bool isSpace(char c)
{
	return (c == ' ');
}
