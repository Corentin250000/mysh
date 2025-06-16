/*
** EPITECH PROJECT, 2024
** B-PSU-100-MLH-1-1-mysudo-anastasija.potapova
** File description:
** my_str_to_array.c
*/

#include <stdlib.h>
#include "../../include/my.h"

int char_in_delim(char c, char *delim)
{
    int i = 0;

    while (delim[i] != '\0') {
        if (c == delim[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

static int skip_char_unwanted(char *str, int i, char *delim)
{
    while (str[i] != '\0' && char_in_delim(str[i], delim) == 1) {
        i++;
    }
    return i;
}

int count_nb_words(char *str, char *delim)
{
    int i = 0;
    int count = 0;
    int size = my_strlen(str);

    while (i < size) {
        while (str[i] != '\0' && char_in_delim(str[i], delim) == 1) {
            i++;
        }
        if (str[i] != '\0') {
            count++;
        }
        while (str[i] != '\0' && char_in_delim(str[i], delim) == 0) {
            i++;
        }
    }
    return count;
}

int word_size(char *str, int i, char *delim)
{
    int size = 0;

    while (str[i] != '\0' && char_in_delim(str[i], delim) == 0) {
        size++;
        i++;
    }
    return size;
}

char *my_dup_array(int i, char *src, char *delim)
{
    int j = 0;
    int size = word_size(src, i, delim);
    char *dest = malloc(sizeof(char) * (size + 1));

    if (dest == NULL)
        return NULL;
    size = size + i;
    while (i < size) {
        dest[j] = src[i];
        j++;
        i++;
    }
    dest[j] = '\0';
    return dest;
}

static void free_array_str(char **array, int column)
{
    for (int j = 0; j < column; j++) {
        free(array[j]);
    }
    free(array);
    return;
}

char **my_str_to_word_array(char *str, char *delim)
{
    int i = skip_char_unwanted(str, 0, delim);
    int size_col = count_nb_words(str, delim);
    char **array = malloc(sizeof(char *) * (size_col + 1));
    int column = 0;

    if (array == NULL) {
        return NULL;
    }
    while (column < size_col) {
        array[column] = my_dup_array(i, str, delim);
        if (array[column] == NULL) {
        free_array_str(array, column);
        }
        i = i + word_size(str, i, delim);
        i = skip_char_unwanted(str, i, delim);
        column++;
    }
    array[column] = NULL;
    return array;
}
