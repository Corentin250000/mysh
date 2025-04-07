/*
** EPITECH PROJECT, 2024
** my_put_nbr.c
** File description:
** task07
*/

#include "my.h"

/**
* @brief Print the number to standard output in argument and return the number
* of digits of number.
* @param nb Number to print
* @return The number of printed characters.
*/
int my_put_nbr(int nb)
{
    int zeros = 1;
    int nb_digits = 0;

    if (nb == -2147483648)
        return write(1, "-2147483648", 11);
    else if (nb < 0) {
        nb_digits += my_putchar('-');
        nb = - nb;
    }
    for (int div = 1000000000; div != 0; div /= 10) {
        if (nb / div == 0 && zeros == 1 && div != 1) {
            nb %= div;
            continue;
        }
        nb_digits += my_putchar(48 + (nb / div));
        zeros = 0;
        nb %= div;
    }
    return nb_digits;
}
