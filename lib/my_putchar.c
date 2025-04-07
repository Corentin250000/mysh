/*
** EPITECH PROJECT, 2024
** my_putchar.c
** File description:
** ...
*/

#include "my.h"

/**
* @brief Print a character
* @param c Character to print
* @return Number of printed characters (1)
*/
int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}
