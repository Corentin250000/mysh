/*
** EPITECH PROJECT, 2025
** detect_call_variable.c
** File description:
** ...
*/

#include "../../include/my.h"

/**
 * @brief Detect if there is a call to a variable in arguments
 * @param args Arguments to analyse
 * @return Index of variable call or -1 if there is no variable call
 */
int detect_call_variable(char **args)
{
    if (!args)
        return -1;
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strstr(args[i], "$") != NULL)
            return i;
    }
    return -1;
}

/**
 * @brief Get the name of called variable
 * @param args All arguments
 * @return The name of variable or NULL if there is no variable
 * @note If the "variable" is empty (the argument is a '$'), the function
 * return NULL.
 */
char *get_name_var(char **args)
{
    int index = detect_call_variable(args);
    char *call_variable = NULL;

    if (index == -1)
        return NULL;
    if (my_strlen(args[index]) < 2)
        return NULL;
    call_variable = my_strstr(args[index], "$");
    if (!call_variable)
        return NULL;
    return my_strdup(&call_variable[1]);
}

/**
 * @brief Determinate the size of array
 * @param arr The array
 * @return The size of array or -1 if arr is NULL
 */
int size_array(char **arr)
{
    int i = 0;

    if (!arr)
        return -1;
    for (; arr[i] != NULL; i++);
    return i;
}

char **separate_variable(char *var)
{
    char **separated_variable;

    if (!var)
        return NULL;
    separated_variable = my_str_to_word_array(var, " \t\n");
    if (!separated_variable)
        return NULL;
    return separated_variable;
}
