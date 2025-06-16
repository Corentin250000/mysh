/*
** EPITECH PROJECT, 2025
** get_prompt.c
** File description:
** get a shell prompt
*/

#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"

int parsing_separators(local_var_t *arr, char *line, char **env)
{
    char **semi_colon_cmds = my_str_to_word_array(line, ";\n");
    int status = 0;
    char **or_cmds = NULL;

    for (int i = 0; semi_colon_cmds[i] != NULL; i++) {
        or_cmds = split_and_or(semi_colon_cmds[i], '|');
        status = handle_or_commands(arr, or_cmds, env);
        free_array(or_cmds);
        if (status != 0)
            break;
    }
    free_array(semi_colon_cmds);
    return status;
}

int mult_args(local_var_t *arr, char **env)
{
    char *command = NULL;
    size_t size = 0;
    char **args = NULL;
    int nbr_bytes = 0;
    int value = 0;

    nbr_bytes = getline(&command, &size, stdin);
    if (nbr_bytes <= 0)
        return -1;
    clean_str_keep_space(command);
    command = place_variable(arr, command, env);
    if (!command)
        return 1;
    if (parsing_separators(arr, command, env) == 1)
        return 1;
    args = my_str_to_word_array(command, ";\n");
    free(command);
    free(args);
    return value;
}

int if_in_tty(local_var_t *arr, char **env)
{
    int nbr_bytes = 0;
    int value = 0;

    while (nbr_bytes != -1) {
        get_special_var(arr, env);
        nbr_bytes = mult_args(arr, env);
        if (nbr_bytes == 1)
            value = 1;
    }
    return value;
}

static int verify_ctrl_d(char **command, int nbr_bytes)
{
    if (feof(stdin)) {
        clearerr(stdin);
        if (nbr_bytes == -1) {
            mini_printf("exit\n");
            exit(0);
        }
        *command = NULL;
        mini_printf("\n");
        return -1;
    }
    return 0;
}

static void process_command(char *command)
{
    char **args = NULL;

    args = my_str_to_word_array(command, ";\n");
    free(args);
}

void handle_input(local_var_t *arr, char *command, char **env)
{
    char *resolved = NULL;

    clean_str_keep_space(command);
    if (command && my_strlen(command) > 0) {
        resolved = apply_magic_quotes(arr, command, env);
        if (!resolved)
            return;
        resolved = resolve_exclamation_command(resolved);
        if (!resolved)
            return;
        add_to_history(resolved);
        resolved = place_variable(arr, resolved, env);
        if (!resolved)
            return;
        if (parsing_separators(arr, resolved, env) == 0) {
            return;
        }
        process_command(resolved);
    }
}

int get_prompt(local_var_t *arr, char **env)
{
    char *command = NULL;
    size_t size = 0;
    int nbr_bytes = 0;

    if (!isatty(0))
        return if_in_tty(arr, env);
    while (1) {
        display_prompt();
        get_special_var(arr, env);
        nbr_bytes = getline(&command, &size, stdin);
        if (verify_ctrl_d(&command, nbr_bytes) == -1)
            continue;
        handle_input(arr, command, env);
        command = NULL;
    }
}
