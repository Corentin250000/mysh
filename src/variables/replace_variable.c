/*
** EPITECH PROJECT, 2025
** replace_variable.c
** File description:
** ...
*/

#include "../../include/my.h"

static char **get_begin_new_args(char **args, int size_var, int index_call,
    int size_args)
{
    int err = 0;
    char **new_args = malloc(sizeof(char *) * (size_args + size_var));

    if (!new_args)
        return NULL;
    my_memcpy(new_args, args, sizeof(char *) * (size_args - index_call + 1));
    return new_args;
}

static char **concatenate_var_args(char **new_args, char **var, int index_call)
{
    int size_var;

    if (!new_args)
        return NULL;
    size_var = size_array(var);
    my_memcpy(&new_args[index_call], var, sizeof(char *) * (size_var + 1));
    new_args[size_var + index_call] = NULL;
    return new_args;
}

static char **concatenate_end_args(char **new_args, char **args,
    int size_var, int index_call)
{
    int size_new_args;
    int size_args;

    if (!new_args)
        return NULL;
    size_new_args = size_array(new_args);
    size_args = size_array(args);
    my_memcpy(&new_args[size_new_args], &args[index_call + 1],
        sizeof(char *) * (size_args - index_call));
    new_args[size_new_args + (size_args - index_call) - 1] = NULL;
    return new_args;
}

/**
 * @brief Replace a variable call by the variable content in command
 * @param variable All arguments of variable
 * @param args All currents arguments
 * @return The new args, with the content of variable. Return NULL if a
 * memory allocation failed.
 */
char **replace_args(char **variable, char **args)
{
    int index_call = detect_call_variable(args);
    int size_args;
    int size_var;
    char **new_args;

    if (index_call == -1)
        return args;
    if (!args)
        return NULL;
    size_args = size_array(args);
    size_var = size_array(variable);
    new_args = get_begin_new_args(args, size_var, index_call, size_args);
    new_args = concatenate_var_args(new_args, variable, index_call);
    new_args = concatenate_end_args(new_args, args, size_var, index_call);
    if (!new_args)
        return NULL;
    return new_args;
}

static char *change_command(char **new_args, char *resolved,
    int size_new_resolved)
{
    char *new_resolved = malloc(sizeof(char) * size_new_resolved);

    if (!new_resolved) {
        free_array(new_args);
        free(resolved);
        return NULL;
    }
    free(resolved);
    new_resolved = my_strcpy(new_resolved, new_args[0]);
    for (int i = 1; new_args[i] != NULL; i++) {
        new_resolved = my_strcat(new_resolved, " ");
        new_resolved = my_strcat(new_resolved, new_args[i]);
    }
    free(new_args);
    return new_resolved;
}

static char *change_args(char **args_var, char *resolved)
{
    char **args = my_str_to_word_array(resolved, " \t\n");
    char **new_args = NULL;
    int size_new_resolved = 0;

    if (!args) {
        free_array(args_var);
        free(resolved);
        return NULL;
    }
    new_args = replace_args(args_var, args);
    free(args);
    free(args_var);
    if (!new_args) {
        free(resolved);
        return resolved;
    }
    for (int i = 0; new_args[i] != NULL; i++)
        size_new_resolved += my_strlen(new_args[i]) + 1;
    return change_command(new_args, resolved, size_new_resolved);
}

static char *get_var_and_replace(local_var_t *arr, char *resolved, char *name,
    char **env)
{
    char *variable = search_variable(name, env, arr);
    char **args_var = NULL;

    free(name);
    if (!variable) {
        free(resolved);
        return NULL;
    }
    args_var = separate_variable(variable);
    if (!args_var) {
        free(variable);
        free(resolved);
        return NULL;
    }
    return change_args(args_var, resolved);
}

/**
 * @brief Replace call to variable by the content of variable
 * @param arr Structure who contain all local variables
 * @param resolved String who contain the command given by user
 * @param env All environment variables
 * @return The new command with replaced variables, or unchanged command in
 * case of error
 */
char *place_variable(local_var_t *arr, char *resolved, char **env)
{
    char **args = my_str_to_word_array(resolved, " \t\n");
    char *name = NULL;

    if (!args)
        return resolved;
    if (detect_call_variable(args) == -1) {
        free_array(args);
        return resolved;
    } else
        name = get_name_var(args);
    free_array(args);
    if (!name) {
        free(resolved);
        return NULL;
    }
    return get_var_and_replace(arr, resolved, name, env);
}
