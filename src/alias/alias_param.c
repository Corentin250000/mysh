/*
** EPITECH PROJECT, 2024
** B-PSU-200-MLH-2-1-42sh-anastasija.potapova
** File description:
** param_alias.c
*/

#include "../../include/my.h"

static char *verif_space(char **name_alias, int y, char *final_line)
{
    if (name_alias[y + 1] != NULL)
                final_line = custom_my_strcat(final_line, " ");
    return final_line;
}

char *return_final_line(char **name_alias, char **tab_info, int i)
{
    char *final_line = NULL;

    final_line = my_strdup(tab_info[i + 1]);
    if (name_alias[1] != NULL) {
        final_line = custom_my_strcat(final_line, " ");
        for (int y = 1; name_alias[y]; y++) {
            final_line = custom_my_strcat(final_line, name_alias[y]);
            final_line = verif_space(name_alias, y, final_line);
        }
    }
    return final_line;
}
