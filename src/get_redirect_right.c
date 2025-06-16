/*
** EPITECH PROJECT, 2025
** get_redirect_right.c
** File description:
** get the right redirect
*/

#include "../include/my.h"

int get_output(local_var_t *arr, char **command, char **env, int out_fd)
{
    char *command_path = get_path(arr, command[0], env);
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        if (out_fd != 1) {
            dup2(out_fd, 1);
            close(out_fd);
        }
        execve(command_path, command, env);
        exit(1);
    }
    waitpid(pid, &status, 0);
    return status;
}

int get_simple_redirection(local_var_t *arr, char **command, char **env, int i)
{
    char *filepath = command[i + 1];
    int out_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int return_output = 0;

    if (command[0] == NULL || filepath == NULL)
        return 1;
    if (out_fd == -1)
        return 1;
    command[i] = NULL;
    return_output = get_output(arr, command, env, out_fd);
    close(out_fd);
    return return_output;
}

int get_double_redirection(local_var_t *arr, char **command, char **env, int i)
{
    char *filepath = command[i + 1];
    int out_fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
    int return_output = 0;

    if (command[0] == NULL || filepath == NULL)
        return 1;
    if (out_fd == -1)
        return 1;
    command[i] = NULL;
    return_output = get_output(arr, command, env, out_fd);
    close(out_fd);
    return return_output;
}

char **check_error_redirection(char *line)
{
    int i = 0;
    char **tab_redirection = NULL;

    while (line[i] != '\0') {
        if (line[i] == '2' && line[i + 1] == '>') {
            tab_redirection = my_str_to_word_array(line, "2>");
            return tab_redirection;
        }
        i++;
    }
    return NULL;
}

int redirection_error(local_var_t *arr, char *line, char **env)
{
    int fd;
    pid_t pid;
    int res_status = 0;
    char **redirection_info = check_error_redirection(line);

    if (redirection_info == NULL || redirection_info[1] == NULL)
        return 1;
    redirection_info[1] = my_strdup(str_clean(redirection_info[1]));
    fd = open(redirection_info[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
    pid = fork();
    if (pid == 0) {
        dup2(fd, STDERR_FILENO);
        parser(arr, str_clean(redirection_info[0]), env);
        close(fd);
        exit(0);
    }
    waitpid(pid, &res_status, 0);
    return 0;
}
