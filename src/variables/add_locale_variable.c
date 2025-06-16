/*
** EPITECH PROJECT, 2025
** add_locale_variable.c
** File description:
** Add/update locale variables
*/

#include "../../include/my.h"

local_var_t *init_local_var_array(char **env)
{
    local_var_t *arr = malloc(sizeof(local_var_t));

    if (!arr)
        return NULL;
    arr->variables = NULL;
    arr->rights = NULL;
    return arr;
}

int count_local_var(local_var_t *arr)
{
    int i = 0;

    if (!arr)
        return 0;
    if (!arr->variables)
        return 0;
    for (; arr->variables[i] != NULL; i++);
    return i;
}

static char *verify_variable_not_null(char **variable, int is_varname)
{
    if (!variable[is_varname])
        return NULL;
    return my_strdup(variable[is_varname]);
}

static int verification_args(char **args)
{
    int size = size_array(args);

    if (size == 1)
        return 0;
    if (size == 2 && args[1][0] == '=')
        return 0;
    if (size == 3 && args[2][0] == '=')
        return 0;
    return 1;
}

/**
 * @note To get varname: put 0 on second parameter
 *
 * To get variable content: put 1 on second parameter
 */
char *get_variable(char **args, int is_varname)
{
    char **variable = NULL;
    char *result = NULL;

    if (!verification_args(args))
        return NULL;
    if (!my_strcmp(args[1], "-r")) {
        variable = my_str_to_word_array(args[2], "=");
        if (!variable)
            return NULL;
        result = verify_variable_not_null(variable, is_varname);
    } else {
        variable = my_str_to_word_array(args[1], "=");
        if (!variable)
            return NULL;
        result = verify_variable_not_null(variable, is_varname);
    }
    for (int i = 0; variable[i] != NULL; i++)
        free(variable[i]);
    free(variable);
    return result;
}

static int fill_new_variable(local_var_t *arr, char **args, int nb_var)
{
    char *name = get_variable(args, 0);
    char *var = get_variable(args, 1);

    arr->variables[nb_var] = my_strcpy(arr->variables[nb_var], name);
    free(name);
    arr->variables[nb_var] = my_strcat(arr->variables[nb_var], "=");
    if (var) {
        arr->variables[nb_var] = my_strcat(arr->variables[nb_var],
            var);
        free(var);
    }
    arr->variables[nb_var + 1] = NULL;
    return 0;
}

static int allocate_new_variable(local_var_t *arr, char **args, int nb_var)
{
    char *name = get_variable(args, 0);
    char *var = get_variable(args, 1);

    if (!name) {
        write(2, "set: Variable name must begin with a letter.\n", 45);
        if (var)
            free(var);
        return 1;
    }
    arr->variables[nb_var] = malloc(sizeof(char) * (my_strlen(name) +
        my_strlen(var) + 2));
    if (name)
        free(name);
    if (var)
        free(var);
    if (!arr->variables[nb_var]) {
        perror(strerror(errno));
        return 1;
    }
    return fill_new_variable(arr, args, nb_var);
}

/**
 * @brief Add a new local variable
 * @param arr Structure array who contain all variables
 * @param args All arguments of command
 * @warning In case of allocation error, the function write an error on error
 * output and quit. So, if the reallocation fail, the new variable isn't added.
 */
int add_local_var(local_var_t *arr, char **args)
{
    int nb_var = count_local_var(arr);
    int err = 0;

    arr->variables = my_realloc(arr->variables, sizeof(char *) * (nb_var + 2),
        sizeof(char *) * (nb_var + 1), &err);
    arr->rights = my_realloc(arr->rights, sizeof(int) * (nb_var + 2),
        sizeof(int) * (nb_var + 1), &err);
    if (err) {
        perror(strerror(errno));
        return 1;
    }
    arr->rights[nb_var] = get_read_only(args);
    return allocate_new_variable(arr, args, nb_var);
}

void free_local_var(local_var_t *arr)
{
    if (!arr)
        return;
    if (arr->variables) {
        for (int i = 0; arr->variables[i] != NULL; i++)
            free(arr->variables[i]);
        free(arr->variables);
    }
    if (arr->rights)
        free(arr->rights);
    free(arr);
}
