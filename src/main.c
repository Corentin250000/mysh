/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** minishell1 main
*/

#include "../include/my.h"

//sudo ln -s $(realpath ./42sh) /usr/local/bin/42sh
//chmod +x 42sh
int run_script(local_var_t *arr, const char *filename, char **env)
{
    FILE *file = fopen(filename, "r");
    char *line = malloc(sizeof(char) * 1024);
    size_t len;

    if (!file || !line)
        return 1;
    while (fgets(line, 1024, file)) {
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (line[0] == '\0' || line[0] == '#')
            continue;
        if (strncmp(line, "#!", 2) == 0)
            continue;
        handle_input(arr, line, env);
    }
    free(line);
    fclose(file);
    return 0;
}

int main(int ac, char **av, char **env)
{
    int value;
    local_var_t *arr = init_local_var_array(env);

    (void)ac;
    (void)av;
    if (!arr)
        return 84;
    ignore_signals();
    load_history();
    if (ac > 1) {
        value = run_script(arr, av[1], env);
    } else
        value = get_prompt(arr, env);
    save_history();
    free_local_var(arr);
    return value;
}
