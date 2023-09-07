#ifndef SHELL_H
#define SHELL_H

#include "macros.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <fontl.h>

/**
 * struct info - Struct for the program's data
 * @program_name: The name of the executable,
 * @input_line: Pointer to the input read for _getline,
 * @command_name: Pointer to the first command typed by the user,
 * @exec_counter: Number of executed commands,
 * @file_descriptor: File descriptor to the input of commands,
 * @tokens: Pointer to array of tokenized input,
 * @env: Copy of the environ,
 * @alias_list: Array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} core_prog_data;

int character_counter (char *string, char *character);
int func_toprint_alias(core_prog_data *data, char *alias);
char *main_get_alias(core_prog_data *data, char *alias);
int main_set_alias(char *alias_string, core_prog_data *data);
void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int str_comparingfunc(char *string1, char *string2, int number);
int get_str_length(char *string);
char *str_duplicate(char *string);
char *str_concator(char *string1, char *string2);
void str_reversal(char *string);

int _print(char *string);
int _printit(char *string);
int _print_error(int errorcode, core_prog_data *data);

int builtin_env(core_prog_data *data);
int builtin_set_env(core_prog_data *data);
int builtin_unset_env(core_prog_data *data);

char *env_get_key(char *name, core_prog_data *data);
int env_set_key(char *key, char *value, core_prog_data *data);
int env_remove_key(char *key, core_prog_data *data);
void print_environ(core_prog_data *data);

int builtin_exit(core_prog_data *data);
int builtin_cd(core_prog_data *data);
int set_working_directory(core_prog_data *data, char *new_dir);
int builtin_helper(core_prog_data *data);
int builtin_alias(core_prog_data *data);

void free_array_of_pointers(char **directories);
void free_recurrent_data(core_prog_data *data);
void free_all_data(core_prog_data *data);

int builtins_list(core_prog_data *data);

char **tokenize_path(core_prog_data *data);
int find_program(core_prog_data *data);

int execute(core_prog_data *data);

void expand_variables(core_prog_data *data);
void expand_alias(core_prog_data *data);
int buffer_add(char *buffer, char *str_to_add);

void tokenizerfunc(core_prog_data *data);
char *_strtok(char *line, char *delim);

int _togetline(core_prog_data *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

void init_data_func(core_prog_data *data, int arc, char *argv[], char **env);
void system_info_func(char *prompt, core_prog_data *data);
void ctrl_plus_c_handler(int opr UNUSED);


/**
 * struct_builtins - Struct for the builtins,
 * @builtin: The name of the builtin,
 * @function: The associated function to be called for each builtin.
 */
typedef struct builtins
{
	char *builtins;
	int (*function)(core_prog_data *data);
} builtins;

#endif /*SHELL_H*/

