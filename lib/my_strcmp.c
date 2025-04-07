/*
** EPITECH PROJECT, 2024
** my_strcmp.c
** File description:
** task06
*/

#include "my.h"

/**
* @brief Compare two strings
* @param s1 First string to compare
* @param s2 Second string to compare
* @return 0 if both strings are exactly the same, else the difference, at same
* index, between s1 and s2, like this: s1[index] - s2[index]
*/
int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    for (; s1[i] != '\0' || s2[i] != '\0'; i++) {
        if (s1[i] - s2[i] != 0)
            return s1[i] - s2[i];
    }
    return 0;
}
