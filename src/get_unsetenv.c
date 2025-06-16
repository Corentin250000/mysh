/*
** EPITECH PROJECT, 2025
** get_unsetenv.c
** File description:
** function to recreate unsetenv command
*/

#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"

void get_unsetenv(char **env, char *command)
{
    char **actu_env = env;
    char **new_env = env;
    int i = 0;
    int j = 0;

    if (actu_env == NULL)
        return;
    while (actu_env[i] != NULL) {
        if (my_strcmp(actu_env[i], command) == 0) {
            i++;
        } else {
            new_env[j] = actu_env[i];
            j++;
            i++;
        }
    }
    new_env[j] = NULL;
}
