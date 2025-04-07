/*
** EPITECH PROJECT, 2025
** command.c
** File description:
** ...
*/

#include "../include/minishell2.h"

static void free_each_command(command_t *infos)
{
    if (infos == NULL)
        return;
    if (infos->command != NULL)
        my_free(infos->command);
    if (infos->options != NULL) {
        for (int i = 0; infos->options[i] != NULL; ++i)
            my_free(infos->options[i]);
        my_free(infos->options);
    }
}

static int do_fork(int verification, command_t *infos)
{
    if (verification == -1) {
        verification = make_fork(infos);
        if (verification == 84)
            return 84;
    }
    return verification;
}

/**
* @brief Ask for a command (or read in case of use via a pipe).
* Make the parsing of the command.
* If the command is builtin, the program execute it without
* fork and return. If the command is not a builtin,
* the program fork and execute the command and
* return according to return value of the function who do the fork.
* @param infos Main structure
* @param return_value Address of an int to get the return value of the
* command
* @return 84 in case of errors, -1 if getline has reached EOF or has
* occur an error or if exec_builtin was executed without built-in
* command, else 0.
*/
int command(command_t *infos, int *return_value)
{
    int verification = 0;

    verification = ask_command(infos);
    if (verification == -1 || verification == 84)
        return verification;
    while (infos->nb_elem_exec > 0) {
        verification = parsing_command(infos);
        if (verification == 84 || verification == 1)
            return verification;
        verification = exec_builtin(infos, return_value);
        if (verification == -255)
            return verification;
        verification = do_fork(verification, infos);
        if (verification == 84)
            return 84;
        *return_value = verification;
        if (my_strstr(infos->complete_command, ";") && infos->nb_elem_exec > 0)
            free_each_command(infos);
    }
    return 0;
}
