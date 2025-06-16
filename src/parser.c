/*
** EPITECH PROJECT, 2025
** parser.c
** File description:
** parsing given functions
*/

#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"

static const struct builtin_cmd BUILTINS[] = {
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"exit", builtin_exit},
    {"history", builtin_history},
    {"where", create_where},
    {"which", create_which},
    {"if", create_if},
    {"set", builtin_set},
    {"unset", builtin_unset},
    {NULL, NULL}
};

static int check_builtins(local_var_t *arr, char **args, char **env)
{
    for (int i = 0; BUILTINS[i].name != NULL; i++) {
        if (cmp_exact_line(args[0], BUILTINS[i].name) == 0)
            return BUILTINS[i].func(arr, args, env);
    }
    return 2;
}

static int redirection_error_handling(char **command_tab, int *i)
{
    if (command_tab[*i + 1] == NULL) {
        error_my_putstr("Missing name for redirect.\n");
        exit(1);
    }
    return 0;
}

int redirection_cases_right(local_var_t *arr, char **command_tab, char **env,
    char *command)
{
    for (int i = 0; command_tab[i] != NULL; i++) {
        if (my_strncmp(command_tab[i], ">>", 2) == 0) {
            redirection_error_handling(command_tab, &i);
            return get_double_redirection(arr, command_tab, env, i);
        }
        if (my_strncmp(command_tab[i], ">", 1) == 0) {
            redirection_error_handling(command_tab, &i);
            return get_simple_redirection(arr, command_tab, env, i);
        }
        if (my_strncmp(command_tab[i], "<", 1) == 0) {
            redirection_error_handling(command_tab, &i);
            return get_simple_redirection_left(arr, command_tab, env, i);
        }
        if (my_strncmp(command_tab[i], "2>", 2) == 0) {
            redirection_error_handling(command_tab, &i);
            return redirection_error(arr, command, env);
        }
    }
    return 1;
}

int parser(local_var_t *arr, char *command, char **env)
{
    char **args = NULL;
    int value = 0;

    if (cmp_exact_line(command, "cd -") == 0) {
        return get_cd_minus(env);
    } else if (my_strncmp(command, "cd", 2) == 0)
        return get_cd(command, env);
    args = my_str_to_word_array(command, " ");
    if (alias(command) == 0 ||
    check_exec(arr, command, env) == 0)
        return 0;
    value = check_builtins(arr, args, env);
    if (value != 2)
        return value;
    value = redirection_cases_right(arr, args, env, command);
    if (value != 1)
        return value;
    return execute_command(arr, command, env);
}
