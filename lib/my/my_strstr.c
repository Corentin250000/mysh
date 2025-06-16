/*
** EPITECH PROJECT, 2024
** my_strstr.c
** File description:
** search for a string occurence in another str
*/

#include <stddef.h>
#include "my.h"

/**
* @brief Search a sub-string in another string
* @param str String where the function is looking for the sub-string
* @param to_find String to find in str
* @return A pointer to the sub-string, or NULL if she doesn't exist
* @warning No need to free the pointer, he will be when the main string is
* free'd (str)
*/
char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int size = my_strlen(to_find);

    if (!size)
        return str;
    for (; str[i] != '\0'; i++) {
        if (!my_strncmp(&str[i], to_find, size))
            return &str[i];
    }
    return NULL;
}
