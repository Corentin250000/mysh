/*
** EPITECH PROJECT, 2025
** update_env.c
** File description:
** ...
*/

#include "../include/minishell2.h"

static void fill_var(command_t *infos, char const *var, char const *new, int i)
{
    infos->cpy_env[i] = my_strcpy(infos->cpy_env[i], var);
    infos->cpy_env[i] = my_strcat(infos->cpy_env[i], "=");
    if (new != NULL)
        infos->cpy_env[i] = my_strcat(infos->cpy_env[i], new);
}

/**
* @brief Determinate the size of a string array
* until the loop reach the end or a NULL character
* @param array String array
* @return size of the string array
*/
int size_array(char **array)
{
    int i = 0;

    for (; array[i] != NULL; ++i);
    return i;
}

static int add_variable(command_t *infos, char const *var, char const *new)
{
    int error = 0;

    infos->cpy_env = my_realloc(infos->cpy_env, sizeof(char *) *
        (infos->size_env + 2), sizeof(char *) * (infos->size_env + 1), &error);
    if (error == 1)
        return 84;
    if (!new) {
        infos->cpy_env[infos->size_env] = malloc(sizeof(char) * (my_strlen(var)
            + 2));
    } else {
        infos->cpy_env[infos->size_env] = malloc(sizeof(char) * (my_strlen(var)
            + my_strlen(new) + 2));
    }
    if (!infos->cpy_env[infos->size_env])
        return 84;
    fill_var(infos, var, new, infos->size_env);
    infos->cpy_env[infos->size_env + 1] = NULL;
    infos->size_env++;
    return 0;
}

static int search_var(command_t *infos, char const *var, int *i)
{
    int found = 0;
    int temp = *i;
    char *var_with_equal = malloc(sizeof(char) * (my_strlen(var) + 2));

    if (!var_with_equal)
        return 0;
    var_with_equal = my_strcpy(var_with_equal, var);
    var_with_equal = my_strcat(var_with_equal, "=");
    for (; infos->cpy_env[temp] != NULL; ++temp) {
        if (!my_strncmp(infos->cpy_env[temp], var_with_equal,
            my_strlen(var_with_equal))) {
                found = 1;
                break;
        }
    }
    *i = temp;
    free(var_with_equal);
    return found;
}

/**
* @brief Add/update a environment variable
* @param infos Main struture
* @param var Variable to create/update
* @param new Content of the variable
* @return 0 if no error, 84 else
*/
int update_env(command_t *infos, char const *var, char const *new)
{
    int found = 0;
    int i = 0;

    if (verify_name_variable(var) == 84)
        return 0;
    found = search_var(infos, var, &i);
    if (found) {
        free(infos->cpy_env[i]);
        infos->cpy_env[i] = malloc(sizeof(char) * (my_strlen(var) +
            my_strlen(new) + 2));
        if (!infos->cpy_env[i])
            return 84;
        fill_var(infos, var, new, i);
        return 0;
    }
    return add_variable(infos, var, new);
}

static void free_str_array(char **array)
{
    if (array != NULL) {
        for (int i = 0; array[i] != NULL; ++i)
            free(array[i]);
        free(array);
    }
}

static char **remove_var_part_2(command_t *infos, char **cpy_env,
    char *var)
{
    int j = 0;
    char **new_env;

    new_env = malloc(sizeof(char *) * (infos->size_env + sizeof(NULL)));
    if (!new_env) {
        free_str_array(cpy_env);
        free(var);
        return NULL;
    }
    for (int i = 0; cpy_env[i] != NULL; ++i) {
        if (!my_strncmp(cpy_env[i], var, my_strlen(var)))
            continue;
        new_env[j] = my_strdup(cpy_env[i]);
        j++;
    }
    free_str_array(cpy_env);
    free(var);
    new_env[j] = NULL;
    return new_env;
}

/**
* @brief Remove a environment variable
* @param infos Main structure
* @param cpy_env Copy of all environment variables
* @param var Variable to remove
* @return If var is not found in cpy_env, then return cpy_env.
*
* Else, return the reallocated cpy_env.
*/
char **remove_variable(command_t *infos, char **cpy_env, char const *var)
{
    int found = 0;
    char *var_with_equal = malloc(sizeof(char) * (my_strlen(var) + 2));

    if (!var_with_equal)
        return cpy_env;
    var_with_equal = my_strcpy(var_with_equal, var);
    var_with_equal = my_strcat(var_with_equal, "=");
    for (int i = 0; cpy_env[i] != NULL; ++i) {
        if (!my_strncmp(cpy_env[i], var, my_strlen(var))) {
            found = 1;
            break;
        }
    }
    if (!found)
        return cpy_env;
    infos->size_env--;
    return remove_var_part_2(infos, cpy_env, var_with_equal);
}
