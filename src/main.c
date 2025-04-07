/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** Main file
*/

#include "../include/minishell2.h"

static int after_loop_program(int verification, int return_value,
    command_t *infos)
{
    if (!isatty(0) && verification != 84)
        return final_free_structure(infos, return_value);
    else if (verification == -255 && isatty(0))
        return final_free_structure(infos, return_value);
    return error_free_structure(infos, 84);
}

int main(int ac, char **av, char **env)
{
    int verification = 0;
    int return_value = 0;
    command_t *infos = copy_env(env, ac);

    if (!infos)
        return 84;
    signal(SIGINT, SIG_IGN);
    while (verification != -255 && verification != 84) {
        verification = command(infos, &return_value);
        if (verification == 84)
            return error_free_structure(infos, 84);
        if (!isatty(0) && verification == -1)
            break;
        free_content_structure(infos);
    }
    return after_loop_program(verification, return_value, infos);
}
