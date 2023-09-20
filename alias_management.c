#include "shell.h"

/**
 * main_get_alias - Add, remove or show aliases.
 * @data: Struct for the program's data.
 * @name: Name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
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
 * Return: zero if sucess, or other number if its declared in the arguments
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
