/*
** EPITECH PROJECT, 2024
** select_print_function.c
** File description:
** Select the correct print function
*/

#include "my.h"

/**
* @brief Select the correct function to print current argument between:
*
* - my_put_nbr
*
* - my_putstr
*
* - my_putchar
* @param ap list of arguments (...)
* @param option Character who determine which function call
* @return The number of printed characters
*/
int select_print(va_list ap, char option)
{
    int size = 0;

    switch (option) {
    case 'd':
        size = my_put_nbr(va_arg(ap, int));
        break;
    case 'i':
        size = my_put_nbr(va_arg(ap, int));
        break;
    case 's':
        size = my_putstr(va_arg(ap, char *));
        break;
    case 'c':
        size = my_putchar((char) va_arg(ap, int));
        break;
    case '%':
        size = my_putchar('%');
    }
    return size;
}
