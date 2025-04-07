/*
** EPITECH PROJECT, 2024
** my_sort_int_array.c
** File description:
** task06
*/

#include "my.h"

/**
* @brief Verify if the array is sorted
* @param array Int array to verify
* @param size Size of the array
* @return 1 if array is sorted, 0 else.
*/
int verify_sort(int *array, int size)
{
    for (int i = 1; i < size; i++) {
        if (array[i - 1] > array[i])
            return 0;
    }
    return 1;
}

/**
* @brief Sort an int array with Bubble sort
* @param array Int array to verify
* @param size Size of the array
*/
void my_sort_int_array(int *array, int size)
{
    for (int i = 1; !verify_sort(array, size); i++) {
        if (i >= size)
            i = 1;
        if (array[i - 1] > array[i])
            my_swap(&array[i - 1], &array[i]);
    }
}
