/*
** EPITECH PROJECT, 2024
** my_strlen.c
** File description:
** task03
*/

#include "my.h"

/**
* @brief Determinate the size of the string
* @param str The string
* @return The size of the string
*/
int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return i;
}
