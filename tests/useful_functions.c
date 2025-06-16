/*
** EPITECH PROJECT, 2025
** useful_functions.c
** File description:
** ...
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}
