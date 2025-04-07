/*
** EPITECH PROJECT, 2024
** my_putnbr_base.c
** File description:
** task18
*/

#include "my.h"

/**
* @brief Print a string
* @param str String to print
* @return Number of printed characters
*/
int my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
    return my_strlen(str);
}

/**
* @brief Calculate the power of a number
* @param nb the number
* @param p the power
* @return The power of nb by p (nb^p)
*/
int power(int nb, int p)
{
    int result = 1;

    if (p == 0)
        return 1;
    else if (p < 0)
        return 0;
    for (int i = 0; i < p; i++)
        result *= nb;
    return result;
}

/**
* @brief Determinate the maximum power (base^power) to determinate the size
* of final string.
* @param nb Number to change base
* @param base Target base
* @return The maximum power to be superior at nb
*/
int max_power_putnbr(int nb, int base)
{
    int result = 0;

    if (nb < 0)
        nb = -nb;
    for (; power(base, result) <= nb; result++);
    return result;
}

/**
* @brief Transform a number written in base 10 into a number written in another
* base and print it to standard output.
* @param nbr Number to change base
* @param base Target base
* @return 0
* @warning The base must be between 2 and 16.
*/
int my_putnbr_base(int nbr, char const *base)
{
    int base_int = my_getnbr(base);
    int res_mod = 0;
    int temp = nbr < 0 ? - nbr : nbr;
    char str[max_power_putnbr(nbr, base_int) + 1];

    str[max_power_putnbr(nbr, base_int)] = '\0';
    if (nbr < 0)
        my_putchar('-');
    for (int i = max_power_putnbr(nbr, base_int) - 1; i >= 0; i--) {
        res_mod = temp % base_int;
        str[i] = character_to_put(res_mod);
        temp /= base_int;
    }
    my_putstr(str);
    return 0;
}
