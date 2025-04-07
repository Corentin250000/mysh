/*
** EPITECH PROJECT, 2024
** my_getnbr.c
** File description:
** task05
*/

#include "my.h"
#include <limits.h>

/**
* @brief Calculate the number of minus '-' to determinate if the number is
* negative
* @param str String to analyse
* @return 0 if the number is positive, 1 else
*/
int is_negative(char const *str)
{
    int nb_minus = 0;

    for (int i = 0; str[i] != '\0' && (str[i] == '-' || str[i] == '+'); i++) {
        if (str[i] == '-')
            nb_minus++;
    }
    return nb_minus % 2 == 0 ? 0 : 1;
}

/**
* @brief Count the number of digit in string
* @param str String to analyse
* @return The number of digits
*/
int nb_digits_str(char const *str)
{
    int nb_digits = 0;
    int j = 0;

    for (; str[j] != '\0' && (str[j] == '-' || str[j] == '+'); j++);
    for (; str[j] != '\0' && str[j] == '0'; j++);
    for (; str[j] != '\0' && (str[j] >= '0' && str[j] <= '9'); j++) {
        nb_digits++;
    }
    return nb_digits;
}

/**
* @brief Calculate the power of 10 according to nb_digits
* @param nb_digits the number of digits
* @return The power of ten
*/
int n_power_ten(int nb_digits)
{
    int result = 1;

    for (int i = 0; i < nb_digits - 1; i++)
        result *= 10;
    return result;
}

/**
* @brief Verify if the number doesn't make an underflow or an overflow before
* being casted into an int
* @param nb_before_verification Number to analyse
* @param is_neg If the number is negative or not
* @return 1 if nb underflow or overflow, 0 else.
*/
int verify_overflow(long long nb_before_verification, int is_neg)
{
    if (is_neg)
        nb_before_verification *= -1;
    if (nb_before_verification > (long long) INT_MAX
        || nb_before_verification < (long long) INT_MIN)
            return 1;
    return 0;
}

/**
* @brief Get a number written in a string
* @param str String to extract the number
* @return The number or 0 in case of errors.
* @warning The number in str must not give an underflow or an overflow on
* result.
*/
int my_getnbr(char const *str)
{
    int is_neg = is_negative(str);
    int nb_digits = nb_digits_str(str);
    int multiply = n_power_ten(nb_digits);
    long long result = 0;
    int i = 0;

    if (nb_digits > 10)
        return 0;
    for (; str[i] != '\0' && (str[i] == '-' || str[i] == '+'); i++);
    for (; str[i] != '\0' && str[i] == '0'; i++);
    for (; str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'); i++) {
        result += multiply * (str[i] - 48);
        multiply /= 10;
    }
    if (verify_overflow(result, is_neg))
        return 0;
    return is_neg ? (int) - result : (int) result;
}
