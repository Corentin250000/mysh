/*
** EPITECH PROJECT, 2025
** check_function.c
** File description:
** ...
*/

#include "../../include/my.h"

static int check_func_alias_part2(local_var_t *arr, info_tab_t infos,
    char **env, int i)
{
    if (my_strncmp(infos.tab_info[i], "alias ", 6) == 0) {
        infos.tab_string_info = my_str_to_word_array(infos.tab_info[i], " ");
        if (!cmp_exact_line(infos.tab_string_info[1], infos.name_alias[0])) {
            infos.final_line = return_final_line(infos.name_alias,
                infos.tab_info, i);
            parser(arr, infos.final_line, env);
            return 0;
        }
    }
}

static int check_func_alias(local_var_t *arr, char **tab_info, char *line,
    char **env)
{
    info_tab_t infos;

    infos.tab_info = tab_info;
    infos.tab_string_info = NULL;
    infos.name_alias = my_str_to_word_array(line, " ");
    infos.final_line = NULL;
    if (infos.name_alias == NULL)
        return 1;
    for (int i = 0; infos.tab_info[i]; i++) {
        if (check_func_alias_part2(arr, infos, env, i) == 0)
            return 0;
    }
    return 1;
}

int check_exec(local_var_t *arr, char *line, char **env)
{
    char *info_file42 = NULL;
    char **tab_info = NULL;
    char **tab_string_info = NULL;

    info_file42 = read_file("/tmp/.42shrc");
    if (!info_file42)
        return 1;
    tab_info = my_str_to_word_array(info_file42, "=\"\n\0");
    if (tab_info == NULL)
        return 1;
    if (check_func_alias(arr, tab_info, line, env) == 0)
        return 0;
    return 1;
}
