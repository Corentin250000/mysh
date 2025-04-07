/*
** EPITECH PROJECT, 2025
** minishell2.h
** File description:
** Header file
*/

#include "../lib/my.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#ifndef STRUCTURES_H_
    #define STRUCTURES_H_

typedef enum redirection {
    SIMPLE_LEFT,
    DOUBLE_LEFT,
    SIMPLE_RIGHT,
    DOUBLE_RIGHT,
    NO_REDIRECTION,
    ERR_REDIRECTION,
    ERROR
} redirection_t;

typedef struct shell_char_s {
    int pipe;
    redirection_t redirection;
} shell_char_t;

/*
First part: free at each iteration
Last part: free at the end of program
*/
typedef struct command_s {
    // First part
    char *complete_command;
    char *command;
    char **options;
    char **execution_list;
    int nb_elem_exec;
    int builtin;
    shell_char_t shell_char;
    // Last part
    char *oldpwd;
    char **cpy_env;
    int size_env;
} command_t;

/*
Also for redirections, not only pipes
Must be free'd after each iteration
*/
typedef struct pipe_s {
    char *first_command;
    char *second_command;
    char *first_correct_path;
    char *second_correct_path;
    char **options_first_command;
    char **options_second_command;
} pipe_t;

#endif /* STRUCTURES_H_ */

///////////////////////////////////////////////////////////////////////////////

#ifndef MACROS_H_
    #define MACROS_H_

    #define PATH_MAX 4096

#endif /* MACROS_H_ */

///////////////////////////////////////////////////////////////////////////////

#ifndef FUNCTIONS_PROTOTYPES_H_
    #define FUNCTIONS_PROTOTYPES_H_

void my_free(void *to_free);

void free_content_structure(command_t *infos);
int error_free_structure(command_t *infos, int return_value);
int final_free_structure(command_t *infos, int return_value);
command_t *copy_env(char **env, int ac);

int print_errno(int error_value);
void separate_command_single_line(char const *line, command_t *infos);
ssize_t read_command_pipe(command_t *infos);
int ask_command(command_t *infos);

char *search_variable_env(command_t *infos, char const *variable);

int is_builtin(command_t *infos);
void search_shell_char(command_t *infos);
int parsing_command(command_t *infos);

int need_find_pathname(command_t *infos);
char **separate_all_path(char const *path);

int size_array(char **array);
int update_env(command_t *infos, char const *var, char const *new);
char **remove_variable(command_t *infos, char **cpy_env, char const *var);

int change_oldpwd(command_t *infos, char *new_oldpwd, char *home);
int print_error_msg_cd(char const *path, char *actual, char *home);
int is_a_directory(command_t *infos, char *actual, char *home);
int end_cd_function(command_t *infos, char *actual, char *home);

int is_a_number(char c);
int str_is_alphanum(char const *str);
int verify_name_variable(char const *var);

int my_env(command_t *infos);
int my_cd(command_t *infos);
int exec_builtin(command_t *infos, int *return_value);

void execution(command_t *infos, char const *good_path);

char *find_good_path(char const *command, char **all_path);
char *prepare_fork(command_t *infos);
int get_signal(__pid_t pid);
int make_fork(command_t *infos);

void print_signal_msg_final(__pid_t pid, char *good_path);

int command(command_t *infos, int *return_value);

void remove_command(command_t *infos);

void free_array(char **arr);
pipe_t *parsing_pipe_redirection(command_t *infos);

int search_fill_correct_path(pipe_t *pipe_struct, command_t *infos);
int exec_right(command_t *infos, int simple);
int exec_simple_left(command_t *infos);

void free_pipe(pipe_t *pipe_struct);
int need_find_pathname_pipe(char const *name);
int separate_commands_options(pipe_t *pipe_struct);
int exec_pipe(command_t *infos, char *path);

// recode

int exec_err_right(command_t *infos);

#endif /* FUNCTIONS_PROTOTYPES_H_ */
