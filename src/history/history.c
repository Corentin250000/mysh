/*
** EPITECH PROJECT, 2025
** history.c
** File description:
** function add the history command
*/

#include "../../include/my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void add_to_history(const char *command)
{
    history_t *history = init_history();
    int *count = get_history_count();
    int *next_id = get_history_next_id();
    size_t len = 0;

    if (command == NULL || my_strlen(command) == 0)
        return;
    len = my_strlen(command);
    if (len > 0 && command[len - 1] == '\n')
        ((char *)command)[len - 1] = '\0';
    if (*count >= 100) {
        for (int i = 1; i < 100; i++)
            history[i - 1] = history[i];
        (*count)--;
    }
    history[*count].command = strdup(command);
    history[*count].timestamp = time(NULL);
    history[*count].number = *next_id;
    (*next_id)++;
    (*count)++;
}

char *format_time(time_t timestamp)
{
    static char time_str[6];
    struct tm *tm_info = localtime(&timestamp);

    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);
    return time_str;
}

int builtin_history(local_var_t *arr, char **command, char **env)
{
    history_t *history = init_history();
    int *count = get_history_count();

    (void)arr;
    for (int i = 0; i < *count; i++) {
        printf("%5d  %s  %s\n", history[i].number,
            format_time(history[i].timestamp), history[i].command);
    }
    return 0;
}

void save_history(void)
{
    char *home = getenv("HOME");
    char *path = malloc(sizeof(char) * 300);
    FILE *file = NULL;
    history_t *history = init_history();
    int *count = get_history_count();

    if (home == NULL)
        return;
    my_strcpy(path, home);
    my_strcat(path, "/.42sh_history");
    file = fopen(path, "w");
    if (file == NULL)
        return;
    for (int i = 0; i < *count; i++)
        fprintf(file, "%ld|%s\n", history[i].timestamp, history[i].command);
    fclose(file);
}

static void parse_history_line
(char *line, history_t *history, int *count, int *next_id)
{
    char *separator = strchr(line, '|');
    char *command;
    int len;

    if (separator == NULL)
        return;
    *separator = '\0';
    history[*count].timestamp = atoi(line);
    command = separator + 1;
    len = my_strlen(command);
    if (len > 0 && command[len - 1] == '\n')
        command[len - 1] = '\0';
    history[*count].command = my_strdup(command);
    history[*count].number = *next_id;
    (*next_id)++;
    (*count)++;
}

void load_history(void)
{
    char *home = getenv("HOME");
    char *path = malloc(sizeof(char) * 300);
    FILE *file = NULL;
    char *line = malloc(sizeof(char) * 500);
    history_t *history = init_history();
    int *count = get_history_count();
    int *next_id = get_history_next_id();

    if (home == NULL)
        return;
    my_strcpy(path, home);
    my_strcat(path, "/.42sh_history");
    file = fopen(path, "r");
    if (file == NULL)
        return;
    while (fgets(line, sizeof(line), file) && *count < 100)
        parse_history_line(line, history, count, next_id);
    fclose(file);
}
