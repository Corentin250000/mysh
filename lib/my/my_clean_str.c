/*
** EPITECH PROJECT, 2025
** clean_str.c
** File description:
** functions clean_str : remove all spaces
** clean_str_keep_space : keep space beetwen 2 words
*/

#include "my.h"
#include <stdio.h>

void clean_str(char *str)
{
    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

void add_a_space(char *str, int *i, int *j)
{
    int space_added = 0;

    if (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n') {
        if (str[*i] == ' ' && space_added == 0) {
            str[*j] = ' ';
            space_added = 1;
            (*j)++;
        }
    }
}

int handle_space_and_char(char current, int *space_added)
{
    if (current == ' ' || current == '\t' || current == '\n') {
        if (*space_added == 0) {
            *space_added = 1;
            return ' ';
        }
        return 0;
    }
    *space_added = 0;
    return current;
}

void clean_str_keep_space(char *str)
{
    int i = 0;
    int j = 0;
    int space_added = 0;
    char processed_char;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    while (str[i] != '\0') {
        processed_char = handle_space_and_char(str[i], &space_added);
        if (processed_char) {
            str[j] = processed_char;
            j++;
        }
        i++;
    }
    if (j > 0 && str[j - 1] == ' ')
        j--;
    str[j] = '\0';
}
