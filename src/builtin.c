/*
** EPITECH PROJECT, 2025
** builtin.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Print current environment
* @param infos Main structure
* @return 0 (no error)
*/
int my_env(command_t *infos)
{
    for (int i = 0; i < infos->size_env && infos->cpy_env[i] != NULL; ++i)
        mini_printf("%s\n", infos->cpy_env[i]);
    return 0;
}

static int nb_options(command_t *infos)
{
    int nb = 0;

    for (; infos->options[nb] != NULL; ++nb);
    return nb;
}

static char *get_home(command_t *infos)
{
    char *home = search_variable_env(infos, "HOME=");
    char **separated_variable;
    char *path_home;

    if (!home)
        return NULL;
    separated_variable = my_str_to_word_array(home, "=");
    if (!separated_variable || !separated_variable[1])
        return NULL;
    path_home = my_strdup(separated_variable[1]);
    for (int i = 0; separated_variable[i] != NULL; ++i)
        my_free(separated_variable[i]);
    my_free(separated_variable);
    return path_home;
}

static int return_to_oldpwd(command_t *infos, char *actual, char *home)
{
    int verification = 0;

    if (!infos->oldpwd) {
        write(2, ": No such file or directory.\n", 29);
        free(home);
        free(actual);
        return 0;
    }
    verification = chdir(infos->oldpwd);
    if (verification == -1) {
        free(home);
        free(actual);
        return 84;
    }
    return change_oldpwd(infos, actual, home);
}

/**
* @brief Change the current directory. If PWD don't exist in env,
* recreate it. If he exist, he just change the value of
* the new location.
* @param infos Main structure
* @return 84 in case of errors, else 0
*/
int my_cd(command_t *infos)
{
    int verification = 0;
    char *home = get_home(infos);
    char *actual = NULL;

    actual = getcwd(actual, PATH_MAX);
    if (!actual)
        return 84;
    if (nb_options(infos) == 1 || !my_strcmp(infos->options[1], "~")) {
        if (!home)
            return 0;
        verification = chdir(home);
        if (verification == -1)
            return print_errno(errno);
        return change_oldpwd(infos, actual, home);
    } else if (!my_strcmp(infos->options[1], "-"))
        return return_to_oldpwd(infos, actual, home);
    return end_cd_function(infos, actual, home);
}

static int second_part_exec_builtin(command_t *infos, int *return_value)
{
    if (!my_strcmp(infos->command, "setenv")) {
        if (size_array(infos->options) == 1)
            return my_env(infos);
        if (size_array(infos->options) < 2)
            return update_env(infos, infos->options[1], NULL);
        return update_env(infos, infos->options[1], infos->options[2]);
    }
    if (!my_strcmp(infos->command, "unsetenv")) {
        if (size_array(infos->options) < 2) {
            write(2, "unsetenv: Too few arguments.\n", 29);
            *return_value = 1;
            return 0;
        }
        infos->cpy_env = remove_variable(infos, infos->cpy_env,
            infos->options[1]);
        return 0;
    }
    return -1;
}

static void exit_code(command_t *infos, int *return_value)
{
    if (size_array(infos->options) > 1)
        *return_value = (int) ((unsigned char) my_getnbr(infos->options[1]));
}

/**
* @brief If command is a built-in command, call corresponding function
* @param infos Main structure
* @param return_value Address of an int to get the return value of program
* @return -1 in case of errors, -255 if exit built-in is given, else 0
*/
int exec_builtin(command_t *infos, int *return_value)
{
    if (!my_strcmp(infos->command, "exit")) {
        if (isatty(0))
            write(1, "exit\n", 5);
        exit_code(infos, return_value);
        return -255;
    }
    if (!my_strcmp(infos->command, "cd")) {
        if (size_array(infos->options) > 2) {
            write(2, "cd: Too many arguments.\n", 24);
            *return_value = 1;
            return 0;
        }
        *return_value = 0;
        return my_cd(infos);
    }
    if (!my_strcmp(infos->command, "env")) {
        *return_value = 0;
        return my_env(infos);
    }
    return second_part_exec_builtin(infos, return_value);
}
