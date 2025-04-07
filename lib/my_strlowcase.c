/*
** EPITECH PROJECT, 2024
** my_strlowcase.c
** File description:
** task09
*/

#include "my.h"

/**
* @brief Put all upper letter to lower letter
* @param str The string to change
* @return The string changed
*/
char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] += (str[i] >= 'A' && str[i] <= 'Z') ? 32 : 0;
    return str;
}
