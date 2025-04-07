/*
** EPITECH PROJECT, 2025
** exec_redirection.c
** File description:
** ...
*/

#include "../include/minishell2.h"

static int no_need_search(pipe_t *pipe_struct)
{
    if (!need_find_pathname_pipe(pipe_struct->options_first_command[0])) {
        pipe_struct->first_correct_path = my_strdup(pipe_struct->
            options_first_command[0]);
        if (!pipe_struct->first_correct_path)
            return 84;
        if (!need_find_pathname_pipe(pipe_struct->options_second_command[0]))
            pipe_struct->second_correct_path = my_strdup(pipe_struct->
                options_second_command[0]);
        if (!need_find_pathname_pipe(pipe_struct->options_second_command[0]) &&
            !pipe_struct->first_correct_path)
                return 84;
        return 1;
    }
    return 0;
}

/**
 * @brief Search correct path for command in pipe_t structure
 * @param pipe_struct Structure for pipes and redirections
 * @param infos Main structure
 * @return 84 in case of error, 0 else
 */
int search_fill_correct_path(pipe_t *pipe_struct, command_t *infos)
{
    char *path;
    char **all_path;
    int no_search = no_need_search(pipe_struct);

    if (no_search == 84)
        return 84;
    else if (no_search == 1)
        return 0;
    path = search_variable_env(infos, "PATH=");
    if (!path)
        return 84;
    all_path = separate_all_path(path);
    if (!all_path)
        return 84;
    pipe_struct->first_correct_path = find_good_path(pipe_struct->
        options_first_command[0], all_path);
    pipe_struct->second_correct_path = find_good_path(pipe_struct->
        options_second_command[0], all_path);
    free_array(all_path);
    return 0;
}

/**
 * @note fd is close only if the fork has not failed.
 */
static int fork_right_redirection(command_t *infos, pipe_t *pipe_struct,
    int fd)
{
    int pid = fork();

    if (pid == -1)
        return 84;
    if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execve(pipe_struct->first_correct_path,
            pipe_struct->options_first_command, infos->cpy_env);
    }
    close(fd);
    waitpid(pid, NULL, 0);
    return WEXITSTATUS(pid);
}

static int right_redirection(command_t *infos, pipe_t *pipe_struct, int simple)
{
    int fd;

    if (simple == 1)
        fd = open(pipe_struct->options_second_command[0],
            O_WRONLY | O_TRUNC | O_CREAT, 0777);
    else
        fd = open(pipe_struct->options_second_command[0],
            O_WRONLY | O_APPEND | O_CREAT, 0777);
    if (fd == -1)
        return 84;
    if (fork_right_redirection(infos, pipe_struct, fd) == 84)
        return 84;
    return 0;
}

/**
 * @brief Execute the command with when there is a simple right redirection.
 * @param infos Main structure
 * @param path String to free
 * @param simple Is a simple (1) or a double redirection (0)
 * @return 84 in case of error, 0 else.
 */
int exec_right(command_t *infos, int simple)
{
    pipe_t *pipe_struct = parsing_pipe_redirection(infos);

    if (search_fill_correct_path(pipe_struct, infos) == 84)
        return 84;
    if (right_redirection(infos, pipe_struct, simple) == 84)
        return 84;
    free_pipe(pipe_struct);
    remove_command(infos);
    return 0;
}

int exec_err_right(command_t *infos)
{
    pipe_t *pipe_struct = parsing_pipe_redirection(infos);
    int fd;
    int pid;

    if (search_fill_correct_path(pipe_struct, infos) == 84)
        return 84;
    fd = open(pipe_struct->options_second_command[0],
        O_WRONLY | O_TRUNC | O_CREAT, 0777);
    pid = fork();
    if (pid == -1)
        return 84;
    if (pid == 0) {
            dup2(fd, STDERR_FILENO);
            close(fd);
            execve(pipe_struct->first_correct_path,
                pipe_struct->options_first_command, infos->cpy_env);
    }
        close(fd);
        waitpid(pid, NULL, 0);
        pid = WEXITSTATUS(pid);
    free_pipe(pipe_struct);
    remove_command(infos);
    return pid;
}

/**
 * @note fd is close only if the fork has not failed.
 */
static int fork_left_redirection(command_t *infos, pipe_t *pipe_struct,
    int fd)
{
    int pid = fork();

    if (pid == -1)
        return 84;
    if (pid == 0) {
        dup2(fd, STDIN_FILENO);
        close(fd);
        execve(pipe_struct->first_correct_path,
            pipe_struct->options_first_command, infos->cpy_env);
    }
    waitpid(pid, NULL, 0);
    return WEXITSTATUS(pid);
}

static int left_redirection(command_t *infos, pipe_t *pipe_struct)
{
    int fd = open(pipe_struct->options_second_command[0], O_RDONLY);

    if (fd == -1)
        return 84;
    if (fork_left_redirection(infos, pipe_struct, fd) == 84)
        return 84;
    return 0;
}

/**
 * @brief Execute the command with when there is a simple right redirection.
 * @param infos Main structure
 * @param path String to free
 * @return 84 in case of error, 0 else.
 */
int exec_simple_left(command_t *infos)
{
    pipe_t *pipe_struct = parsing_pipe_redirection(infos);
    struct stat s;

    if (search_fill_correct_path(pipe_struct, infos) == 84)
        return 84;
    if (lstat(pipe_struct->options_second_command[0], &s) == -1) {
        write(2, pipe_struct->options_second_command[0],
            my_strlen(pipe_struct->options_second_command[0]));
        write(2, ": No such file or directory.\n", 29);
        free_pipe(pipe_struct);
        remove_command(infos);
        return 0;
    }
    if (left_redirection(infos, pipe_struct) == 84)
        return 84;
    free_pipe(pipe_struct);
    remove_command(infos);
    return 0;
}
