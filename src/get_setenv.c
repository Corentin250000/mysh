/*
** EPITECH PROJECT, 2025
** get_setenv.c
** File description:
** function to recreate setenv command
*/

#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"

int handle_setenv_errors(char *str)
{
    int i = 0;

    if (!(str[0] >= 'a' && str[0] <= 'z') &&
        !(str[0] >= 'A' && str[0] <= 'Z')) {
        error_my_putstr("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    while (str[i] != '\0') {
        if (!(str[i] >= 'a' && str[i] <= 'z')
            && !(str[i] >= 'A' && str[i] <= 'Z') &&
            !(str[i] >= '0' && str[i] <= '9') && str[i] != '_') {
            error_my_putstr("setenv: Variable name must contain");
            error_my_putstr(" alphanumeric characters.\n");
            return 1;
        }
        i++;
    }
    return 0;
}

int get_setenv(char *command, char **env, char *value)
{
    int size = my_strlen(command) + my_strlen(value) + 2;
    char *new_env_line = malloc(sizeof(char) * size);
    int i = 0;

    if (new_env_line == NULL || command == NULL)
        return 84;
    if (handle_setenv_errors(command) == 1)
        return 1;
    my_strcpy(new_env_line, command);
    my_strcat(new_env_line, "=");
    my_strcat(new_env_line, value);
    for (; env[i] != NULL; i++) {
        if (my_strcmp(env[i], command) == 0) {
            env[i] = new_env_line;
            return 0;
        }
    }
    env[i] = new_env_line;
    env[i + 1] = NULL;
    return 0;
}
