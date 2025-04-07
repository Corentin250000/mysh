/*
** EPITECH PROJECT, 2025
** ask_command.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Print the error message according to the error code
* @param error_value Errno value
* @return 84 (error code)
*/
int print_errno(int error_value)
{
    perror(strerror(error_value));
    return 84;
}

/**
* @brief Separate commands separated by semicolons
* @param line String who contain commands line given by user
* @return A string array who contain all separated commands
*/
void separate_command_single_line(char const *line, command_t *infos)
{
    if (!line)
        return;
    infos->execution_list = my_str_to_word_array(line, ";");
    if (infos->execution_list)
        infos->nb_elem_exec = nb_word(line, ";");
}

/**
* @brief Read all command given to program via a pipe
* @param infos Main structure
* @return Number of readed characters, or -1 in case of errors
*/
ssize_t read_command_pipe(command_t *infos)
{
    size_t size = 32000;
    ssize_t characters = 0;
    char *buffer = NULL;

    characters = getline(&buffer, &size, stdin);
    if (characters == -1) {
        if (buffer)
            free(buffer);
        return -1;
    }
    infos->complete_command = my_strdup(buffer);
    if (!infos->complete_command) {
        free(buffer);
        return print_errno(errno);
    }
    free(buffer);
    separate_command_single_line(infos->complete_command, infos);
    return !infos->execution_list ? print_errno(errno) : characters;
}

/**
* @brief Read all commands given to program, via a pipe or given by user
* directly
* @param infos Main structure
* @return If program is used via a pipe, return the number of readed
* characters. Else, it returns 0 or -1 in case of errors.
*/
int ask_command(command_t *infos)
{
    size_t size = 32000;
    ssize_t characters = 0;
    char *buffer = NULL;

    if (!isatty(0))
        return (int) read_command_pipe(infos);
    mini_printf("$> ");
    characters = getline(&buffer, &size, stdin);
    if (characters == -1) {
        if (buffer)
            free(buffer);
        return -1;
    }
    infos->complete_command = my_strdup(buffer);
    free(buffer);
    if (!infos->complete_command)
    return print_errno(errno);
    separate_command_single_line(infos->complete_command, infos);
    return !infos->execution_list ? print_errno(errno) : 0;
}
