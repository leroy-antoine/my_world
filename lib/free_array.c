/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** free_array
*/

#include <stdlib.h>

void free_array(char **tab)
{
    int i = 0;

    while (tab[i] != NULL) {
        free(tab[i]);
        i++;
    }
    free(tab);
}
