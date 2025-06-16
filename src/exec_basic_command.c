/*
** EPITECH PROJECT, 2025
** exec_basic_command.c in terminal
** File description:
** execute all basic command
*/

#include "../include/my.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

static char *get_whole_command(char *whole_command, char *temp)
{
    whole_command = malloc(my_strlen(temp) + 1);
    if (whole_command == NULL) {
        free(temp);
        return NULL;
    }
    my_strcpy(whole_command, temp);
    free(temp);
    return whole_command;
}

char *find_command_in_paths(char **paths, char *command_part,
    char *temp, char *whole_command)
{
    for (int i = 0; paths[i] != NULL; i++) {
        temp = malloc(my_strlen(paths[i]) + my_strlen(command_part) + 2);
        if (temp == NULL)
            return NULL;
        temp[0] = '\0';
        my_strcat(temp, paths[i]);
        my_strcat(temp, "/");
        my_strcat(temp, command_part);
        if (access(temp, X_OK) == 0) {
            whole_command = get_whole_command(whole_command, temp);
            break;
        }
        free(temp);
    }
    return whole_command;
}

char *get_path(local_var_t *arr, char *command, char **env)
{
    char *temp = NULL;
    char *whole_command = NULL;
    char *env_line = remove_type(arr->variables, "path=");
    char **paths = NULL;
    char *command_part = NULL;

    if (env_line == NULL || command == NULL)
        return NULL;
    paths = my_str_to_word_array(env_line, ":=\n\"\"");
    if (command[0] == '/' || (command[0] == '.' && command[1] == '/')) {
        my_strdup(command);
        return command;
    }
    return find_command_in_paths(paths, command, temp, whole_command);
}

void exec_error_handling(char *command_path, char **args, char **env)
{
    struct stat status;

    if (stat(command_path, &status) != 0) {
        error_my_putstr(args[0]);
        error_my_putstr(": Command not found.\n");
        exit(1);
    }
    if (access(command_path, X_OK) < 0 || S_ISREG(status.st_mode) != 1) {
        error_my_putstr(args[0]);
        error_my_putstr(": Permission denied.\n");
        exit(1);
    }
    if (execve(command_path, args, env) == -1) {
        error_my_putstr(args[0]);
        error_my_putstr(": Exec format error. Binary file not executable.\n");
        exit(1);
    }
}

int execute_command(local_var_t *arr, char *command, char **env)
{
    pid_t pid = fork();
    char **args = my_str_to_word_array(command, " ");
    char *command_path;
    int status = 0;

    if (!access(args[0], F_OK) && !access(args[0], X_OK))
        command_path = my_strdup(args[0]);
    else
        command_path = get_path(arr, args[0], env);
    if (pid == 0) {
        reactive_signals();
        exec_error_handling(command_path, args, env);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        get_signals(status);
        return status;
    }
    return 1;
}
