#include "shell.h"

/**
 * print_environ - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_environ(core_prog_data *data)
{
	int index_j;

	for (index_j = 0; data->env[index_j]; index_j++)
	{
		_print(data->env[index_j]);
		_print("\n");
	}
}

/**
 * env_set_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_set_key(char *key, char *value, core_prog_data *data)
{
	int i, keyoflength = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);
	keyoflength = get_str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_comparingfunc(key, data->env[i], keyoflength) &&
		 data->env[i][keyoflength] == '=')
		{
			is_new_key = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = str_concator(str_duplicate(key), "=");
	data->env[i] = str_concator(data->env[i], value);

	if (is_new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, core_prog_data *data)
{
	int i, keyoflength = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);
	keyoflength = get_str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_comparingfunc(key, data->env[i], keyoflength) &&
		 data->env[i][keyoflength] == '=')
		{
			return (data->env[i] + keyoflength + 1);
		}
	}
	return (NULL);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, core_prog_data *data)
{
	int i, keylength = 0;

	if (key == NULL || data->env == NULL)
		return (0);
	keylength = get_str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_comparingfunc(key, data->env[i], keylength) &&
		 data->env[i][keylength] == '=')
		{
			free(data->env[i]);
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}
