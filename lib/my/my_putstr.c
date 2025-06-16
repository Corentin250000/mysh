/*
** EPITECH PROJECT, 2024
** my_putstr.c
** File description:
** print a character or an str
*/

#include "my.h"

int error_my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        error_my_putchar(str[i]);
        i++;
    }
    return 0;
}

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return 0;
}
