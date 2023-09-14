#include "shell.h"

/**
 * _print - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, get_str_length(string)));
}
/**
 * _printit - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _printit(char *string)
{
	return (write(STDERR_FILENO, string, get_str_length(string)));
}

/**
 * _print_error - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_error(int errorcode, core_prog_data *data)
{
	char num_in_char[10] = {'\0'};

	long_to_string((long) data->exec_counter, num_in_char, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printit(data->program_name);
		_printit(": ");
		_printit(num_in_char);
		_printit(": ");
		_printit(data->tokens[0]);
		if (errorcode == 2)
			_printit(": Illegal number: ");
		else
			_printit(": can't cd to ");
		_printit(data->tokens[1]);
		_printit("\n");
	}
	else if (errorcode == 127)
	{
		_printit(data->program_name);
		_printit(": ");
		_printit(num_in_char);
		_printit(": ");
		_printit(data->command_name);
		_printit(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printit(data->program_name);
		_printit(": ");
		_printit(num_in_char);
		_printit(": ");
		_printit(data->command_name);
		_printit(": Permission denied\n");
	}
	return (0);
}
