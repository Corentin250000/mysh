/*
** EPITECH PROJECT, 2024
** my_show_word_array.c
** File description:
** display the content of an array
*/

#include <stddef.h>
#include "my.h"
#include <stdio.h>

int my_show_word_array(char *const *tab)
{
    int i = 0;

    while (tab[i] != NULL) {
        my_putstr(tab[i]);
        my_putchar('\n');
        i++;
    }
    return 0;
}
