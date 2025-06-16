/*
** EPITECH PROJECT, 2025
** get_pipes.c
** File description:
** get the pipes
*/

#include "../include/my.h"

int execute_first_command(local_var_t *arr, pipe_t com_env, int in_fd,
    int out_fd)
{
    char **command = my_str_to_word_array(com_env.command, " \t");
    char *command_path = get_path(arr, command[0], com_env.env);
    pid_t pid = fork();

    if (pid == 0) {
        if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        execve(command_path, command, com_env.env);
        exit(1);
    }
    return pid;
}

int get_nb_commands(char **commands)
{
    int nb_cmd = 0;

    while (commands[nb_cmd] != NULL)
        nb_cmd++;
    return nb_cmd;
}

int return_pipe_fd_error(int pipe_fd[2])
{
    if (pipe(pipe_fd) == -1)
        return 84;
    return 0;
}

static void wait_children(pid_t *pids, int nb_cmd)
{
    for (int i = 0; i < nb_cmd; i++)
        waitpid(pids[i], NULL, 0);
    free(pids);
}

int handle_piped_commands(local_var_t *arr, char **commands, char **env)
{
    int nb_cmd = get_nb_commands(commands);
    int pipe_fd[2];
    int input_fd = STDIN_FILENO;
    pid_t *pids = malloc(nb_cmd * sizeof(pid_t));
    pipe_t com_env;

    for (int i = 0; i < nb_cmd; i++) {
        if (i < nb_cmd - 1)
            return_pipe_fd_error(pipe_fd);
        com_env.command = commands[i];
        com_env.env = env;
        pids[i] = execute_first_command(arr, com_env, input_fd,
            (i < nb_cmd - 1) ? pipe_fd[1] : STDOUT_FILENO);
        if (i < nb_cmd - 1) {
            close(pipe_fd[1]);
            input_fd = pipe_fd[0];
        }
    }
    wait_children(pids, nb_cmd);
    return 0;
}

int process_piped_input(local_var_t *arr, char *input_line, char **env)
{
    char **commands = my_str_to_word_array(input_line, "|");

    if (commands[1] == NULL)
        return 1;
    handle_piped_commands(arr, commands, env);
    return 0;
}
