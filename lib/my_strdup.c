/*
** EPITECH PROJECT, 2024
** my_strdup.c
** File description:
** task01
*/

#include "my.h"

/**
* @brief Duplicate the string
* @param src Source string
* @return The new string, or NULL if malloc has failed
* @note A \0 is automatically added at the end of string
*/
char *my_strdup(char const *src)
{
    int i = 0;
    int size = my_strlen(src);
    char *str = malloc(sizeof(char) * (size + 1));

    if (!str)
        return NULL;
    for (; src[i] != '\0'; i++)
        str[i] = src[i];
    str[i] = '\0';
    return str;
}
