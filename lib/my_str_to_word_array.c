/*
** EPITECH PROJECT, 2025
** day08
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>
#include <stddef.h>

static char *word(char const *str, int start, int stop)
{
    char *temp = malloc(sizeof(char) * (stop - start + 1));
    int compt = 0;

    if (temp == NULL)
        return NULL;
    for (int i = start; i < stop; i++) {
        temp[compt] = str[i];
        ++compt;
    }
    temp[compt] = '\0';
    return (temp);
}

static int check_sep(char const *str, int i, char const *sep)
{
    int j = 0;

    while (sep[j] != '\0') {
        if (sep[j] == str[i])
            return (0);
        j++;
    }
    return (1);
}

static int sizearr(char const *str, char const *sep)
{
    int nbchar = 0;
    int i = 1;

    while (str[i] != '\0') {
        if (check_sep(str, i, sep) == 0 && check_sep(str, i - 1, sep) == 1)
            ++nbchar;
        i++;
    }
    if (check_sep(str, i - 1, sep) == 1)
        ++nbchar;
    return (nbchar + 1);
}

static int make_array(char ***tab, char const *str, char const *sep)
{
    int index = 0;
    int runner = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (check_sep(str, i, sep) == 1)
            ++runner;
        if (i > 0 && check_sep(str, i, sep) == 0
            && check_sep(str, i - 1, sep) == 1) {
            (*tab)[index] = word(str, i - runner, i);
            ++index;
            runner = 0;
        }
        i++;
    }
    if (check_sep(str, i - 1, sep) == 1) {
        (*tab)[index] = word(str, i - runner, i);
        ++index;
    }
    return index;
}

char **my_str_to_word_array(char const *str, char const *sep)
{
    char **tab = NULL;
    int index = 0;

    if (str == NULL || sep == NULL)
        return NULL;
    tab = malloc(sizeof(char *) * sizearr(str, sep));
    if (tab == NULL)
        return NULL;
    index = make_array(&tab, str, sep);
    tab[index] = NULL;
    return tab;
}
