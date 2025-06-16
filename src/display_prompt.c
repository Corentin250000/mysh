/*
** EPITECH PROJECT, 2025
** display_prompt.c
** File description:
** display the prompt
*/

#include "../include/my.h"

void display_folder(char *cwd, char const *home)
{
    char *folder = NULL;

    if (home != NULL && strcmp(cwd, home) == 0)
        printf("➜  ~");
    else {
        folder = strrchr(cwd, '/');
        if (folder && folder[1] != '\0')
            folder++;
        else
            folder = cwd;
        printf("➜  %s", folder);
    }
}

void display_prompt(void)
{
    char *cwd = NULL;
    char *home = getenv("HOME");
    char *git_info = get_git_branch();

    cwd = getcwd(NULL, 0);
    put_cyan();
    display_folder(cwd, home);
    if (git_info) {
        printf(" %s", git_info);
        free(git_info);
    }
    reset_color();
    printf(" ");
    free(cwd);
}
