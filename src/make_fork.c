/*
** EPITECH PROJECT, 2025
** make_fork.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief If needed, find the good path of the command.
* @param command the command who need to find his path
* @param all_path all path to test
* @return the good path, or if there is no good path or in case of error,
* return NULL.
*/
char *find_good_path(char const *command, char **all_path)
{
    char *path;
    int size_command;

    if (!command || !all_path)
        return NULL;
    size_command = my_strlen(command) + 2;
    for (int i = 1; all_path[i] != NULL; ++i) {
        path = malloc(sizeof(char) * (my_strlen(all_path[i]) + size_command));
        if (!path)
            return NULL;
        path = my_strcpy(path, all_path[i]);
        path = my_strcat(path, "/");
        path = my_strcat(path, command);
        if (access(path, F_OK) == -1)
            free(path);
        else
            return path;
    }
    return NULL;
}

/**
* @brief Execute all needed function before to fork.
* @param infos Main structure
* @return the good path of command or NULL if not needed or in case of error.
*/
char *prepare_fork(command_t *infos)
{
    char *path = search_variable_env(infos, "PATH=");
    char *good_path = NULL;
    char **all_path = separate_all_path(path);

    if (!all_path || !infos->command || !infos->options)
        return NULL;
    if (need_find_pathname(infos))
        good_path = find_good_path(infos->command, all_path);
    for (int i = 0; all_path[i] != NULL; ++i)
        free(all_path[i]);
    free(all_path);
    return good_path;
}

/**
* @brief Get the id of a signal in case of the child was
* terminated/stopped by signal.
* @param pid the pid of the child
* @return id of a signal or 84 if there is no signal.
*/
int get_signal(__pid_t pid)
{
    if (WIFSIGNALED(pid))
        return WTERMSIG(pid);
    if (WIFSTOPPED(pid))
        return WSTOPSIG(pid);
    return 84;
}

static int wrong_command(command_t *infos, char *good_path)
{
    if (!good_path && need_find_pathname(infos)) {
        write(2, infos->command, my_strlen(infos->command));
        write(2, ": Command not found.\n", 21);
        remove_command(infos);
        return 1;
    }
    return 0;
}

static void catch_during_exec(int sig)
{
    if (sig == SIGINT)
        return;
}

static int exec_redirection(command_t *infos, char *path)
{
    if (path)
        free(path);
    if (infos->shell_char.redirection == SIMPLE_LEFT)
        return exec_simple_left(infos);
    if (infos->shell_char.redirection == DOUBLE_LEFT)
        return 0;
    if (infos->shell_char.redirection == SIMPLE_RIGHT)
        return exec_right(infos, 1);
    if (infos->shell_char.redirection == DOUBLE_RIGHT)
        return exec_right(infos, 0);
    if (infos->shell_char.redirection == ERR_REDIRECTION)
        return exec_err_right(infos);
    return 0;
}

/**
* @brief Make the fork to execute the command.
* @param infos Main structure
* @return Return 84 in case of error with wait, 1 if there is a wrong
* command, else the function return the exit status of the child
* process.
*/
int make_fork(command_t *infos)
{
    __pid_t pid;
    char *good_path = prepare_fork(infos);

    if (wrong_command(infos, good_path))
        return 1;
    if (infos->shell_char.pipe)
        return exec_pipe(infos, good_path);
    if (infos->shell_char.redirection != NO_REDIRECTION)
        return exec_redirection(infos, good_path);
    pid = fork();
    if (pid == -1)
        return print_errno(errno);
    if (pid == 0)
        execution(infos, good_path);
    if (wait((int *) &pid) == -1)
        return 84;
    signal(SIGINT, catch_during_exec);
    print_signal_msg_final(pid, good_path);
    remove_command(infos);
    return WEXITSTATUS(pid);
}
