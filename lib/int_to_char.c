/*
** EPITECH PROJECT, 2024
** int_to_char.c
** File description:
** my_atoi
*/

#include "my.h"

/**
* @brief Convert an unsigned int into a string
* @param data Unsigned int to convert
* @return A string who contain the unsigned int. Return NULL if a memory
* allocation has failed.
* @warning The final string contain undesirables zeros at the beginning of the
* string.
*
* @warning Use int_to_char() to avoid them.
*/
char *create_string(unsigned int data)
{
    char *before_result = malloc(sizeof(char) * 10 + 1);
    char *result;
    int divise = 1000000000;
    unsigned int temp = data;
    unsigned int result_division;

    if (!before_result)
        return NULL;
    for (int i = 0; divise != 0; i++) {
        result_division = temp / divise;
        before_result[i] = 48 + result_division;
        temp -= divise * result_division;
        divise /= 10;
    }
    before_result[10] = '\0';
    result = my_strdup(before_result);
    free(before_result);
    return result;
}

/**
* @brief Remove all undesirables zeros at the beginning of the string.
* @param nb String to change
* @param size Size of the string
* @return A string who contain the unsigned int without undesirables zeros.
* Return NULL if a memory allocation has failed.
*/
char *remove_zeros(char *nb, int size)
{
    int other_nb = 0;
    int nb_zeros = 0;
    int j = 0;
    char *result;

    for (int i = 0; i < size; i++) {
        if (other_nb != 0)
            break;
        if (nb[i] == '0')
            nb_zeros++;
        else
            other_nb++;
    }
    result = malloc(sizeof(char) * (size - nb_zeros + 1));
    if (!result)
        return NULL;
    for (; j < size - nb_zeros; j++)
        result[j] = nb[j + nb_zeros];
    result[j] = '\0';
    return result;
}

/**
* @brief Convert an unsigned int into a string. Remove all undesirables zeros.
* @param data Unsigned int to convert
* @return A string who contain the number without zeros at the beginning.
* Return NULL if a memory allocation has failed.
* @note If you want to keep all zeros, use create_string() instead.
*
* @note If you already have your string, and just want to remove the
* unwanted zeros, use remove_zeros() instead.
*/
char *int_to_char(unsigned int data)
{
    char *str_with_zero = create_string(data);
    char *str_without_zero;

    if (!str_with_zero)
        return NULL;
    str_without_zero = remove_zeros(str_with_zero, my_strlen(str_with_zero));
    free(str_with_zero);
    if (!str_without_zero)
        return NULL;
    return str_without_zero;
}
