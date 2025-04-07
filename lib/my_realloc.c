/*
** EPITECH PROJECT, 2025
** my_realloc.c
** File description:
** ...
*/

#include "my.h"

static void *replace_value(void *ptr, void *new_ptr, size_t previous_size)
{
    void *temp_ptr = ptr;
    void *temp_new_ptr = new_ptr;

    for (size_t i = 0; i < previous_size; ++i) {
        *((char *) new_ptr) = *((char *) ptr);
        ptr++;
        new_ptr++;
    }
    ptr = temp_ptr;
    free(ptr);
    new_ptr = temp_new_ptr;
    return new_ptr;
}

/**
* @brief Reallocate the pointer to new size, copy previous data into the new
* pointer and free the old pointer.
* @param ptr Pointer to reallocate
* @param new_size New size for the pointer
* @param previous_size Actual size of ptr
* @param error An address of int to know if there were any errors
* @return the new pointer reallocated with previous pointer's data or, in case
* of error, the unchanged ptr, with error put at 1.
* @note If ptr is NULL -> do a malloc of given size and return the new pointer.
*
* @note If size is inferior to 1 and ptr not NULL -> return unchanged ptr and
* error variable is put at 1.
*
* @note In case of allocation error -> return unchanged ptr and error variable
* is put at 1.
*
* @note If the function return unchanged ptr -> you must free yourself the
* pointer.
*/
void *my_realloc(void *ptr, size_t new_size, size_t previous_size, int *error)
{
    void *new_ptr;

    if (!ptr) {
        new_ptr = malloc(new_size);
        return new_ptr;
    } else if (new_size < 1) {
        *error = 1;
        return ptr;
    }
    new_ptr = malloc(new_size);
    if (!new_ptr) {
        *error = 1;
        return ptr;
    }
    return replace_value(ptr, new_ptr, previous_size);
}
