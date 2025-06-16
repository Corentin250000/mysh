##
## EPITECH PROJECT, 2024
## Makfile
## File description:
## Compilation tool Makefile
##

SRC	=	src/main.c\
		src/put_color.c\
		src/display_prompt.c\
		src/get_prompt.c\
		src/open_file.c\
		src/exec_basic_command.c\
		src/parser.c\
		src/get_signals.c\
		src/get_cd.c\
		src/get_setenv.c\
		src/get_unsetenv.c\
		src/get_pipes.c\
		src/get_redirect_right.c\
		src/get_redirect_left.c\
		src/clean_str.c\
		src/alias/alias.c\
		src/history/history.c\
		src/history/init_struct.c\
		src/history/exclamation.c\
		src/handle_and_or.c\
		src/call/call_builtin.c\
		src/variables/add_locale_variable.c\
		src/variables/detect_call_variable.c\
		src/variables/replace_variable.c\
		src/variables/search_variable.c\
		src/variables/builtin.c\
		src/variables/get_read_only.c\
		src/variables/get_special_variables.c\
		src/where.c\
		src/which.c\
		src/if.c\
		src/redirect_signals.c\
		src/alias/alias_param.c\
		src/alias/check_function.c\
		src/handle_magic_quote.c\
		src/get_git_branch.c\

SRC_UNIT_TESTS	=	src/put_color.c\
					src/display_prompt.c\
					src/get_prompt.c\
					src/open_file.c\
					src/exec_basic_command.c\
					src/parser.c\
					src/get_signals.c\
					src/get_cd.c\
					src/get_setenv.c\
					src/get_unsetenv.c\
					src/get_pipes.c\
					src/get_redirect_right.c\
					src/get_redirect_left.c\
					src/clean_str.c\
					src/alias/alias.c\
					src/history/history.c\
					src/history/init_struct.c\
					src/history/exclamation.c\
					src/handle_and_or.c\
					src/call/call_builtin.c\
					src/variables/add_locale_variable.c\
					src/variables/detect_call_variable.c\
					src/variables/replace_variable.c\
					src/variables/search_variable.c\
					src/variables/builtin.c\
					src/variables/get_read_only.c\
					src/variables/get_special_variables.c\
					src/where.c\
					src/which.c\
					src/if.c\
					src/redirect_signals.c\
					src/alias/alias_param.c\
					src/alias/check_function.c\
					src/handle_magic_quote.c\
					src/get_git_branch.c\
					tests/useful_functions.c\
					tests/test_open_file.c\
					tests/test_signals.c\
					tests/test_local_variables.c\

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

COVR =	--coverage -lcriterion

LIB =	-Llib/my -lmy

CFLAGS =	-g -I include

all: $(OBJ)
	make -C lib/my > /dev/null
	gcc $(CFLAGS) $(OBJ) -o $(NAME) $(LIB) -L include/

clean:
	make clean -C lib/my > /dev/null
	rm -f $(OBJ)
	rm -f $(NAME)

fclean:	clean
	make fclean -C lib/my > /dev/null
	rm -f $(NAME)
	rm -f *.gcno
	rm -f *.gcda
	rm -f unit_tests

re:	fclean all

all_test:
	make -C ./lib/my > /dev/null

unit_tests: all_test
	gcc $(COVR) -o unit_tests $(SRC_UNIT_TESTS) $(LIB) $(CFLAGS)

tests_run: unit_tests
	./unit_tests --verbose

gcovr:
	gcovr --exclude tests/ --txt-metric branch

coding_style:	fclean
			coding-style . .
			cat coding-style-reports.log
			rm -f coding-style-reports.log

.PHONY:	all clean fclean re all_test unit_tests tests_run gcovr coding_style
