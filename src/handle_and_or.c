/*
** EPITECH PROJECT, 2025
** display_prompt.c
** File description:
** display the prompt
*/

#include "../include/my.h"

int count_nb_searator(char *line, char separator)
{
    int count = 1;

    for (int i = 0; line[i]; i++) {
        if (line[i] == separator && line[i + 1] == separator) {
            count++;
            i++;
        }
    }
    return count;
}

char **split_and_or(char *line, char separator)
{
    char **result = NULL;
    int pos = 0;
    char *start = line;
    int count = count_nb_searator(line, separator);

    result = malloc(sizeof(char *) * (count + 1));
    for (int i = 0; line[i]; i++) {
        if (line[i] == separator && line[i + 1] == separator) {
            line[i] = '\0';
            result[pos] = my_strdup(start);
            pos++;
            i++;
            start = &line[i + 1];
        }
    }
    result[pos] = my_strdup(start);
    pos++;
    result[pos] = NULL;
    return result;
}

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

static void print_null_command_error(void)
{
    write(2, "Invalid null command.\n", 23);
}

int handle_and_commands(local_var_t *arr, char **and_cmds, char **env)
{
    int status = 0;

    for (int i = 0; and_cmds[i] != NULL; i++) {
        clean_str_keep_space(and_cmds[i]);
        if (and_cmds[i][0] == '\0') {
            print_null_command_error();
            return 1;
        }
        if (process_piped_input(arr, and_cmds[i], env) == 0)
            continue;
        status = parser(arr, and_cmds[i], env);
        if (status != 0)
            break;
    }
    return status;
}

int handle_or_commands(local_var_t *arr, char **or_cmds, char **env)
{
    int status = 0;
    char **and_cmds = NULL;

    for (int j = 0; or_cmds[j] != NULL; j++) {
        if (or_cmds[j][0] == '\0') {
            print_null_command_error();
            return 1;
        }
        and_cmds = split_and_or(or_cmds[j], '&');
        status = handle_and_commands(arr, and_cmds, env);
        free_array(and_cmds);
        if (status == 0)
            break;
    }
    return status;
}
