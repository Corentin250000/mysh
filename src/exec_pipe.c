/*
** EPITECH PROJECT, 2025
** exec_pipe_redirection.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Determinate if the program need to search the real pathname of the
* command given by the user.
* @param name Name of command
* @return 1 if the program need to find the real path, else 0.
* @note Only for pipes and redirections, for other case, see
* need_find_pathname().
*/
int need_find_pathname_pipe(char const *name)
{
    if (!name)
        return 84;
    if (!my_strcmp(name, "cd") || !my_strcmp(name, "exit")
        || !my_strcmp(name, "setenv") ||
        !my_strcmp(name, "unsetenv") ||
        !my_strcmp(name, "env"))
            return 0;
    if (access(name, F_OK) == -1)
        return 1;
    return 0;
}

/**
 * @brief Separate both commands to create a char ** who contain commands with
 * their options.
 * @param pipe_struct The special structure in case of there are pipes or
 * redirections in the command
 * @return 84 in case of errors, 0 else.
 * @note Both complete command are free'd, even in case of error.
 *
 * @note In case of error, both char ** are free'd.
 */
int separate_commands_options(pipe_t *pipe_struct)
{
    pipe_struct->options_first_command = my_str_to_word_array(pipe_struct->
        first_command, " \n\t|<>");
    pipe_struct->options_second_command = my_str_to_word_array(pipe_struct->
        second_command, " \n\t|<>");
    free(pipe_struct->first_command);
    free(pipe_struct->second_command);
    if (!pipe_struct->options_first_command ||
        !pipe_struct->options_second_command) {
            free_array(pipe_struct->options_first_command);
            free_array(pipe_struct->options_second_command);
            pipe_struct->options_first_command = NULL;
            pipe_struct->options_second_command = NULL;
            return 84;
    }
    return 0;
}

static void do_second_fork(int *second_pid, int fd[2], pipe_t *pipe_struct,
    command_t *infos)
{
    *second_pid = fork();
    if (*second_pid == -1)
        return;
    if (*second_pid == 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execve(pipe_struct->second_correct_path,
            pipe_struct->options_second_command, infos->cpy_env);
    }
}

static int fork_pipe(pipe_t *pipe_struct, command_t *infos, int fd[2])
{
    pid_t first_pid = fork();
    pid_t second_pid = 0;

    if (first_pid == -1)
        return 84;
    if (first_pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(pipe_struct->first_correct_path,
            pipe_struct->options_first_command, infos->cpy_env);
    }
    do_second_fork(&second_pid, fd, pipe_struct, infos);
    if (second_pid == -1)
        return 84;
    close(fd[0]);
    close(fd[1]);
    waitpid(first_pid, NULL, 0);
    waitpid(second_pid, NULL, 0);
    return WEXITSTATUS(second_pid);
}

void free_pipe(pipe_t *pipe_struct)
{
    if (!pipe_struct)
        return;
    if (pipe_struct->first_correct_path)
        free(pipe_struct->first_correct_path);
    if (pipe_struct->second_correct_path)
        free(pipe_struct->second_correct_path);
    if (pipe_struct->options_first_command) {
        for (int i = 0; pipe_struct->options_first_command[i] != NULL; i++)
            free(pipe_struct->options_first_command[i]);
        free(pipe_struct->options_first_command);
    }
    if (pipe_struct->options_second_command) {
        for (int i = 0; pipe_struct->options_second_command[i] != NULL; i++)
            free(pipe_struct->options_second_command[i]);
        free(pipe_struct->options_second_command);
    }
    free(pipe_struct);
}

/**
 * @brief Execute the command with when there is a pipe.
 * @param infos Main structure
 * @param path String to free
 * @return 84 in case of error, 0 else.
 */
int exec_pipe(command_t *infos, char *path)
{
    int fd[2];
    pipe_t *pipe_struct = parsing_pipe_redirection(infos);

    if (pipe(fd) == -1)
        return 84;
    if (search_fill_correct_path(pipe_struct, infos) == 84)
        return 84;
    if (fork_pipe(pipe_struct, infos, fd) == 84)
        return 84;
    free_pipe(pipe_struct);
    if (path)
        free(path);
    remove_command(infos);
    return 0;
}
