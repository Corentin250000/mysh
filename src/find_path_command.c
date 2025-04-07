/*
** EPITECH PROJECT, 2025
** find_path_command.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Determinate if the program need to search the real pathname of the
* command given by the user.
* @param infos Main structure
* @return 1 if the program need to find the real path, else 0.
*/
int need_find_pathname(command_t *infos)
{
    if (!infos->command)
        return 84;
    if (access(infos->command, F_OK) == -1 && !infos->builtin)
        return 1;
    return 0;
}

/**
* @brief Separate all path contain in the enviroment variable PATH.
* @param path The buffer who contain all paths
* @return All separated path in a string array, or NULL in case of errors.
*/
char **separate_all_path(char const *path)
{
    char **all_path;

    if (!path)
        return NULL;
    all_path = my_str_to_word_array(path, "=:");
    if (!all_path)
        return NULL;
    return all_path;
}
