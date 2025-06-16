/*
** EPITECH PROJECT, 2025
** open_file.c
** File description:
** function that open a file
*/

#include "../include/my.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int open_file_error_handling(int fd, int nb_bytes, char *buffer)
{
    if (fd == -1) {
        my_putstr("cannot open file\n");
        free(buffer);
        return 84;
    }
    if (nb_bytes < 0) {
        my_putstr("cannot read file\n");
        free(buffer);
        return 84;
    }
    if (buffer == NULL) {
        my_putstr("The return value of the malloc function is NULL\n");
        return 84;
    }
    return 0;
}

int file_size(char *file)
{
    struct stat info;

    stat(file, &info);
    return info.st_size;
}

char *open_file(char *filepath)
{
    int size = file_size(filepath);
    char *buffer = malloc(sizeof(char) * (size + 1));
    int fd = 0;
    int nb_bytes = 0;

    if (filepath == NULL || buffer == NULL)
        return NULL;
    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return NULL;
    nb_bytes = read(fd, buffer, size);
    buffer[nb_bytes] = '\0';
    if (open_file_error_handling(fd, nb_bytes, buffer) == 84)
        return NULL;
    close(fd);
    return buffer;
}
