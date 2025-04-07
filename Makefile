##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/ask_command.c	\
		src/parsing.c	\
		src/parsing_env.c	\
		src/execution.c	\
		src/find_path_command.c	\
		src/make_fork.c	\
		src/builtin.c	\
		src/write_signal_message.c	\
		src/preparation_next_iteration.c	\
		src/my_free.c	\
		src/update_env.c	\
		src/command.c	\
		src/error_handling_cd.c	\
		src/error_handling_setenv.c	\
		src/list_exec.c	\
		src/parsing_pipe_redirections.c	\
		src/exec_pipe.c	\
		src/exec_redirection.c	\

SRC_UNIT_TESTS	=	src/ask_command.c	\
					src/parsing.c	\
					src/parsing_env.c	\
					src/execution.c	\
					src/find_path_command.c	\
					src/make_fork.c	\
					src/builtin.c	\
					src/write_signal_message.c	\
					src/preparation_next_iteration.c	\
					src/my_free.c	\
					src/update_env.c	\
					src/command.c	\
					src/list_exec.c	\
					src/error_handling_cd.c	\
					src/error_handling_setenv.c	\
					src/parsing_pipe_redirections.c	\
					src/exec_pipe.c	\
					src/exec_redirection.c	\
					tests/test_execution.c	\
					tests/test_builtin.c	\
					tests/test_find_path.c	\

OBJ	=	$(SRC:.c=.o)

OBJ_UNIT_TESTS	=	$(SRC_UNIT_TESTS:.c=.o)

NAME	=	mysh

CC	=	gcc

FLAGS	=	-Wall -Wextra -g -Iinclude

LIBS	=	-Llib/ -lmy

CFLAGS	=	$(FLAGS) $(LIBS)

$(NAME):
		make re -C lib/ > /dev/null
		$(CC) -o $(NAME) $(SRC) $(FLAGS) $(CFLAGS)

all:	$(NAME)

clean:
		rm -f $(OBJ)
		rm -f $(OBJ_UNIT_TESTS)
		find . -type f -name '*.gcda' -delete
		find . -type f -name '*.gcno' -delete
		find . -type f -name '*.gcov' -delete
		find . -type f -name '*~' -delete

fclean:	clean
		rm -f $(NAME)
		rm -f unit_tests

re:		fclean all

tests_run:	$(OBJ_UNIT_TESTS)
		make re -C lib/ > /dev/null
		$(CC) --coverage -lcriterion -o unit_tests $(SRC_UNIT_TESTS) $(CFLAGS)
		./unit_tests --verbose

coding_style:	fclean
			coding-style . .
			cat coding-style-reports.log
			rm -f coding-style-reports.log

.PHONY:	all clean fclean re tests_run coding_style
