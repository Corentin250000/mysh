/*
** EPITECH PROJECT, 2024
** mini_printf.c
** File description:
** function in order to recreate
*/

#include <stdarg.h>
#include "my.h"
#include <unistd.h>

int my_putchar_len(char c)
{
    return write(1, &c, 1);
}

int arguments(char c, va_list *args, int i, int *count)
{
    if (c == 'd')
        return my_put_nbr(va_arg(*args, int));
    if (c == 's')
        return my_putstr(va_arg(*args, char *));
    if (c == 'i')
        return my_put_nbr(va_arg(*args, int));
    if (c == 'c')
        return my_putchar_len(va_arg(*args, int));
    if (c == '%')
        return my_putchar_len('%');
    *count = -1;
    return *count;
}

int mini_printf(const char *format, ...)
{
    int i = 0;
    int count = 0;
    int nb_char = 0;
    va_list args;

    va_start(args, format);
    while (format[i] != '\0') {
        if (format[i] == '%') {
            i++;
            count = count + arguments(format[i], &args, i, &count);
        } else {
            my_putchar(format[i]);
            count++;
        }
        if (count == -1)
            return -1;
        i++;
    }
    va_end(args);
    return count;
}
