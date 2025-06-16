##
## EPITECH PROJECT, 2024
## makefile
## File description:
## make
##

SRC =	my_putchar.c\
		my_put_nbr.c\
		my_putstr.c\
		my_str_to_word_array.c\
		my_strlen.c\
		my_show_word_array.c\
		my_getnbr.c\
		my_strstr.c\
		my_strcmp.c\
		my_strncmp.c\
		my_strdup.c\
		my_strcat.c\
		my_strcpy.c\
		my_clean_str.c\
		mini_printf.c\
		open_file.c\
		my_strncat.c\
		my_realloc.c\
		my_memcpy.c\

OBJ = $(SRC:.c=.o)

NAME = libmy.a

$(NAME):  $(OBJ)
	ar rc $(NAME) $(OBJ)

all:	$(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
