/*
** EPITECH PROJECT, 2025
** which.c
** File description:
** function to recreate the shell which
*/

#include "../include/my.h"

void check_which_path(char **paths, char **args, int *i)
{
    char *full_path = NULL;

    for (int j = 0; paths[j] != NULL; j++) {
        full_path = create_full_path(paths[j], args[*i]);
        if (!full_path)
            continue;
        if (access(full_path, X_OK) == 0) {
            my_putstr(full_path);
            my_putchar('\n');
            free(full_path);
            break;
        }
        free(full_path);
    }
}

int create_which(local_var_t *arr, char **args, char **env)
{
    char **paths = get_env_paths(env);
    char *full_path = NULL;

    (void)arr;
    if (!paths)
        return 1;
    for (int i = 1; args[i] != NULL; i++) {
        if (is_builtin(args[i])) {
            my_putstr(args[i]);
            my_putstr(": shell built-in command.\n");
            continue;
        }
        check_which_path(paths, args, &i);
    }
    free_array(paths);
    return 0;
}
