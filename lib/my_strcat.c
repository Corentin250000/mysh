/*
** EPITECH PROJECT, 2024
** my_strcat.c
** File description:
** task02
*/

#include "my.h"

/**
* @brief Concatenate the second string on the first
* @param dest Destination string
* @param src Source string, to concatenate on dest
* @return The destination string who contain dest + src
* @note A \0 is automatically added at the end of string
* @warning The destination string must be correctly allocated with the size of
* both strings
*/
char *my_strcat(char *dest, char const *src)
{
    int size_dest = my_strlen(dest);
    int size_src = my_strlen(src);
    int j = 0;

    for (; j < size_src; j++)
        dest[size_dest + j] = src[j];
    dest[size_dest + j] = '\0';
    return dest;
}
