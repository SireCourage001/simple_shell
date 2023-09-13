#include "shell.h"

/**
 * main_get_alias - Add, remove or show aliases.
 * @data: Struct for the program's data.
 * @name: Name of the requested alias.
 * Return: zero if success, or other number if its declared in the arguments
 */
char *main_get_alias(core_prog_data *data, char *name)
{
	int ind_i, alias_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = get_str_length(name);

	for (ind_i = 0; data->alias_list[ind_i]; ind_i++)
	{
		if (str_comparingfunc(name, data->alias_list[ind_i], alias_length) &&
			data->alias_list[ind_i][alias_length] == '=')
		{
			return (data->alias_list[ind_i] + alias_length + 1);
		}
	}
	return (NULL);

}

/**
 * func_toprint_alias - add, remove, show aliases
 * @data: struct of the data
 * @alias: name of the alias
 * Return: zero if success, or other number if its declared in the arguments
 */
int func_toprint_alias(core_prog_data *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = get_str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_comparingfunc(data->alias_list[i], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be set in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if success, or other number if its declared in the arguments
 */
int main_set_alias(char *alias_string, core_prog_data *data)
{
	int i, j;
	char cmbuffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			cmbuffer[i] = alias_string[i];
		else
		{
			temp = main_get_alias(data, alias_string + i + 1);
			break;
		}
	for (j = 0; data->alias_list[j]; j++)
		if (str_comparingfunc(cmbuffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}
	if (temp)
	{
		buffer_add(cmbuffer, "=");
		buffer_add(cmbuffer, temp);
		data->alias_list[j] = str_duplicate(cmbuffer);
	}
	else
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
