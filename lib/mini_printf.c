/*
** EPITECH PROJECT, 2024
** mini_printf.c
** File description:
** mini_printf
*/

#include "my.h"

/**
* @brief Verify if there is no incorrect flag
* @param format String to analyse
* @return 1 if there is no errors, 0 else.
*/
int verify_format(const char *format)
{
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && (format[i + 1] != 'd' &&
            format[i + 1] != 'i' && format[i + 1] != 'c' &&
            format[i + 1] != 's' && format[i + 1] != '%'))
                return 0;
        if (format[i] == '%') {
            i++;
            continue;
        }
    }
    return 1;
}

/**
* @brief Print the string to standard output
* @param format String to print this flags and their parameters in next
* parameters
* @param ... Others paramters according to flags in the format
* @return The number of printed characters of 84 in case of errors
*/
int mini_printf(const char *format, ...)
{
    va_list ap;
    int nb_char_printed = 0;

    va_start(ap, format);
    if (!verify_format(format)) {
        va_end(ap);
        return 84;
    }
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            nb_char_printed += select_print(ap, format[i + 1]);
            i++;
            continue;
        }
        nb_char_printed += my_putchar(format[i]);
    }
    va_end(ap);
    return nb_char_printed;
}
