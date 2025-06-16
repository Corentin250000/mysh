/*
** EPITECH PROJECT, 2025
** exclamation.c
** File description:
** function add the history command
*/

#include "../../include/my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int my_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

char *resolve_exclamation_by_number(int number)
{
    history_t *history = init_history();
    int *count = get_history_count();

    for (int i = 0; i < *count; i++) {
        if (history[i].number == number)
            return strdup(history[i].command);
    }
    return NULL;
}

char *resolve_exclamation_by_prefix(char *prefix, char *input)
{
    history_t *history = init_history();
    int *count = get_history_count();

    for (int i = *count - 1; i >= 0; i--) {
        if (my_strncmp(history[i].command, prefix, my_strlen(prefix)) == 0)
            return strdup(history[i].command);
    }
    return NULL;
}

char *resolve_exclamation_command(char *input)
{
    history_t *history = init_history();
    int *count = get_history_count();

    if (input[0] != '!')
        return input;
    if (input[1] == '!' && input[2] == '\0') {
        if (*count > 0)
            return strdup(history[*count - 1].command);
        return NULL;
    }
    if (my_isdigit(input[1]))
        return resolve_exclamation_by_number(atoi(&input[1]));
    return resolve_exclamation_by_prefix(&input[1], input);
}
