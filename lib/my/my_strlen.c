/*
** EPITECH PROJECT, 2024
** my_strlen.c
** File description:
** function that gives the size of a string
*/

int my_strlen(char const *str)
{
    int size = 0;

    if (!str)
        return 0;
    while (str[size] != '\0') {
        size = size + 1;
    }
    return size;
}
