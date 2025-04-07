/*
** EPITECH PROJECT, 2025
** my_free.c
** File description:
** ...
*/

#include "../include/minishell2.h"

/**
* @brief Free the paramter and set in to NULL
* @param to_free variable to free
*/
void my_free(void *to_free)
{
    if (!to_free)
        return;
    free(to_free);
    to_free = NULL;
}
