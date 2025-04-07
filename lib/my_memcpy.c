/*
** EPITECH PROJECT, 2025
** my_memcpy.c
** File description:
** ...
*/

#include "my.h"

/**
* @brief Copy the memory from src to dest
* @param dest Destination pointer
* @param src Source pointer
* @param size Size of the content to copy
* @note If src is NULL, the function quit before the copy,
* so dest doesn't change
*/
void my_memcpy(void *dest, void *src, size_t size)
{
    void *temp_dest = dest;
    void *temp_src = src;

    if (!src)
        return;
    for (size_t i = 0; i < size; ++i) {
        *(char *) dest = *(char *) src;
        dest++;
        src++;
    }
    dest = temp_dest;
    src = temp_src;
}
