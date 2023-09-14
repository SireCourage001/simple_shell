#include "shell.h"
/**
 * _strtok - separates strings with delimiters
 * @line: It´s pointer to array we receive in getline.
 * @delim: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copy_of_str;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			break;
		}
		if (delim[j] == '\0')
			break;
	}
	copy_of_str = str;
	if (*copy_of_str == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copy_of_str);
			}
		}
	}
	return (copy_of_str);
}

/**
 * tokenizerfuncn - this function separate the string
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenizerfuncn(core_prog_data *data)
{
	char *delimiter = " \t";
	int i, j, countVal = 2, length;

	length = get_str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input_line[i] == delimiter[j])
				countVal++;
		}
	}

	data->tokens = malloc(countVal * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_duplicate(_strtok(NULL, delimiter));
	}
}
