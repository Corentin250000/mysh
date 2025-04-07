/*
** EPITECH PROJECT, 2025
** error_handling_builtin.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Change actual pwd and oldpwd.
* new_oldpwd is automatically freed.
* Also free unused home variable defined in my_cd function.
* @param infos Main structure
* @param new_oldpwd New previous location (oldpwd)
* @param home Path to home to free
* @return 84 in case of errors, else 0
*/
int change_oldpwd(command_t *infos, char *new_oldpwd, char *home)
{
    int verification = 0;
    char *new_pwd = NULL;

    if (infos->oldpwd)
        my_free(infos->oldpwd);
    infos->oldpwd = my_strdup(new_oldpwd);
    my_free(new_oldpwd);
    my_free(home);
    new_pwd = getcwd(new_pwd, PATH_MAX);
    if (!new_pwd)
        return 84;
    verification = update_env(infos, "PWD", new_pwd);
    free(new_pwd);
    if (verification == 84)
        return 84;
    return !infos->oldpwd ? 84 : 0;
}

/**
* @brief Make verification on the directory (if he exist or not)
* @param path Path to directory to verify it
* @param actual String to free
* @param home String to free
* @return 0
*/
int print_error_msg_cd(char const *path, char *actual, char *home)
{
    free(actual);
    free(home);
    if (!access(path, F_OK)) {
        write(2, path, (size_t) my_strlen(path));
        write(2, ": Permission denied.\n", 21);
    } else {
        write(2, path, (size_t) my_strlen(path));
        write(2, ": No such file or directory.\n", 29);
    }
    return 0;
}

/**
* @brief Determinate if the "directory" for the command cd is really a
* directory
* @param infos Main structure
* @return 84 if lstat has failed, 0 else.
* @note If lstat has failed, the function print the errno value.
*
* @note If the directory is not a real directory, the function print on error
* output an error message, like TCSH.
*/
int is_a_directory(command_t *infos, char *actual, char *home)
{
    struct stat s;

    if (access(infos->options[1], F_OK) == -1) {
        write(2, infos->options[1], (size_t) my_strlen(infos->options[1]));
        write(2, ": No such file or directory.\n", 29);
        free(actual);
        free(home);
        return 84;
    } else if (lstat(infos->options[1], &s) == -1) {
        free(actual);
        free(home);
        return 84;
    }
    if (S_ISDIR(s.st_mode))
        return 0;
    write(2, infos->options[1], (size_t) my_strlen(infos->options[1]));
    write(2, ": Not a directory.\n", 19);
    free(actual);
    free(home);
    return 84;
}

/**
* @brief Make last verifications for the command cd
* @param infos Main structure
* @param actual String to free
* @param home String to free
* @return 0 even in case of error
*/
int end_cd_function(command_t *infos, char *actual, char *home)
{
    int verification = 0;

    if (is_a_directory(infos, actual, home) == 84)
        return 0;
    verification = chdir(infos->options[1]);
    if (verification == -1)
        return print_error_msg_cd(infos->options[1], actual, home);
    return change_oldpwd(infos, actual, home);
}
