/*
** EPITECH PROJECT, 2025
** list_exec.c
** File description:
** Operation with the list of command to execute
*/

#include "../include/minishell2.h"

static char **copy_str_array(char **dest, char **src)
{
    int i = 0;

    dest = malloc(sizeof(char *) * (size_array(src) + 1));
    if (!dest)
        return NULL;
    for (; i < size_array(src); ++i)
        dest[i] = my_strdup(src[i]);
    dest[i] = NULL;
    for (int j = 0; src[j] != NULL; ++j)
        free(src[j]);
    free(src);
    return dest;
}

/**
* @brief Remove first command (command already parsed) from the execution
* list.
* @param infos Main structure
*
* @todo Fix the function -> to remove only first command and leave intact
* other command
*/
void remove_command(command_t *infos)
{
    char **temp = malloc(sizeof(char *) * (size_array(infos->execution_list)));
    int index = 0;

    if (!temp)
        return;
    for (int i = 0; infos->execution_list[i] != NULL; ++i) {
        if (i != 0) {
            temp[index] = my_strdup(infos->execution_list[i]);
            index++;
        }
    }
    temp[index] = NULL;
    for (int j = 0; infos->execution_list[j] != NULL; ++j)
        free(infos->execution_list[j]);
    free(infos->execution_list);
    infos->execution_list = copy_str_array(infos->execution_list, temp);
    infos->nb_elem_exec--;
}
