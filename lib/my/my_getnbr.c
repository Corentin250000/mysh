/*
** EPITECH PROJECT, 2023
** my_getnbr.c
** File description:
** function that convert char into integer
*/

#include <stddef.h>

static int error(char const *str, int i)
{
    if (str[i] == '\0') {
        return 0;
    }
}

int my_getnbr(char const *str)
{
    long i = 0;
    long y = 0;
    long n = 0;

    error(str, i);
    while (!(str[i] >= '0' && str[i] <= '9')) {
        if (str[i] == '-')
            n++;
        i++;
    }
    for (; str[i] >= 48 && str[i] <= 57; i++) {
        y *= 10;
        y += str[i] - 48;
        if (y > 2147483647 || y < -2147483648)
            return 0;
    }
    if (n % 2 != 0)
        y *= -1;
    return y;
}
