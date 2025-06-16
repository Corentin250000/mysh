/*
** EPITECH PROJECT, 2024
** my_strcat.c
** File description:
** concatenate two strings
*/

#include "my.h"
#include <stdlib.h>

char *my_strcat(char *dest, char const *src)
{
    int size_src = my_strlen(src);
    int size_dest = my_strlen(dest);
    int i = 0;

    while (i != size_src) {
        dest[size_dest + i] = src[i];
        i++;
    }
    dest[size_dest + i] = '\0';
    return dest;
}

char *custom_my_strcat(char *dest, char const *src)
{
    int start = my_strlen(src);
    int end = my_strlen(dest);
    int character = 0;
    int i = 0;
    char *line = malloc(sizeof(char) * (start + end) + 1);

    while (character != end) {
        line[character] = dest[character];
        character++;
    }
    while (i != start) {
        line[character] = src[i];
        character++;
        i++;
    }
    line[character] = '\0';
    return line;
}
