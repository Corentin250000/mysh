/*
** EPITECH PROJECT, 2024
** my_strncat.c
** File description:
** concatenate two
** strings according to size
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int size_src = my_strlen(src);
    int size_dest = my_strlen(dest);
    int i = 0;

    while (src[i] != '\0' && i < nb) {
        dest[size_dest + i] = src[i];
        i++;
    }
    dest[size_dest + i] = '\0';
    return dest;
}
