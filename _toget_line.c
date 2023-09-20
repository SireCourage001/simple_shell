#include "shell.h"

/**
* check_logic_ops - checks and split for && and || operators
* @array_commands: array of the commands.
* @i: index in the array_commands to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL; 
	int indj;

	/* checks for the & char in the command line*/
	for (indj = 0; array_commands[i] != NULL  && array_commands[i][indj]; indj++)
	{
		if (array_commands[i][indj] == '&' && array_commands[i][indj + 1] == '&')
		{
			/* split the line when chars && was found */
			temp = array_commands[i];
			array_commands[i][indj] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + indj + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			indj = 0;
		}
		if (array_commands[i][indj] == '|' && array_commands[i][indj + 1] == '|')
		{
			/* split the line when chars || was found */
			temp = array_commands[i];
			array_commands[i][indj] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + indj + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			indj = 0;
		}
	}
	return (i);
}

/**
* _togetline - read one line from the prompt.
* @data: struct for the program's data
*
* Return: reading counting bytes.
*/
int _togetline(core_prog_data *data)
{
	char dabuff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}
		bytes_read = read(data->file_descriptor, &dabuff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);
		i = 0;
		do {
			array_commands[i] = str_duplicate(_strtok(i ? NULL : dabuff, "\n;"));
			i = check_logic_ops(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}
	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (get_str_length(data->input_line));
}
