/*
** EPITECH PROJECT, 2025
** if.c
** File description:
** function to recreate the shell if
*/

#include "../include/my.h"

int is_builtin(char *command)
{
    static const char *builtins[] = {
        "cd", "exit",
        "setenv", "unsetenv",
        "history", "echo",
        "set", "unset",
        NULL
    };

    for (int i = 0; builtins[i]; i++) {
        if (cmp_exact_line(command, builtins[i]) == 0)
            return 1;
    }
    return 0;
}

char **get_env_paths(char **env)
{
    char *env_line = remove_type(env, "PATH=");

    if (!env_line)
        return NULL;
    return my_str_to_word_array(env_line, ":=\n\"\"");
}

char *create_full_path(char *dir, char *command)
{
    int len = my_strlen(dir) + my_strlen(command) + 2;
    char *full_path = malloc(sizeof(char) * len);

    if (full_path == NULL)
        return NULL;
    full_path[0] = '\0';
    my_strcat(full_path, dir);
    my_strcat(full_path, "/");
    my_strcat(full_path, command);
    return full_path;
}

int print_corresponding_paths(char *command, char **paths)
{
    char *full_path = NULL;
    int found = 0;

    for (int i = 0; paths[i] != NULL; i++) {
        full_path = create_full_path(paths[i], command);
        if (full_path == NULL)
            continue;
        if (access(full_path, X_OK) == 0) {
            my_putstr(full_path);
            my_putchar('\n');
            found = 1;
        }
        free(full_path);
    }
    return found;
}

int create_where(local_var_t *arr, char **args, char **env)
{
    char **paths = get_env_paths(env);
    int found;

    (void)arr;
    if (!paths)
        return 1;
    for (int i = 1; args[i] != NULL; i++) {
        found = 0;
        if (is_builtin(args[i])) {
            my_putstr(args[i]);
            my_putstr(" is a shell built-in\n");
            found = 1;
        }
        if (print_corresponding_paths(args[i], paths))
            found = 1;
    }
    free_array(paths);
    return 0;
}
