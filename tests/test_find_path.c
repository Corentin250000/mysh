/*
** EPITECH PROJECT, 2025
** test_find_path.c
** File description:
** ...
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell2.h"
#include "redirect.h"

Test(need_find_pathname, no_command)
{
    command_t *infos = malloc(sizeof(command_t));
    int result = 0;

    cr_assert_not_null(infos);
    infos->command = NULL;
    infos->builtin = 0;
    result = need_find_pathname(infos);
    cr_assert(result == 84);
}

Test(need_find_pathname, is_builtin)
{
    command_t *infos = malloc(sizeof(command_t));
    int result = 0;

    cr_assert_not_null(infos);
    infos->command = my_strdup("exit");
    cr_assert_not_null(infos->command);
    infos->builtin = 1;
    result = need_find_pathname(infos);
    cr_assert(result == 0);
}

Test(need_find_pathname, no_need_to_find_the_pathname_absolute_path)
{
    command_t *infos = malloc(sizeof(command_t));
    int result = 0;

    cr_assert_not_null(infos);
    infos->command = my_strdup("/bin/ls");
    cr_assert_not_null(infos->command);
    infos->builtin = 0;
    result = need_find_pathname(infos);
    cr_assert(result == 0);
}

Test(need_find_pathname, no_need_to_find_the_pathname_relative_path)
{
    command_t *infos = malloc(sizeof(command_t));
    int result = 0;

    cr_assert_not_null(infos);
    infos->command = my_strdup("../../../../../../../../bin/ls");
    cr_assert_not_null(infos->command);
    infos->builtin = 0;
    result = need_find_pathname(infos);
    cr_assert(result == 0);
}

Test(need_find_pathname, no_need_to_find_the_pathname_wrong_absolute_path)
{
    command_t *infos = malloc(sizeof(command_t));
    int result = 0;

    cr_assert_not_null(infos);
    infos->command = my_strdup("/dev/ls");
    cr_assert_not_null(infos->command);
    infos->builtin = 0;
    result = need_find_pathname(infos);
    cr_assert(result == 1);
}

Test(need_find_pathname, no_need_to_find_the_pathname_wrong_relative_path)
{
    command_t *infos = malloc(sizeof(command_t));
    int result = 0;

    cr_assert_not_null(infos);
    infos->command = my_strdup("../../../../../../../bin/ls");
    cr_assert_not_null(infos->command);
    infos->builtin = 0;
    result = need_find_pathname(infos);
    cr_assert(result == 1);
}

Test(need_find_pathname, need_to_find_the_pathname)
{
    command_t *infos = malloc(sizeof(command_t));
    int result = 0;

    cr_assert_not_null(infos);
    infos->command = my_strdup("ls");
    cr_assert_not_null(infos->command);
    infos->builtin = 0;
    result = need_find_pathname(infos);
    cr_assert(result == 1);
}

Test(separate_all_path, no_path)
{
    char *path = NULL;
    char **all_path = separate_all_path(path);

    cr_assert_null(all_path);
}

Test(separate_all_path, simple_test)
{
    char *path = my_strdup("PATH=/home/corentin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin:/home/corentinpasquier/.local/bin:/home/corentin/Epitech_projects/2024-2025_tek1/Create-base-Makefile:/home/corentin/Epitech_projects/2024-2025_tek1/put_header_c_file:/home/corentin/.local/bin");
    char **all_path;

    cr_assert_not_null(path);
    all_path = separate_all_path(path);
    cr_assert_not_null(all_path);
    cr_assert_str_eq(all_path[0], "PATH");
}

Test(separate_all_path, simple_test_2)
{
    char *path = my_strdup("PATH=/home/corentin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin:/home/corentinpasquier/.local/bin:/home/corentin/Epitech_projects/2024-2025_tek1/Create-base-Makefile:/home/corentin/Epitech_projects/2024-2025_tek1/put_header_c_file:/home/corentin/.local/bin");
    char **all_path;

    cr_assert_not_null(path);
    all_path = separate_all_path(path);
    cr_assert_not_null(all_path);
    cr_assert_str_eq(all_path[3], "/usr/local/bin");
}

Test(separate_all_path, simple_test_3)
{
    char *path = my_strdup("PATH=/home/corentin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin:/home/corentinpasquier/.local/bin:/home/corentin/Epitech_projects/2024-2025_tek1/Create-base-Makefile:/home/corentin/Epitech_projects/2024-2025_tek1/put_header_c_file:/home/corentin/.local/bin");
    char **all_path;

    cr_assert_not_null(path);
    all_path = separate_all_path(path);
    cr_assert_not_null(all_path);
    cr_assert_null(all_path[16]);
}
