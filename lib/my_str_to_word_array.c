/*
** EPITECH PROJECT, 2024
** my_str_to_word_array.c
** File description:
** task04
*/

#include "my.h"

/**
* @brief Determinate if the character c is a separator
* @param c Character to analyse
* @param unauthorized String who contain all separators
* @return 0 if the character is a separator or 1 if the character is not a
* separator.
*/
int is_unauthorized(char c, char const *unauthorized)
{
    int present = 1;

    for (int i = 0; unauthorized[i] != '\0'; i++) {
        if (c == unauthorized[i])
            present = 0;
    }
    return present;
}

/**
* @brief Determinate the size of actual separator portion on string
* @param str String to analyse
* @param index Index of string to begin the analyse
* @param unauthorized String who contain all separators
* @return The size of the portion of separators (between two words)
*/
int size_not_word(char const *str, int index, char const *unauthorized)
{
    for (; !is_unauthorized(str[index], unauthorized)
        && str[index] != '\0'; index++);
    return index;
}

/**
* @brief Count the number of words in the string to know how many memory place
* the program must allocate.
* @param str String to analyse
* @param unauthorized String who contain all separators
* @return The number of words
*/
int nb_word(char const *str, char const *unauthorized)
{
    int nbr = is_unauthorized(str[0], unauthorized);

    for (int i = 1; str[i] != '\0'; ++i) {
        if (!is_unauthorized(str[i - 1], unauthorized) &&
            is_unauthorized(str[i], unauthorized))
                nbr++;
    }
    return nbr;
}

/**
* @brief Determinate the size of actual word portion on string
* @param str String to analyse
* @param index Index of string to begin the analyse
* @param unauthorized String who contain all separators
* @return The size of the portion of word (between two separators)
*/
int size_word(char const *str, int index, char const *unauthorized)
{
    int size = 0;
    int i = index;

    for (; is_unauthorized(str[i], unauthorized) && str[i] != '\0'; i++)
        size++;
    return size;
}

static char *fill_word(char const *str, int *index_str, int word_size)
{
    char *word = malloc(sizeof(char) * (word_size + 1));

    if (!word)
        return NULL;
    for (int j = 0; j < word_size; j++) {
        word[j] = str[*index_str];
        (*index_str)++;
    }
    word[word_size] = '\0';
    return word;
}

/**
* @brief Separate a string into a string array who will contain all words
* separated by separators characters
* @param str String to analyse
* @param unauthorized String who contain all separators
* @return The string array or NULL in case of errors
*/
char **my_str_to_word_array(char const *str, char const *unauthorized)
{
    int word_number = nb_word(str, unauthorized);
    int index_str = 0;
    int word_size = 0;
    char **result = malloc(sizeof(char *) * (word_number + 1));

    if (!result)
        return NULL;
    for (int i = 0; i < word_number; i++) {
        index_str = size_not_word(str, index_str, unauthorized);
        word_size = size_word(str, index_str, unauthorized);
        result[i] = fill_word(str, &index_str, word_size);
        if (!result[i])
            return NULL;
    }
    result[word_number] = NULL;
    return result;
}
