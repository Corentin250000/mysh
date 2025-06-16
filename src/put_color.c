/*
** EPITECH PROJECT, 2025
** put_color.c
** File description:
** add colors to text
*/

#include <stdio.h>
#include "../include/my.h"

/**
 * @note printf("\033[1m"); to put in bold
 */
void put_cyan(void)
{
    printf("\033[1m");
    printf("\033[36m");
    fflush(stdout);
}

void put_yellow(void)
{
    printf("\033[1;33m");
    fflush(stdout);
}

void reset_color(void)
{
    printf("\033[0m");
    fflush(stdout);
}
