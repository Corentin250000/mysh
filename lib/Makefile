##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC	=	conversion_letter.c	\
		convert_base.c	\
		my_compute_factorial_it.c	\
		my_compute_power_it.c	\
		my_getnbr_base.c	\
		my_getnbr.c	\
		my_put_nbr.c	\
		my_putchar.c	\
		my_putnbr_base.c	\
		my_sort_int_array.c	\
		my_sort_word_array.c	\
		my_str_to_word_array.c	\
		my_strcapitalize.c	\
		my_strcat.c	\
		my_strcmp.c	\
		my_strcpy.c	\
		my_strdup.c	\
		my_strlen.c	\
		my_strlowcase.c	\
		my_strncat.c	\
		my_strncmp.c	\
		my_strstr.c	\
		my_strupcase.c	\
		my_swap.c	\
		select_print_function.c	\
		mini_printf.c	\
		my_strncpy.c	\
		my_realloc.c	\
		int_to_char.c	\
		my_memcpy.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

CC	=	ar rc

$(NAME):
		gcc -c $(SRC) && $(CC) $(NAME) $(OBJ) && rm -f $(OBJ)

all:	$(NAME)

clean:
		rm -f $(OBJ)
		find . -type f -name '*~' -delete

fclean:	clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
