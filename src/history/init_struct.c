/*
** EPITECH PROJECT, 2025
** init_struct.c
** File description:
** function to init the struct
*/

#include "../../include/my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

history_t *init_history(void)
{
    static history_t *history = NULL;

    if (!history) {
        history = malloc(sizeof(history_t) * 100);
        if (history == NULL)
            return NULL;
        for (int i = 0; i < 100; i++) {
            history[i].command = NULL;
            history[i].timestamp = 0;
            history[i].number = 0;
        }
    }
    return history;
}

int *get_history_count(void)
{
    static int count = 0;

    return &count;
}

int *get_history_next_id(void)
{
    static int id = 1;

    return &id;
}
