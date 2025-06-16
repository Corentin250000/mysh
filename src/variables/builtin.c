/*
** EPITECH PROJECT, 2025
** builtin.c
** File description:
** ...
*/

#include "../../include/my.h"

static int error_msg_set(char const *varname)
{
    write(2, "set: $", 6);
    write(2, varname, my_strlen(varname));
    write(2, " is read-only.\n", 15);
    return 1;
}

static int update_variable(local_var_t *arr, var_t var, char **args, int index)
{
    int size = my_strlen(var.varname) + my_strlen(var.var) + 1;
    char *new_variable = malloc(sizeof(char) * (size + 1));

    if (!new_variable)
        return 1;
    new_variable = my_strcpy(new_variable, var.varname);
    new_variable = my_strcat(new_variable, "=");
    if (var.var)
        new_variable = my_strcat(new_variable, var.var);
    arr->rights[index] = get_read_only(args);
    free(arr->variables[index]);
    arr->variables[index] = new_variable;
    return 0;
}

static int print_local_variables(local_var_t *arr)
{
    if (!arr)
        return 1;
    if (!arr->variables)
        return 1;
    for (int i = 0; arr->variables[i] != NULL; i++)
        mini_printf("%s\n", arr->variables[i]);
    return 0;
}

/**
 * @brief Add or update a local variable
 * @param arr Structure array who contain all variables
 * @param args All arguments of command
 * @return 1 in case of errors, 0 else
 * @note If there is no content, the variable is deleted
 * (more precisely, the variable is now empty).
 */
int builtin_set(local_var_t *arr, char **args, char **env)
{
    char *varname = get_variable(args, 0);
    char *var = get_variable(args, 1);
    int index = 0;
    var_t variable;

    (void)env;
    if (size_array(args) == 1)
        return print_local_variables(arr);
    index = search_var_array(arr->variables, varname);
    if (index == -1)
        return add_local_var(arr, args);
    if (arr->rights[index] == 1)
        return error_msg_set(varname);
    variable.varname = varname;
    variable.var = var;
    return update_variable(arr, variable, args, index);
}

static int verification_index_var(int index, char const *varname,
    local_var_t *arr)
{
    if (index == -1)
        return 1;
    if (arr->rights[index]) {
        write(2, "unset: $", 8);
        write(2, varname, my_strlen(varname));
        write(2, " is read-only.\n", 15);
        return 1;
    }
    return 0;
}

static char *get_varname_unset(char **args)
{
    char *result = NULL;

    if (size_array(args) < 2)
        return NULL;
    result = my_strdup(args[1]);
    return result;
}

static int copy_variables(local_var_t *arr, char **new_var, int *new_rights,
    int index)
{
    int nb_var = count_local_var(arr);
    int index_new = 0;

    for (int i = 0; i < nb_var; i++) {
        if (i == index)
            continue;
        new_var[index_new] = my_strdup(arr->variables[i]);
        if (!new_var[index_new])
            return 1;
        new_rights[index_new] = arr->rights[i];
        index_new++;
    }
    for (int i = 0; i < nb_var; i++)
        free(arr->variables[i]);
    free(arr->rights);
    free(arr->variables);
    arr->variables = new_var;
    arr->rights = new_rights;
    return 0;
}

/**
 * @brief Delete a local variable
 * @param arr Structure array who contain all variables
 * @param args All arguments of command
 * @return 1 in case of errors, 0 else
 */
int builtin_unset(local_var_t *arr, char **args, char **env)
{
    char *varname = get_varname_unset(args);
    int index = search_var_array(arr->variables, varname);
    int nb_var = count_local_var(arr);
    char **new_variables = NULL;
    int *new_rights = NULL;

    (void)env;
    if (verification_index_var(index, varname, arr))
        return 1;
    new_variables = malloc(sizeof(char *) * nb_var);
    if (!new_variables)
        return 1;
    new_rights = malloc(sizeof(int) * nb_var);
    if (!new_rights) {
        free(new_variables);
        return 1;
    }
    return copy_variables(arr, new_variables, new_rights, index);
}
