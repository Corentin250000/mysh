/*
** EPITECH PROJECT, 2025
** get_read_only.c
** File description:
** ...
*/

#include "../../include/my.h"

int get_read_only(char **args)
{
    int size_args = size_array(args);

    if (size_args < 2)
        return 0;
    if (!my_strcmp(args[1], "-r"))
        return 1;
    return 0;
}
