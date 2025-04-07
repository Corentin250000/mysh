/*
** EPITECH PROJECT, 2024
** conversion_letter.c
** File description:
** conversion letter
*/

#include "my.h"

/**
* @brief Get the correct character to put for the base conversion
* @param res_mod Rest of the modulo
* @return The character to put.
*/
char character_to_put(int res_mod)
{
    char result = 0;

    if (res_mod >= 10)
        result = 65 + (res_mod - 10);
    else if (res_mod < 10)
        result = 48 + res_mod;
    return result;
}

/**
* @brief Get the correct value according to the character, the base and the
* power
* @param base Base of character
* @param letter The character to transform
* @param power_max Place in number
* @return The value corresponding to character, base and power
*/
int value_to_add(int base, char letter, int power_max)
{
    int result = 0;

    if (letter >= '0' && letter <= '9')
        result = (letter - 48) * power(base, power_max);
    else if ((letter >= 'A' && letter <= 'F') || (letter >= 'a' &&
        letter <= 'f'))
            result = (letter - 55) * power(base, power_max);
    return result;
}
