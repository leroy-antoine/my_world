/*
** EPITECH PROJECT, 2025
** 106bombyx
** File description:
** is_int_float
*/

#include <string.h>
#include <ctype.h>

int is_int(char *av, char *set)
{
    int error = 0;
    int sign = 0;

    if (av[0] == '\0')
        return 84;
    for (int i = 0; av[i] != '\0'; i++) {
        if (isdigit(av[i]) == 0)
            error++;
        if (av[i] == '-' && sign == 0)
                sign++;
    }
    if (error == sign && strcmp(set, "integer") == 0)
        return 0;
    if (error != 0)
        return 84;
    return 0;
}
