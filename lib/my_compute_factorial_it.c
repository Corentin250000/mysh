/*
** EPITECH PROJECT, 2024
** my_compute_factorial_it.c
** File description:
** task01
*/

#include "my.h"

/**
* @brief Calculate the factorial of a number
* @param nb
* @return The factorial of nb
* @warning any number superior at 12 give 0, because the factorial of these
* number give an int overflow (>2.147.483.647).
*/
int my_compute_factorial_it(int nb)
{
    int result = 1;

    if (nb < 0 || nb > 12)
        return 0;
    else if (nb == 0)
        return 1;
    for (int i = 1; i <= nb; i++)
        result *= i;
    return result;
}
