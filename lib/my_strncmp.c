/*
** EPITECH PROJECT, 2024
** my_strncmp.c
** File description:
** task07
*/

#include "my.h"

/**
* @brief Compare two strings until the end of src or until n characters
* @param s1 First string to compare
* @param s2 Second string to compare
* @param n Limit
* @return 0 if both strings are exactly the same, else the difference, at same
* index, between s1 and s2, like this: s1[index] - s2[index]
*/
int my_strncmp(char const *s1, char const *s2, int n)
{
    for (int i = 0; (s1[i] != '\0' || s2[i] != '\0') && i < n; i++) {
        if (s1[i] - s2[i] != 0)
            return s1[i] - s2[i];
    }
    return 0;
}
