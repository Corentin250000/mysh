/*
** EPITECH PROJECT, 2025
** preparation_next_iteration.c
** File description:
** ...
*/

#include "../include/minishell2.h"

static void free_env(command_t *infos)
{
    if (infos->cpy_env != NULL) {
        for (int i = 0; infos->cpy_env[i] != NULL && i < infos->size_env; ++i)
            free(infos->cpy_env[i]);
        free(infos->cpy_env);
    }
}

/**
* @brief Free the content of the structure who need to be reallocated later.
* @param infos Main structure
*/
void free_content_structure(command_t *infos)
{
    if (infos == NULL)
        return;
    if (infos->command != NULL)
        my_free(infos->command);
    if (infos->complete_command != NULL)
        my_free(infos->complete_command);
    if (infos->options != NULL) {
        for (int i = 0; infos->options[i] != NULL; ++i)
            my_free(infos->options[i]);
        my_free(infos->options);
    }
    if (infos->execution_list != NULL) {
        for (int i = 0; infos->execution_list[i] != NULL; ++i)
            free(infos->execution_list[i]);
        free(infos->execution_list);
    }
}

/**
* @brief Free all content of the structure in case of error in the program.
* @param infos Main structure
* @param return_value
* @return The return value given in parameter.
*/
int error_free_structure(command_t *infos, int return_value)
{
    if (infos->command != NULL)
        free(infos->command);
    if (infos->complete_command != NULL)
        free(infos->complete_command);
    if (infos->options != NULL) {
        for (int i = 0; infos->options[i] != NULL; ++i)
            free(infos->options[i]);
        free(infos->options);
    }
    if (infos->execution_list != NULL) {
        for (int i = 0; infos->execution_list[i] != NULL; ++i)
            free(infos->execution_list[i]);
        free(infos->execution_list);
    }
    if (infos->oldpwd != NULL)
        free(infos->oldpwd);
    free_env(infos);
    if (infos != NULL)
        free(infos);
    return return_value;
}

/**
* @brief Free not free'd content of the structure before quit the program.
* @param infos Main structure
* @param return_value
* @return The return value given in parameter.
*/
int final_free_structure(command_t *infos, int return_value)
{
    if (infos->oldpwd != NULL)
        free(infos->oldpwd);
    free_env(infos);
    if (infos != NULL)
        free(infos);
    return return_value;
}

static int copy_env_verification(int size_env, char **env, command_t *infos)
{
    for (int i = 0; i < size_env; ++i) {
        infos->cpy_env[i] = my_strdup(env[i]);
        if (!infos->cpy_env[i]) {
            my_free(infos);
            return 84;
        }
    }
    infos->size_env = size_env;
    infos->cpy_env[size_env] = NULL;
    return 0;
}

static void set_value(command_t *infos)
{
    if (!infos)
        return;
    infos->builtin = 0;
    infos->command = NULL;
    infos->execution_list = NULL;
    infos->nb_elem_exec = 0;
    infos->complete_command = NULL;
    infos->cpy_env = NULL;
    infos->oldpwd = NULL;
    infos->options = NULL;
    infos->size_env = 0;
}

/**
* @brief Init main structure of program and copy the environment into it.
* @param env Current environment, given to program at the beginning
* @param ac Number of arguments when user called the program
* @return The structure or NULL in case of errors.
*/
command_t *copy_env(char **env, int ac)
{
    int size_env = 0;
    int verification = 0;
    command_t *infos;

    if (ac != 1)
        return NULL;
    infos = malloc(sizeof(command_t));
    if (!infos)
        return NULL;
    set_value(infos);
    for (; env[size_env] != NULL; ++size_env);
    infos->cpy_env = malloc(sizeof(char *) * (size_env + 1));
    if (!infos->cpy_env) {
        my_free(infos);
        return NULL;
    }
    verification = copy_env_verification(size_env, env, infos);
    if (verification == 84)
        return NULL;
    return infos;
}
