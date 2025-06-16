/*
** EPITECH PROJECT, 2025
** test_local_variables.c
** File description:
** ...
*/

#include "../include/my.h"
#include "useful_functions.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(detect_call_variable, variable_called)
{
    char **args = malloc(sizeof(char *) * 5);

    cr_assert_not_null(args);
    args[0] = my_strdup("ls");
    cr_assert_not_null(args[0]);
    args[1] = my_strdup("45");
    cr_assert_not_null(args[1]);
    args[2] = my_strdup("$test");
    cr_assert_not_null(args[2]);
    args[3] = my_strdup("-lA");
    cr_assert_not_null(args[3]);
    args[4] = NULL;
    cr_assert(detect_call_variable(args) == 2);
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

Test(detect_call_variable, no_variable_call)
{
    char **args = malloc(sizeof(char *) * 5);

    cr_assert_not_null(args);
    args[0] = my_strdup("ls");
    cr_assert_not_null(args[0]);
    args[1] = my_strdup("45");
    cr_assert_not_null(args[1]);
    args[2] = my_strdup("test");
    cr_assert_not_null(args[2]);
    args[3] = my_strdup("-lA");
    cr_assert_not_null(args[3]);
    args[4] = NULL;
    cr_assert(detect_call_variable(args) == -1);
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

Test(detect_call_variable, NULL_args)
{
    char **args = NULL;

    cr_assert(detect_call_variable(args) == -1);
}

Test(size_array, simple_test)
{
    char **args = malloc(sizeof(char *) * 5);

    cr_assert_not_null(args);
    args[0] = my_strdup("ls");
    cr_assert_not_null(args[0]);
    args[1] = my_strdup("45");
    cr_assert_not_null(args[1]);
    args[2] = my_strdup("test");
    cr_assert_not_null(args[2]);
    args[3] = my_strdup("-lA");
    cr_assert_not_null(args[3]);
    args[4] = NULL;
    cr_assert(size_array(args) == 4);
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

Test(size_array, NULL_arr)
{
    char **args = NULL;

    cr_assert(size_array(args) == -1);
}

Test(separate_variable, simple_test)
{
    char **var = separate_variable(" \n test ert\n\tazerty\t");

    cr_assert_not_null(var);
    cr_assert(size_array(var) == 3);
    cr_assert_str_eq(var[0], "test");
    cr_assert_str_eq(var[1], "ert");
    cr_assert_str_eq(var[2], "azerty");
    for (int i = 0; var[i] != NULL; i++)
        free(var[i]);
    free(var);
}

Test(replace_args, correct_replace)
{
    char **new_args;
    char **args = malloc(sizeof(char *) * 5);
    char **var = separate_variable(" \n test ert\n\tazerty\t");

    cr_assert_not_null(var);
    cr_assert_not_null(args);
    args[0] = my_strdup("ls");
    cr_assert_not_null(args[0]);
    args[1] = my_strdup("45");
    cr_assert_not_null(args[1]);
    args[2] = my_strdup("$test");
    cr_assert_not_null(args[2]);
    args[3] = my_strdup("-lA");
    cr_assert_not_null(args[3]);
    args[4] = NULL;
    new_args = replace_args(var, args);
    cr_assert(size_array(new_args) == 6);
    cr_assert_str_eq(new_args[0], "ls");
    cr_assert_str_eq(new_args[1], "45");
    cr_assert_str_eq(new_args[2], "test");
    cr_assert_str_eq(new_args[3], "ert");
    cr_assert_str_eq(new_args[4], "azerty");
    cr_assert_str_eq(new_args[5], "-lA");
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
    for (int i = 0; var[i] != NULL; i++)
        free(var[i]);
    free(var);
    free(new_args);
}

Test(replace_args, no_variable)
{
    char **new_args;
    char **args = malloc(sizeof(char *) * 5);
    char **var = separate_variable(" \n test ert\n\tazerty\t");

    cr_assert_not_null(var);
    cr_assert_not_null(args);
    args[0] = my_strdup("ls");
    cr_assert_not_null(args[0]);
    args[1] = my_strdup("45");
    cr_assert_not_null(args[1]);
    args[2] = my_strdup("test");
    cr_assert_not_null(args[2]);
    args[3] = my_strdup("-lA");
    cr_assert_not_null(args[3]);
    args[4] = NULL;
    new_args = replace_args(var, args);
    cr_assert(size_array(new_args) == 4);
    cr_assert_str_eq(new_args[0], "ls");
    cr_assert_str_eq(new_args[1], "45");
    cr_assert_str_eq(new_args[2], "test");
    cr_assert_str_eq(new_args[3], "-lA");
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
    for (int i = 0; var[i] != NULL; i++)
        free(var[i]);
    free(var);
}

Test(replace_args, NULL_args)
{
    char **new_args;
    char **args = NULL;
    char **var = separate_variable(" \n test ert\n\tazerty\t");

    new_args = replace_args(var, args);
    cr_assert_null(new_args);
    for (int i = 0; var[i] != NULL; i++)
        free(var[i]);
    free(var);
}
