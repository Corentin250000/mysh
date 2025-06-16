/*
** EPITECH PROJECT, 2025
** get_git_branch.c
** File description:
** get git branch
*/

#include "../include/my.h"

static char *read_git_head(const char *git_path)
{
    char head_path[1024];
    char *ref = NULL;
    FILE *head_file;
    size_t len = 0;

    snprintf(head_path, sizeof(head_path), "%s/HEAD", git_path);
    head_file = fopen(head_path, "r");
    if (!head_file)
        return NULL;
    if (getline(&ref, &len, head_file) == -1) {
        fclose(head_file);
        return NULL;
    }
    fclose(head_file);
    ref[strcspn(ref, "\n")] = 0;
    if (strncmp(ref, "ref: refs/heads/", 16) == 0)
        memmove(ref, ref + 16, strlen(ref + 16) + 1);
    return ref;
}

char *find_git_directory(const char *path)
{
    char *git_path = malloc(1024);
    char *current = strdup(path);
    char *last_slash;

    while (1) {
        snprintf(git_path, 1024, "%s/.git", current);
        if (access(git_path, F_OK) == 0)
            break;
        last_slash = strrchr(current, '/');
        if (!last_slash || last_slash == current)
            return NULL;
        *last_slash = '\0';
    }
    free(current);
    return git_path;
}

char *get_git_branch(void)
{
    char *cwd = getcwd(NULL, 0);
    char *git_path = NULL;
    char *branch = NULL;
    char *formatted_output = NULL;

    if (!cwd)
        return NULL;
    git_path = find_git_directory(cwd);
    free(cwd);
    if (!git_path)
        return NULL;
    branch = read_git_head(git_path);
    free(git_path);
    if (!branch)
        return NULL;
    formatted_output = malloc(strlen(branch) + 32);
    sprintf(formatted_output, "%sgit%s:(%s%s%s)",
        BLUE, BLUE, RED, branch, BLUE);
    free(branch);
    return formatted_output;
}
