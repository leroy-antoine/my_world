/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** main
*/

#include "lib.h"
#include "myworld.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int check_env(char **env)
{
    int i = 0;

    while (env[i] != 0) {
        if (strstr(env[i], "DISPLAY=:") != NULL)
            return SUCCESS;
        i++;
    }
    return ERROR;
}

static int show_usage(void)
{
    char *usage = open_file(USAGE);

    if (usage == NULL)
        return SUCCESS;
    printf("%s\n", usage);
    free(usage);
    return SUCCESS;
}

int main(int ac, char **av, char **env)
{
    if (ac == 2)
        if (strcmp("-h", av[1]) == 0)
            return show_usage();
    if (check_env(env) != ERROR)
        return my_starter();
    return ERROR;
}
