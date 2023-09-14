#include "shell.h"

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void ctrl_plus_c_handler(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * sisifo - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void system_info_func(char *prompt, core_prog_data *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter)) 
	{
		_print(prompt);
		error_code = string_len = _togetline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenizerfuncn(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}

/**
 * inicialize_data - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void init_data_func(core_prog_data *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printit(data->program_name);
			_printit(": 0: Can't open ");
			_printit(argv[1]);
			_printit("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * main - initialize the main program
 * @argc: number of values received
 * @argv: values from the command line
 * @env: values received from the com line
 * Return: Returns zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	core_prog_data data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	init_data_func(data, argc, argv, env);

	signal(SIGINT, ctrl_plus_c_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	system_info_func(prompt, data);
	return (0);
}
