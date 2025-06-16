/*
** EPITECH PROJECT, 2024
** B-PSU-200-MLH-2-1-42sh-anastasija.potapova
** File description:
** alias.c
*/

#include "../../include/my.h"
#include <stdio.h>
#include <unistd.h>

char **check_alias(char *line)
{
    int i = 0;
    char **tab_redirection = my_str_to_word_array(line, " ");

    while (tab_redirection[i]) {
        if (cmp_exact_line("alias", tab_redirection[i]) == 0) {
            return tab_redirection;
        }
        i++;
    }
    return NULL;
}

void which_print(char **tab_file, int i)
{
    int y = 0;

    if (tab_file[i + 3] != NULL &&
        cmp_exact_line(tab_file[i + 3], "alias") != 0) {
            y = (i + 3);
            my_putchar('(');
            my_putstr(tab_file[i + 2]);
            my_putchar(' ');
            for (; tab_file[y + 1] != NULL &&
            cmp_exact_line(tab_file[y + 1], "alias") != 0; y++) {
                my_putstr(tab_file[y]);
                my_putchar(' ');
            }
            my_putstr(tab_file[y]);
            my_putchar(')');
    } else
        my_putstr(tab_file[i + 2]);
}

int print_alias(void)
{
    char *info_file42 = read_file("/tmp/.42shrc");
    char **tab_file = NULL;
    int i = 0;

    if (info_file42 == NULL)
        return 0;
    tab_file = my_str_to_word_array(info_file42, " =\"\n\0");
    if (tab_file == NULL)
        return 1;
    while (tab_file[i]) {
        if (cmp_exact_line(tab_file[i], "alias") == 0) {
            my_putstr(tab_file[i + 1]);
            my_putchar('\t');
            which_print(tab_file, i);
            my_putchar('\n');
        }
        i++;
    }
    return 0;
}

static char *put_line_file(char **alias_info)
{
    char *line_file = my_strdup("alias ");

    line_file = custom_my_strcat(line_file, alias_info[1]);
    line_file = custom_my_strcat(line_file, "=\"");
    for (int i = 2; alias_info[i]; i++) {
        line_file = custom_my_strcat(line_file, alias_info[i]);
        if (alias_info[i + 1] != NULL)
            line_file = custom_my_strcat(line_file, " ");
    }
    line_file = custom_my_strcat(line_file, "\"\n");
    return line_file;
}

static int which_return_exist(int replaced)
{
    if (replaced != 0) {
        rename("/tmp/.tmp42shrc", "/tmp/.42shrc");
        remove("/tmp/.tmp42shrc");
        return 1;
    }
    remove("/tmp/.tmp42shrc");
    return 0;
}

static int loop_verif(char **lines, char **line_info, int fd, char *new_line)
{
    char **info_file = NULL;
    int replaced = 0;

    for (int i = 0; lines[i]; i++) {
        info_file = my_str_to_word_array(lines[i], " =\"\n");
        if (info_file && info_file[0] && info_file[1] &&
            cmp_exact_line(info_file[0], "alias") == 0 &&
            cmp_exact_line(info_file[1], line_info[1]) == 0) {
            write(fd, new_line, my_strlen(new_line));
            replaced++;
        } else {
            write(fd, lines[i], my_strlen(lines[i]));
            write(fd, "\n", 1);
        }
    }
    return replaced;
}

static int verif_exist(char **line_info, char *new_line)
{
    char *buffer_file = read_file("/tmp/.42shrc");
    int fd = open("/tmp/.tmp42shrc", O_CREAT | O_WRONLY, 0644);
    int replaced = 0;
    char **lines = NULL;

    if (fd == -1 || line_info[1] == NULL || buffer_file == NULL)
        return 0;
    lines = my_str_to_word_array(buffer_file, "\n");
    replaced = loop_verif(lines, line_info, fd, new_line);
    if (which_return_exist(replaced) == 1)
        return 1;
    return 0;
}

int alias(char *line)
{
    int fd;
    char **alias_info = check_alias(line);
    char *line_file;

    if (alias_info == NULL || (alias_info[1] != NULL && alias_info[2] == NULL))
        return 1;
    if (alias_info[1] == NULL)
        return print_alias();
    line_file = put_line_file(alias_info);
    if (verif_exist(alias_info, line_file) == 1)
        return 0;
    fd = open("/tmp/.42shrc", O_CREAT | O_WRONLY | O_APPEND, 0644);
    write(fd, line_file, my_strlen(line_file));
    close(fd);
    return 0;
}
