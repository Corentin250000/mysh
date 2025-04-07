/*
** EPITECH PROJECT, 2025
** parsing_path.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Search a variable into the environment.
* @param infos Main structure
* @param variable The variable to search
* @return The complete line of the variable, or NULL if not found or in case
* of errors.
* @warning If variable is found no need to free the result.
*/
char *search_variable_env(command_t *infos, char const *variable)
{
    int size_variable = my_strlen(variable);
    int has_found = 0;
    int i = 0;

    if (!size_variable)
        return NULL;
    for (; infos->cpy_env[i] != NULL; ++i) {
        if (!my_strncmp(infos->cpy_env[i], variable, size_variable)) {
            has_found = 1;
            break;
        }
    }
    return has_found ? infos->cpy_env[i] : NULL;
}
