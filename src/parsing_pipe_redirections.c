/*
** EPITECH PROJECT, 2025
** parsing_pipe_redirections.c
** File description:
** ...
*/

#include "../include/minishell2.h"

void free_array(char **arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i] != NULL; ++i)
        free(arr[i]);
    free(arr);
}

/*
Also work with redirections
*/
static char **separate_command_pipe(command_t *infos)
{
    char **temp = NULL;

    if (infos->shell_char.pipe == 1 &&
        infos->shell_char.redirection == NO_REDIRECTION)
            temp = my_str_to_word_array(infos->execution_list[0], "|");
    if (infos->shell_char.redirection == SIMPLE_LEFT ||
        infos->shell_char.redirection == DOUBLE_LEFT)
            temp = my_str_to_word_array(infos->execution_list[0], "<");
    if (infos->shell_char.redirection == SIMPLE_RIGHT ||
        infos->shell_char.redirection == DOUBLE_RIGHT)
            temp = my_str_to_word_array(infos->execution_list[0], ">");
    if (infos->shell_char.redirection == ERR_REDIRECTION)
            temp = my_str_to_word_array(infos->execution_list[0], "2>");
    if (size_array(temp) < 2) {
        free_array(temp);
        return NULL;
    }
    return temp;
}

static void *free_commands_error(pipe_t *pipe_struct)
{
    if (pipe_struct->first_command)
        free(pipe_struct->first_command);
    if (pipe_struct->second_command)
        free(pipe_struct->second_command);
    free(pipe_struct);
    return NULL;
}

/**
 * @brief Parse the command from execution list to separate commands, separated
 * by a pipe ('|') or a redirection ('<', '<<', '>' or '>>').
 * @param Main structure
 * @return A structure who contain both commands, or NULL in case of error.
 * @todo Parsing of list_exec[0] -> put result in pipe_t structure
 * the structure contain the first command (redirection of stdout to the write
 * fd of pipe), the second command (redirection of read fd from pipe to stdin),
 * the first fd to redirect to fd[1] (write) and the second fd to redirect to
 * fd[0] (read).
 * fd[0] and fd[1] are int fd[2]; to give to pipe()
 */
pipe_t *parsing_pipe_redirection(command_t *infos)
{
    pipe_t *pipe_struct;
    char **temp;

    if (infos->shell_char.redirection == ERROR)
        return NULL;
    pipe_struct = malloc(sizeof(pipe_t));
    if (!pipe_struct)
        return NULL;
    temp = separate_command_pipe(infos);
    if (!temp) {
        free(pipe_struct);
        return NULL;
    }
    pipe_struct->first_command = my_strdup(temp[0]);
    pipe_struct->second_command = my_strdup(temp[1]);
    free_array(temp);
    if (!pipe_struct->first_command || !pipe_struct->second_command)
        return free_commands_error(pipe_struct);
    return separate_commands_options(pipe_struct) == 84 ? NULL : pipe_struct;
}
