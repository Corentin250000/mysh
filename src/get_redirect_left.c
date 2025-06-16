/*
** EPITECH PROJECT, 2025
** get_redirect_left.c
** File description:
** get the left redirect
*/

#include "../include/my.h"

int get_input(local_var_t *arr, char **command, char **env, int in_fd)
{
    char *command_path = get_path(arr, command[0], env);
    int status = 0;
    pid_t pid = fork();

    if (pid == -1)
        return 1;
    if (pid == 0) {
        if (in_fd != 0) {
            dup2(in_fd, 0);
            close(in_fd);
        }
        execve(command_path, command, env);
        exit(1);
    }
    waitpid(pid, &status, 0);
    return status;
}

int get_simple_redirection_left(local_var_t *arr, char **command, char **env,
    int i)
{
    char *filepath = command[i + 1];
    int in_fd = open(filepath, O_RDONLY);
    int return_input = 0;

    if (command[0] == NULL)
        return 1;
    if (in_fd == -1)
        return 1;
    command[i] = NULL;
    return_input = get_input(arr, command, env, in_fd);
    close(in_fd);
    return return_input;
}
