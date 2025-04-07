/*
** EPITECH PROJECT, 2025
** execution.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Put the action of SIGINT to default. Execute the command.
* @param infos Main structure
* @param good_path Real path of command, if needed
*/
void execution(command_t *infos, char const *good_path)
{
    signal(SIGINT, SIG_DFL);
    if (infos->builtin || !infos->options || !infos->cpy_env)
        return;
    if (!good_path) {
        execve(infos->command, infos->options, infos->cpy_env);
        return;
    }
    execve(good_path, infos->options, infos->cpy_env);
}
