/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h include with
** all inclued functions
*/

#ifndef MY_H_
    #define MY_H_

void my_putchar(char c);
void error_my_putchar(char c);
int my_putstr(char const *str);
int error_my_putstr(char const *str);
int my_put_nbr(int nb);
void my_putchar(char c);
char **my_str_to_word_array(char *str, char *delim);
int my_strlen(char const *str);
int skip_unwanted_char(char *str, int i);
int my_show_word_array(char *const *tab);
int my_getnbr(char const *str);
char *my_strstr(char *str, char const *to_find);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strdup(char const *str);
int my_strcmp(char const *s1, char const *s2);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int n);
void clean_str(char *str);
void clean_str_keep_space(char *str);
int mini_printf(const char *format, ...);
int error_my_putstr(char const *str);
char *my_strncat(char *dest, char const *src, int nb);

#endif /* MY_H_ */
