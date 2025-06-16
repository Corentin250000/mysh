/*
** EPITECH PROJECT, 2024
** my_strncmp.c
** File description:
** compare two string according to a size
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n) {
        i++;
    }
    if (i == n)
        return 0;
    return s1[i] - s2[i];
}
