/*
** EPITECH PROJECT, 2025
** if.c
** File description:
** handle the if command like tcsh.
*/

#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"

static char *remove_quotes(char *str)
{
    int len = my_strlen(str);
    char *clean = NULL;

    if (len >= 2 &&
        ((str[0] == '"' && str[len - 1] == '"') ||
        (str[0] == '\'' && str[len - 1] == '\''))) {
        clean = malloc(sizeof(char) * (len - 1));
        if (!clean)
            return NULL;
        strncpy(clean, str + 1, len - 2);
        clean[len - 2] = '\0';
        return clean;
    } else {
        return my_strdup(str);
    }
}

static int get_total_length(char **args, char *sep)
{
    int total_len = 0;
    char *clean_arg = NULL;

    for (int i = 0; args[i]; i++) {
        clean_arg = remove_quotes(args[i]);
        total_len += my_strlen(clean_arg) + my_strlen(sep);
        free(clean_arg);
    }
    return total_len;
}

char *my_str_concat_from(char **args, char *sep)
{
    int total_len = get_total_length(args, sep);
    char *result = malloc(sizeof(char) * (total_len + 1));
    char *clean_arg = NULL;

    if (!result)
        return NULL;
    result[0] = '\0';
    for (int i = 0; args[i]; i++) {
        clean_arg = remove_quotes(args[i]);
        my_strcat(result, clean_arg);
        if (args[i + 1])
            my_strcat(result, sep);
        free(clean_arg);
    }
    return result;
}

char *clean_parenthesis(char *str)
{
    int len = my_strlen(str);
    char *clean = malloc(len + 1);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != '(' && str[i] != ')') {
            clean[j] = str[i];
            j++;
        }
    }
    clean[j] = '\0';
    return clean;
}

int my_str_isnum(char *str)
{
    int i = 0;

    if (!str || !str[0])
        return 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    for (; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int find_condition_index(char **args, int *index_out)
{
    char *a = NULL;
    char *b = NULL;
    char *c = NULL;

    for (int i = 1; args[i] && args[i + 1] && args[i + 2]; i++) {
        a = clean_parenthesis(args[i]);
        b = clean_parenthesis(args[i + 1]);
        c = clean_parenthesis(args[i + 2]);
        if (my_str_isnum(a) && my_str_isnum(c)) {
            *index_out = i;
            free(a);
            free(b);
            free(c);
            return 1;
        }
        free(a);
        free(b);
        free(c);
    }
    return 0;
}

static int equation_condition(char *a, char *op, char *b)
{
    int x = my_getnbr(a);
    int y = my_getnbr(b);

    if (my_strcmp(op, "==") == 0)
        return x == y;
    if (my_strcmp(op, "!=") == 0)
        return x != y;
    if (my_strcmp(op, "<") == 0)
        return x < y;
    if (my_strcmp(op, ">") == 0)
        return x > y;
    if (my_strcmp(op, "<=") == 0)
        return x <= y;
    if (my_strcmp(op, ">=") == 0)
        return x >= y;
    mini_printf("Unsupported operator: %s\n", op);
    return -1;
}

static void execute_if_command(local_var_t *arr, char **args, int start,
    char **env)
{
    char *cmd = NULL;

    if (args[start] && my_strcmp(args[start], ")") == 0)
        start++;
    if (args[start]) {
        cmd = my_str_concat_from(args + start, " ");
        handle_input(arr, cmd, env);
        free(cmd);
    }
}

int create_if(local_var_t *arr, char **args, char **env)
{
    int i = 0;
    char *cond1_str = NULL;
    char *op_str = NULL;
    char *cond2_str = NULL;
    int result = 0;

    if (!find_condition_index(args, &i)) {
        my_putstr("if: Too few arguments.\n");
        return 1;
    }
    cond1_str = clean_parenthesis(args[i]);
    op_str = clean_parenthesis(args[i + 1]);
    cond2_str = clean_parenthesis(args[i + 2]);
    result = equation_condition(cond1_str, op_str, cond2_str);
    if (result == -1)
        return 1;
    if (result)
        execute_if_command(arr, args, i + 3, env);
    return 0;
}
