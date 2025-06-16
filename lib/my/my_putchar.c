/*
** EPITECH PROJECT, 2024
** my_putchar.c
** File description:
** function that print a character
*/

#include <unistd.h>

void error_my_putchar(char c)
{
    write(2, &c, 1);
}

void my_putchar(char c)
{
    write(1, &c, 1);
}
