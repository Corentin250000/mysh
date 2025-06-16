/*
** EPITECH PROJECT, 2024
** B-PSU-200-MLH-2-1-minishell1-hugo.jaskulski
** File description:
** open_file.c
*/

#include "../../include/my.h"

size_t files_size(char *file)
{
    struct stat info;

    if (stat(file, &info) < 0)
        return -1;
    return info.st_size;
}

int open_the_file(char const *filepath)
{
    int fd = 0;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return -1;
    return fd;
}

char *read_file(char const *filepath)
{
    int fd = open_the_file(filepath);
    size_t size = files_size((char *)filepath);
    char *buffer = NULL;

    if (size == -1)
        return NULL;
    buffer = malloc(sizeof(char) * (size + 1));
    if (!buffer)
        return NULL;
    if (read(fd, buffer, size) == -1) {
        free(buffer);
        return NULL;
    }
    buffer[size] = '\0';
    return buffer;
}
