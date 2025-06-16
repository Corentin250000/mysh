/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h include with
** all inclued functions and struct
*/

#ifndef MY_H_
    #define MY_H_

    #include <stddef.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <crypt.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <grp.h>
    #include <unistd.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <errno.h>

    #define BLUE   "\033[34m"
    #define RED    "\033[31m"
    #define RESET  "\033[0m"

typedef struct history_s {
    char *command;
    time_t timestamp;
    int number;
} history_t;

typedef struct var_s {
    char *varname;
    char *var;
} var_t;

typedef struct pipe_s {
    char *command;
    char **env;
} pipe_t;

typedef struct local_var_s {
    char **variables;
    int *rights;
} local_var_t;

typedef struct info_tab_s {
    char **tab_info;
    char **tab_string_info;
    char **name_alias;
    char *final_line;
} info_tab_t;

struct builtin_cmd {
    char *name;
    int (*func)(local_var_t *, char **, char **);
};

char *get_git_branch(void);
char *find_git_directory(const char *path);

//get cd
int get_cd(char *command, char **env);
int get_cd_minus(char **env);
char *remove_type(char **env, char *type);

//parser
int parser(local_var_t *arr, char *command, char **env);
int parse_setenv_command(char **command, char **env);
int parsing_all_args(char **args, char **env);

//get minishell prompt
int get_prompt(local_var_t *arr, char **env);
void handle_input(local_var_t *arr, char *command, char **env);

//open file
int open_file_error_handling(int fd, int nb_bytes, char *buffer);
int file_size(char *file);
char *open_file(char *filepath);

//get path
int execute_command(local_var_t *arr, char *command, char **env);
char *get_path(local_var_t *arr, char *command, char **env);
void exec_error_handling(char *command_path, char **args, char **env);

//get signals
int get_signals(int status);
char *get_current_path(void);

//get right redirection
int get_simple_redirection(local_var_t *arr, char **command_str, char **env,
    int i);
int get_double_redirection(local_var_t *arr, char **command_str, char **env,
    int i);

//get left redirection
int get_simple_redirection_left(local_var_t *arr, char **command, char **env,
    int i);

//get setenv && get_unsetenv
int get_setenv(char *command, char **env, char *value);
void get_unsetenv(char **env, char *command);

//get pipe
int process_piped_input(local_var_t *arr, char *input_line, char **env);
int handle_pipes_and_redirections(char *input, char **env);

//history
int display_history(char *history_path);
char *get_history_path(void);
char *resolve_exclamation_command(char *input);
char *resolve_exclamation_by_prefix(char *prefix, char *input);
char *resolve_exclamation_by_number(int number);
// int builtin_history(char **args, char **env);
int builtin_history(local_var_t *arr, char **command, char **env);
int builtin_setenv(local_var_t *arr, char **command, char **env);
int builtin_unsetenv(local_var_t *arr, char **command, char **env);
int builtin_exit(local_var_t *arr, char **command, char **env);
int builtin_cd(local_var_t *arr, char **command, char **env);
void load_history(void);
void save_history(void);
void add_to_history(const char *command);
history_t *init_history(void);
int *get_history_count(void);
int *get_history_next_id(void);

//handle && and ||
// int handle_or_commands(char **or_cmds, char **env, char *history_path);
int handle_or_commands(local_var_t *arr, char **or_cmds, char **env);
char **split_on_double_pipe(char *line);
char **split_and_or(char *line, char separator);
void free_array(char **array);

// prompt color
void display_prompt(void);
void reset_color(void);
void put_yellow(void);
void put_cyan(void);

//where
int create_where(local_var_t *arr, char **args, char **env);
int is_builtin(char *command);
char **get_env_paths(char **env);
char *create_full_path(char *dir, char *command);

//which
int create_which(local_var_t *arr, char **args, char **env);

//alias
int alias(char *line);
int check_exec(local_var_t *arr, char *line, char **env);
char *return_final_line(char **name_alias, char **tab_info, int i);

//magic quotes
char *apply_magic_quotes(local_var_t *arr, char *command, char **env);

//create if
int create_if(local_var_t *arr, char **args, char **env);

//lib function
int my_putstr(char const *str);
int my_put_nbr(int nb);
void my_putchar(char c);
int my_strlen(char const *str);
int my_getnbr(char const *str);
char *my_strstr(char *str, char const *to_find);
char **my_str_to_word_array(char *str, char *delim);
void clean_str_keep_space(char *str);
int my_show_word_array(char *const *tab);
int my_strcmp(char const *s1, char const *s2);
size_t files_size(char *file);
char *custom_my_strcat(char *dest, char const *src);
char *my_strcat(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int n);
int mini_printf(const char *format, ...);
char *my_strdup(char const *str);
char *my_strcpy(char *dest, char const *src);
int error_my_putstr(char const *str);
int cmp_exact_line(char const *s1, char const *s2);
char *str_clean(char *str);
int redirection_error(local_var_t *arr, char *line, char **env);
char *read_file(char const *filepath);
void display_prompt(void);
void reset_color(void);
void put_yellow(void);
void put_cyan(void);
char *my_strncat(char *dest, char const *src, int nb);
void *my_realloc(void *ptr, size_t new_size, size_t previous_size, int *error);
void my_memcpy(void *dest, void *src, size_t size);

// local variables

local_var_t *init_local_var_array(char **env);
char *get_variable(char **args, int is_varname);
char *build_varname(char const *varname);
int search_var_array(char **array, char const *varname);
char *search_variable(char const *varname, char **env, local_var_t *arr);
int count_local_var(local_var_t *arr);
int get_read_only(char **args);
int add_local_var(local_var_t *arr, char **args);
int detect_call_variable(char **args);
char *get_name_var(char **args);
int size_array(char **arr);
char **separate_variable(char *var);
char **replace_args(char **variable, char **args);
char *place_variable(local_var_t *arr, char *resolved, char **env);
int builtin_set(local_var_t *arr, char **args, char **env);
int builtin_unset(local_var_t *arr, char **args, char **env);
void free_local_var(local_var_t *arr);
void get_special_var(local_var_t *arr, char **env);

// redirect signals

void ignore_signals(void);
void reactive_signals(void);

#endif /* MY_H_ */
