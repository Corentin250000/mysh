/*
** EPITECH PROJECT, 2024
** my_put_nbr.c
** File description:
** print all digits combinaisons
*/

#include "../../include/my.h"

int my_put_nbr(int nb)
{
    long int nbr = nb;

    if (nbr < 0) {
        nbr = - nbr;
        my_putchar('-');
    }
    if (nbr >= 10) {
        my_put_nbr(nbr / 10);
        my_putchar(nbr % 10 + '0');
    }
    if (nbr < 10) {
        my_putchar(nbr + '0');
    }
    return nbr;
}
