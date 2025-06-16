/*
** EPITECH PROJECT, 2024
** B-PSU-200-MLH-2-1-42sh-anastasija.potapova
** File description:
** call_builtin.c
*/
#include <unistd.h>
#include <stdio.h>
#include "../../include/my.h"

int builtin_setenv(local_var_t *arr, char **command, char **env)
{
    (void)arr;
    if (command[1] == NULL) {
        my_show_word_array(env);
        return 0;
    }
    if (command[2] == NULL)
        get_setenv(command[1], env, "");
    else
        get_setenv(command[1], env, command[2]);
    return 0;
}

int builtin_unsetenv(local_var_t *arr, char **command, char **env)
{
    (void)arr;
    if (command[1] == NULL) {
        error_my_putstr("unsetenv: Too few arguments.\n");
        return 1;
    }
    get_unsetenv(env, command[1]);
    return 0;
}

int builtin_exit(local_var_t *arr, char **command, char **env)
{
    (void)arr;
    (void)command;
    (void)env;
    if (isatty(0))
        mini_printf("exit\n");
    exit(EXIT_SUCCESS);
    return 0;
}

int builtin_cd(local_var_t *arr, char **command, char **env)
{
    (void)arr;
    if (cmp_exact_line(command[0], "cd -") == 0)
        return get_cd_minus(env);
    return get_cd(command[0], env);
}
