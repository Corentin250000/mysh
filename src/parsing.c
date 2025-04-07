/*
** EPITECH PROJECT, 2025
** parsing.c
** File description:
** Parsing of the command
*/

#include "../include/minishell2.h"

/**
* @brief Determinate if the command (in the structure) is a built-in or not.
* @param infos Main structure
* @return 1 if the command is a built-in command, 0 else.
*/
int is_builtin(command_t *infos)
{
    if (!my_strcmp(infos->command, "cd") || !my_strcmp(infos->command, "exit")
        || !my_strcmp(infos->command, "setenv") ||
        !my_strcmp(infos->command, "unsetenv") ||
        !my_strcmp(infos->command, "env"))
            return 1;
    return 0;
}

/**
* @brief Search for all shell characters (pipe and redirections)
* @param infos Main structure
* @note If no redirection is found, the value of infos->shell_char.redirection
* is NO_REDIRECTION. If there is no pipe, the value of infos->shell_char.pipe
* is 0.
*/
void search_shell_char(command_t *infos)
{
    infos->shell_char.redirection = NO_REDIRECTION;
    infos->shell_char.pipe = 0;
    if (!infos->execution_list)
        return;
    if (my_strstr(infos->execution_list[0], "|"))
        infos->shell_char.pipe = 1;
    if (my_strstr(infos->execution_list[0], "<<"))
        infos->shell_char.redirection = DOUBLE_LEFT;
    else if (my_strstr(infos->execution_list[0], "<"))
        infos->shell_char.redirection = SIMPLE_LEFT;
    if (my_strstr(infos->execution_list[0], ">>"))
        infos->shell_char.redirection = DOUBLE_RIGHT;
    else if (my_strstr(infos->execution_list[0], ">"))
        infos->shell_char.redirection = SIMPLE_RIGHT;
    if (my_strstr(infos->execution_list[0], "2>"))
        infos->shell_char.redirection = ERR_REDIRECTION;
    if (infos->shell_char.redirection == SIMPLE_LEFT &&
        infos->shell_char.pipe == 1) {
            infos->shell_char.redirection = ERROR;
            infos->shell_char.pipe = 0;
            write(2, "Ambiguous input redirect.\n", 26);
        }
}

/**
* @brief Separate the command given by user into the command and the options.
* @param infos Main structure
* @return 84 in case of errors, 1 if the command is empty, 0 else.
*/
int parsing_command(command_t *infos)
{
    if (!infos->execution_list || !infos->execution_list[0])
        return 84;
    if (my_strlen(infos->execution_list[0]) == 1)
        return 1;
    search_shell_char(infos);
    if (infos->shell_char.redirection == ERROR)
        return 1;
    infos->options = my_str_to_word_array(infos->execution_list[0],
        " \n\t");
    if (!infos->options)
        return 84;
    infos->command = my_strdup(infos->options[0]);
    if (!infos->command)
        return 84;
    infos->builtin = is_builtin(infos);
    if (infos->builtin)
        remove_command(infos);
    return 0;
}
