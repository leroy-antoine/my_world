/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** lib
*/

#ifndef LIB_H_
    #define LIB_H_

int is_int(char *av, char *set);
char **my_str_to_word_array(char const *str, char const *sep);
void free_array(char **tab);
char *open_file(char *file);
#endif
