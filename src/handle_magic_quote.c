/*
** EPITECH PROJECT, 2025
** get_prompt.c
** File description:
** get a shell prompt
*/

#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"

static void exec_child(local_var_t *arr, char **cmd, char **env, int fd)
{
    close(STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execve(get_path(arr, cmd[0], env), cmd, env);
    exit(1);
}

static char *init_output_buffer(void)
{
    char *output = malloc(sizeof(char));

    if (!output)
        return NULL;
    output[0] = '\0';
    return output;
}

static int get_output(char **output, char *buffer,
    size_t *output_len, ssize_t bytes)
{
    char *new_output = realloc(*output, *output_len + bytes + 1);

    if (!new_output) {
        free(*output);
        return -1;
    }
    *output = new_output;
    my_strcpy(*output + *output_len, buffer);
    *output_len += bytes;
    return 0;
}

char *collect_output(int read_fd)
{
    char buffer[1024];
    char *output = init_output_buffer();
    size_t output_len = 0;
    ssize_t bytes;

    if (!output)
        return NULL;
    bytes = read(read_fd, buffer, sizeof(buffer) - 1);
    while (bytes > 0) {
        buffer[bytes] = '\0';
        if (get_output(&output, buffer, &output_len, bytes) == -1)
            return NULL;
        bytes = read(read_fd, buffer, sizeof(buffer) - 1);
    }
    if (output_len > 0 && output[output_len - 1] == '\n')
        output[output_len - 1] = '\0';
    return output;
}

char *get_magic_quote_output(local_var_t *arr, char *cmd_str, char **env)
{
    int pipefd[2];
    pid_t pid;
    char **cmd = my_str_to_word_array(cmd_str, " \t\n");
    char *output = NULL;

    if (pipe(pipefd) == -1)
        return NULL;
    pid = fork();
    if (pid == -1)
        return NULL;
    if (pid == 0)
        exec_child(arr, cmd, env, pipefd[1]);
    close(pipefd[1]);
    output = collect_output(pipefd[0]);
    close(pipefd[0]);
    waitpid(pid, NULL, 0);
    return output;
}

char *replace_magic_quote(char *cmd, char *start, char *end, char *output)
{
    size_t prefix_len = start - cmd;
    size_t suffix_len = my_strlen(end + 1);
    size_t total_len = prefix_len + my_strlen(output) + suffix_len + 1;
    char *result = malloc(sizeof(char) * total_len);

    if (!result)
        return NULL;
    strncpy(result, cmd, prefix_len);
    result[prefix_len] = '\0';
    my_strcat(result, output);
    my_strcat(result, end + 1);
    return result;
}

char *handle_single_magic_quote(local_var_t *arr, char *start, char *end,
    pipe_t cmd_env)
{
    char *sub_cmd = NULL;
    char *output = NULL;
    char *temp = NULL;

    *end = '\0';
    sub_cmd = start + 1;
    if ((end - start - 1) == 0)
        return replace_magic_quote(cmd_env.command, start, end, "");
    output = get_magic_quote_output(arr, sub_cmd, cmd_env.env);
    if (!output)
        return cmd_env.command;
    for (size_t i = 0; output[i]; i++) {
        if (output[i] == '\n')
            output[i] = ' ';
    }
    temp = replace_magic_quote(cmd_env.command, start, end, output);
    free(cmd_env.command);
    free(output);
    return temp;
}

char *apply_magic_quotes(local_var_t *arr, char *command, char **env)
{
    char *new_cmd = my_strdup(command);
    pipe_t cmd_env;

    if (!new_cmd)
        return NULL;
    while (strchr(new_cmd, '`') && strchr(strchr(new_cmd, '`') + 1, '`')) {
        cmd_env.command = new_cmd;
        cmd_env.env = env;
        new_cmd = handle_single_magic_quote(arr, strchr(new_cmd, '`'),
            strchr(strchr(new_cmd, '`') + 1, '`'), cmd_env);
    }
    return new_cmd;
}
