/*
** EPITECH PROJECT, 2025
** get_cd.c
** File description:
** function to execute the cd command
*/

#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"

char *get_line_path(char **env, char *type)
{
    int i = 0;
    char *home_line = NULL;
    int size = my_strlen(type);

    if (env == NULL)
        return NULL;
    while (env[i] != NULL) {
            if (my_strncmp(env[i], type, size) == 0) {
                home_line = env[i];
            }
        i++;
    }
    return home_line;
}

char *remove_type(char **env, char *type)
{
    int i = 0;
    int len = my_strlen(type);

    if (!env)
        return NULL;
    while (env[i]) {
        if (my_strncmp(env[i], type, len) == 0)
            return env[i] + len;
        i++;
    }
    return NULL;
}

char *get_current_path(void)
{
    size_t n = 0;
    char *buf = NULL;

    return (getcwd(buf, n));
}

int get_cd(char *command, char **env)
{
    char **args = my_str_to_word_array(command, " ");
    char *dir = NULL;
    char *home = remove_type(env, "HOME=");
    char *actual_dir = get_current_path();
    char *pwd = remove_type(env, "PWD=");

    get_setenv("OLDPWD", env, actual_dir);
    if (args[1] == NULL)
        dir = home;
    else
        dir = args[1];
    if (chdir(dir) == -1) {
        error_my_putstr(dir);
        error_my_putstr(": No such file or directory.\n");
        return 1;
    }
    pwd = actual_dir;
    return 0;
}

int get_cd_minus(char **env)
{
    char *pwd = remove_type(env, "PWD=");
    char *oldpwd = remove_type(env, "OLDPWD=");

    get_setenv("OLDPWD", env, pwd);
    if (oldpwd == NULL)
        return 1;
    if (chdir(oldpwd) == -1) {
        free(oldpwd);
        return 1;
    }
    return 0;
}
