/*
** EPITECH PROJECT, 2024
** my_strcpy.c
** File description:
** task01
*/

#include "my.h"

/**
* @brief Copy the second string on the first
* @param dest Destination string
* @param src Source string, to copy on dest
* @return The destination string who contain src
* @note A \0 is automatically added at the end of string
* @warning The destination string must be correctly allocated with the size of
* src string
*/
char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
