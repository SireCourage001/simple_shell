#include "shell.h"
/**
 * execute - execute a command with its entire path vars.
 * @data: a pointer to the program's data
 * Return: If success returns zero, otherwise, return -1.
 */
int execute(core_prog_data *data)
{
	int d_returnVal = 0, status;
	pid_t pidd;

	d_returnVal = builtins_list(data);
	if (d_returnVal != -1)
		return (d_returnVal);

	d_returnVal = find_program(data);
	if (d_returnVal)
	{
		return (d_returnVal);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			d_returnVal = execve(data->tokens[0], data->tokens, data->env);
			if (d_returnVal == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}

/**
 * expand_alias - expand aliases
 * @data: a pointer to a struct of the program's data
 * 
 * Return: nothing, but sets errno.
 */
void expand_alias(core_prog_data *data)
{
	int i, j, data_expanded = 0;
	char m_line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(m_line, data->input_line);

	for (i = 0; m_line[i]; i++)
	{
		for (j = 0; m_line[i + j] && m_line[i + j] != ' '; j++)
			expansion[j] = m_line[i + j];
				expansion[j] = '\0';

			temp = main_get_alias(data, expansion);
			if (temp)
			{
				expansion[0] = '\0';
				buffer_add(expansion, m_line + i + j);
				m_line[i] = '\0';
				buffer_add(m_line, temp);
																			m_line[get_str_length(m_line)] = '\0';
																			buffer_add(m_line, expansion);
																			data_expanded = 1;
			}
			break;
	}
	if (data_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(m_line);
	}
}
/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 * 
 * Return: nothing, but sets errno.
 */
void expand_variables(core_prog_data *data)
{
	int i, j;
	char m_line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(m_line, data->input_line);
	for (i = 0; m_line[i]; i++)
		if (m_line[i] == '#')
			m_line[i--] = '\0';
		else if (m_line[i] == '$' && m_line[i + 1] == '?')
		{
			m_line[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(m_line, expansion);
			buffer_add(m_line, data->input_line + i + 2);
		}
		else if (m_line[i] == '$' && m_line[i + 1] == '$')
		{
			m_line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(m_line, expansion);
			buffer_add(m_line, data->input_line + i + 2);
		}
		else if (m_line[i] == '$' && (m_line[i + 1] == ' ' || m_line[i + 1] == '\0'))
			continue;
		else if (m_line[i] == '$')
		{
			for (j = 1; m_line[i + j] && m_line[i + j] != ' '; j++)
				expansion[j - 1] = m_line[i + j];
				temp = env_get_key(expansion, data);
				m_line[i] = '\0', expansion[0] = '\0';
				buffer_add(expansion, m_line + i + j);
				temp ? buffer_add(m_line, temp) : 1;
				buffer_add(m_line, expansion);
		}

	if (!str_comparingfunc(data->input_line, m_line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(m_line);
	}
}
int buffer_add(char *buffer, char *str_tobe_added)
{
	int length_of_str, i;

	length_of_str = get_str_length(buffer);
	for (i = 0; str_tobe_added[i]; i++)
	{
		buffer[length_of_str + i] = str_tobe_added[i];
	}
	buffer[length_of_str + i] = '\0';
	return (length_of_str + i);
}




