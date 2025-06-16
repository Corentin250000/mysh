/*
** EPITECH PROJECT, 2025
** search_variable.c
** File description:
** ...
*/

#include "../../include/my.h"

/**
 * @brief Build the varname to search it into environment variables (add a '='
 * to varname)
 * @param varname Name of variable
 * @return The new varname with the '=', or NULL in case of error
 */
char *build_varname(char const *varname)
{
    int size = 0;
    char *varname_with_equal;

    if (!varname)
        return NULL;
    size = my_strlen(varname);
    varname_with_equal = malloc(sizeof(char) * (size + 2));
    if (!varname_with_equal)
        return NULL;
    varname_with_equal = my_strcpy(varname_with_equal, varname);
    varname_with_equal = my_strcat(varname_with_equal, "=");
    return varname_with_equal;
}

/**
 * @brief Search a certain variable in list of variable
 * @param array Array of string who contain all variables in this format:
 * name=content
 * @param varname The name of variable to search
 * @return The array's index of the variable, or -1 if the variable isn't
 * present
 */
int search_var_array(char **array, char const *varname)
{
    char *var_with_equal = build_varname(varname);
    int index = 0;
    int size_var = 0;

    if (!var_with_equal)
        return -1;
    if (!array) {
        free(var_with_equal);
        return -1;
    }
    size_var = my_strlen(var_with_equal);
    for (; array[index] != NULL; index++) {
        if (!my_strncmp(array[index], var_with_equal, size_var)) {
            free(var_with_equal);
            return index;
        }
    }
    free(var_with_equal);
    return -1;
}

/**
 * @brief Search a variable in list of local variables and in environment
 * variables
 * @param varname Variable to search
 * @param env Array of strings who contain all environment variables
 * @param arr Array of structures who contain all local variables
 * @return The content of variable or NULL if the variable doesn't exist or in
 * case of errors
 */
char *search_variable(char const *varname, char **env, local_var_t *arr)
{
    int index = search_var_array(arr->variables, varname);
    char *content = NULL;

    if (index != -1) {
        content = my_strdup(&arr->variables[index][my_strlen(varname) + 1]);
        return content ? content : NULL;
    }
    index = search_var_array(env, varname);
    if (index == -1) {
        write(2, varname, my_strlen(varname));
        write(2, ": Undefined variable.\n", 22);
        return NULL;
    }
    content = my_strdup(&env[index][my_strlen(varname) + 1]);
    return content ? content : NULL;
}
