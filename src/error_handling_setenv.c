/*
** EPITECH PROJECT, 2025
** error_handling_setenv.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Determinate if the character is a number
* @param c the character to analyse
* @return 1 if it's a number, 0 else
*/
int is_a_number(char c)
{
    return (c >= '0' && c <= '9');
}

/**
* @brief Determinate if the string is composed by alphanumeric characters
* @param str String to analyse
* @return 1 if the string is correct, 0 else
* @note Here, the underscore '_' is accepted as alphanum character
*/
int str_is_alphanum(char const *str)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z')
            && (str[i] < 'A' || str[i] > 'Z') && str[i] != '_')
                return 0;
    }
    return 1;
}

/**
* @brief Verify the name of variable
* @param var Name variable to verify
* @return 84 in case of errors, 0 else
*/
int verify_name_variable(char const *var)
{
    if (is_a_number(var[0])) {
        write(2, "setenv: Variable name must begin with a letter.\n", 49);
        return 84;
    }
    if (!str_is_alphanum(var)) {
        write(2, "setenv: Variable name must contain alphanumeric"
            " characters.\n", 61);
        return 84;
    }
    return 0;
}
