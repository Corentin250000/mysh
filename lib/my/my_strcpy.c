/*
** EPITECH PROJECT, 2024
** my_strcpy.c
** File description:
** copy a string to another
*/

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
