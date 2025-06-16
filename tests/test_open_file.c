/*
** EPITECH PROJECT, 2025
** test_open_file.c
** File description:
** ...
*/

#include "../include/my.h"
#include "useful_functions.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(open_file_error_handling, negative_file_descriptor, .init = redirect_all_std)
{
    char *buffer = malloc(50);
    int fd = -1;

    cr_assert_not_null(buffer);
    cr_assert(open_file_error_handling(fd, 0, buffer) == 84);
    cr_assert_stdout_eq_str("cannot open file\n");
}

Test(open_file_error_handling, negative_bytes_number, .init = redirect_all_std)
{
    char *buffer = malloc(50);
    int fd = 0;

    cr_assert_not_null(buffer);
    cr_assert(open_file_error_handling(fd, -1, buffer) == 84);
    cr_assert_stdout_eq_str("cannot read file\n");
}

Test(open_file_error_handling, null_buffer, .init = redirect_all_std)
{
    char *buffer = NULL;
    int fd = 0;

    cr_assert_null(buffer);
    cr_assert(open_file_error_handling(fd, 0, buffer) == 84);
    cr_assert_stdout_eq_str("The return value of the malloc function is NULL\n");
}

Test(open_file_error_handling, no_error)
{
    char *buffer = malloc(50);
    int fd = 0;

    cr_assert_not_null(buffer);
    cr_assert(open_file_error_handling(fd, 0, buffer) == 0);
}

Test(file_size, size_file_test)
{
    cr_assert(file_size("tests/test_size") == 3);
}

Test(open_file, simple_test)
{
    char *buffer = open_file("tests/test_size");

    cr_assert_not_null(buffer);
    cr_assert_str_not_empty(buffer);
    cr_assert_str_eq(buffer, "ert");
    free(buffer);
}

Test(open_file, empty_file)
{
    char *buffer = open_file("tests/empty_file");

    cr_assert_not_null(buffer);
    cr_assert_str_empty(buffer);
    free(buffer);
}

Test(open_file, null_filepath)
{
    char *buffer = open_file(NULL);

    cr_assert_null(buffer);
}

Test(open_file, no_rights_file)
{
    char *buffer;

    system("chmod 000 tests/no_rights");
    buffer = open_file(NULL);
    system("chmod 664 tests/no_rights");
    cr_assert_null(buffer);
}
