/*
** EPITECH PROJECT, 2024
** my_compute_power_it.c
** File description:
** task03
*/

#include "my.h"

/**
* @brief Calculate the power of a number
* @param nb the number
* @param p the power
* @return The power of nb by p (nb^p)
*/
int my_compute_power_it(int nb, int p)
{
    int result = nb;

    if (p < 0)
        return 0;
    else if (p == 0)
        return 1;
    for (int i = 0; i < p - 1; i++)
        result *= nb;
    return result;
}
