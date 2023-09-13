#include "shell.h"

/**
 * builtins_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int builtins_list(core_prog_data *data)
{
	int loop1;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_helper},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};
	for (loop1 = 0; options[loop1].builtin != NULL; loop1++)
	{
		if (str_comparingfunc(options[loop1].builtin, data->command_name, 0))
		{
			return (options[loop1].function(data));
		}
	}
	return (-1);
}

/**
 * builtin_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */
int builtin_alias(core_prog_data *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (func_toprint_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (character_counter(data->tokens[i], "="))
			main_set_alias(data->tokens[i], data);
		else
			func_toprint_alias(data, data->tokens[i]);
	}

	return (0);
}

/**
 * set_working_directory - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if success, or other number if its declared in the arguments
 */
int set_working_directory(core_prog_data *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_comparingfunc(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_helper - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */
int builtin_helper(core_prog_data *data)
{
	int i, length = 0;
	char *vmssg_info[6] = {NULL};

	vmssg_info[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(vmssg_info[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	vmssg_info[1] = HELP_EXIT_MSG;
	vmssg_info[2] = HELP_ENV_MSG;
	vmssg_info[3] = HELP_SETENV_MSG;
	vmssg_info[4] = HELP_UNSETENV_MSG;
	vmssg_info[5] = HELP_CD_MSG;

	for (i = 0; vmssg_info[i]; i++)
	{
		length = get_str_length(data->tokens[1]);
		if (str_comparingfunc(data->tokens[1], vmssg_info[i], length))
		{
			_print(vmssg_info[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

