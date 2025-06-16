/*
** EPITECH PROJECT, 2025
** get_special_variables.c
** File description:
** ...
*/

#include "../../include/my.h"

static char **build_args(char const *varname, char const *content)
{
    char **args = malloc(sizeof(char *) * 3);

    if (!args || !varname || !content)
        return NULL;
    args[0] = my_strdup("set");
    args[1] = malloc(sizeof(char) * (my_strlen(varname) + my_strlen(content)
        + 2));
    if (!args[1]) {
        return NULL;
        free(args);
    }
    args[1] = my_strcpy(args[1], varname);
    args[1] = my_strcat(args[1], "=");
    args[1] = my_strcat(args[1], content);
    return args;
}

static void get_path_special(local_var_t *arr, char **env)
{
    char *content = NULL;
    char **args;

    content = remove_type(env, "PATH=");
    if (!content)
        return;
    args = build_args("path", content);
    if (!args)
        return;
    builtin_set(arr, args, env);
    free_array(args);
}

static void get_home_special(local_var_t *arr, char **env)
{
    char *content = NULL;
    char **args;

    content = remove_type(env, "HOME=");
    if (!content)
        return;
    args = build_args("home", content);
    if (!args)
        return;
    builtin_set(arr, args, env);
    free_array(args);
}

void get_special_var(local_var_t *arr, char **env)
{
    char **args;

    if (!env) {
        args = build_args("path", "/usr/bin:/bin");
        if (!args)
            return;
        builtin_set(arr, args, env);
        free(args);
        return;
    }
    get_path_special(arr, env);
    get_home_special(arr, env);
}
