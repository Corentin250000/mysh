/*
** EPITECH PROJECT, 2024
** my_strdup.f
** File description:
** function that copy a str in a located memory
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char const *str)
{
    int str_size = my_strlen(str);
    char *dest = malloc(sizeof(char) * (str_size + 1));
    int i = 0;

    if (!dest)
        return NULL;
    if (!str) {
        free(dest);
        return NULL;
    }
    while (str[i] != '\0') {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
