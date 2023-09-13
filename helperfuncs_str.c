#include "shell.h"

/**
 *str_reversal -  function to reverses a string.
 *
 * @string: pointer to string.
 * Return: void.
 */
void str_reversal(char *string)
{
	int i = 0, length = get_str_length(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}

/**
 ** str_comparingfunc - Compare two strings
  * @string1: String one, or the shorter
  * @string2: String two, or the longer
  * @number: number of characters to be compared, 0 if infinite
  * Return: 1 if the strings are equals,0 if the strings are different
  */
int str_comparingfunc(char *string1, char *string2, int number)
{
	int main_loop;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (get_str_length(string1) != get_str_length(string2))
			return (0);
		for (main_loop = 0; string1[main_loop]; main_loop++)
		{
			if (string1[main_loop] != string2[main_loop])
				return (0);
		}
		return (1);
	}
	else
	{
		for (main_loop = 0; main_loop < number; main_loop++)
		{
			if (string1[main_loop] != string2[main_loop])
				return (0);
		}
		return (1);
	}
}

/**
 * get_str_length - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int get_str_length(char *string)
{
	int main_length = 0;

	if (string == NULL)
		return (0);

	while (string[main_length++] != '\0')
	{
	}
	return (--main_length);
}

/**
 * str_duplicate - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *str_duplicate(char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = get_str_length(string) + 1;
	
	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		result[i] = string[i];
	}

	return (result);
}

/**
 * str_concator - concatenates two strings.
 * @string1: String to be concatenated
 * @string2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_concator(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = get_str_length(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = get_str_length(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
		for (length1 = 0; string1[length1] != '\0'; length1++)
			result[length1] = string1[length1];
		free(string1);

		/* copy of string2 */
			for (length2 = 0; string2[length2] != '\0'; length2++)
			{
				result[length1] = string2[length2];
				length1++;
			}

			result[length1] = '\0';
			return (result);
}





 
 
