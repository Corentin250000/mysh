/*
** EPITECH PROJECT, 2024
** B-PSU-200-MLH-2-1-42sh-anastasija.potapova
** File description:
** clean_str.c
*/

#include <stdlib.h>

int is_alpha(char *str, int i)
{
    if (str[i] >= 'a' && str[i] <= 'z')
        return 1;
    if (str[i] >= 'A' && str[i] <= 'Z')
        return 1;
    if (str[i] >= '0' && str[i] <= '9')
        return 1;
    if (str[i] == '-' || str[i] == '.' || str[i] == '/' || str[i] == '=' ||
        str[i] == '_' || str[i] == '~' || str[i] == ';' || str[i] == '|' ||
        str[i] == '>' || str[i] == '.')
        return 1;
    return 0;
}

int size_alloc(char *str)
{
    int i = 0;
    int size = 0;

    while (str[i] != '\0') {
        if (is_alpha(str, i) == 1 || is_alpha(str, i) == 1 &&
        is_alpha(str, i + 1) == 0 || is_alpha(str, i) == 0 &&
        is_alpha(str, i + 1) == 1)
            size++;
        i++;
    }
    return size;
}

int skip_char(char *str, int i)
{
    while (str[i] != '\0' && is_alpha(str, i) == 0) {
        i++;
    }
    return i;
}

char *str_clean(char *str)
{
    int i = skip_char(str, 0);
    int size = size_alloc(str) + 1;
    char *clean = malloc(sizeof(char) * size);
    int y = 0;

    while (str[i] != '\0') {
        if (is_alpha(str, i) == 1 || is_alpha(str, i) == 1 &&
        is_alpha(str, i + 1) == 0 || is_alpha(str, i) == 0 &&
        is_alpha(str, i + 1) == 1) {
            clean[y] = str[i];
            y++;
        }
        i++;
    }
    clean[y] = '\0';
    return clean;
}
