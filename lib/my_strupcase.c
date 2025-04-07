/*
** EPITECH PROJECT, 2024
** my_strupcase.c
** File description:
** task08
*/

#include "my.h"

/**
* @brief Put all lower letter to upper letter
* @param str The string to change
* @return The string changed
*/
char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] -= (str[i] >= 'a' && str[i] <= 'z') ? 32 : 0;
    return str;
}
