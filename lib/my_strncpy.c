/*
** EPITECH PROJECT, 2024
** my_strncpy.c
** File description:
** task02
*/

#include "my.h"

/**
* @brief Copy the second string on the first until the end of src or
* until n characters
* @param dest Destination string
* @param src Source string, to copy on dest
* @param n Limit
* @return The destination string who contain src
* @note A \0 is automatically added at the end of string
* @warning The destination string must be correctly allocated with the size of
* src string
*/
char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    for (; src[i] != '\0' && i < n; i++)
        dest[i] = src[i];
    if (n > i)
        dest[i] = '\0';
    return dest;
}
