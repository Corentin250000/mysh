/*
** EPITECH PROJECT, 2024
** my_strncat.c
** File description:
** task03
*/

#include "my.h"

/**
* @brief Concatenate the second string on the first until the end of src or
* until nb characters
* @param dest Destination string
* @param src Source string, to concatenate on dest
* @param nb Limit
* @return The destination string who contain dest + src
* @note A \0 is automatically added at the end of string
* @warning The destination string must be correctly allocated with the size of
* both strings
*/
char *my_strncat(char *dest, char const *src, int nb)
{
    int size_dest = my_strlen(dest);
    int size_src = my_strlen(src);

    for (int j = 0; j < size_src && j < nb; j++)
        dest[size_dest + j] = src[j];
    return dest;
}
