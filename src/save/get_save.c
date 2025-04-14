/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** get_save
*/

#include "lib.h"
#include "myworld.h"
#include "textbox.h"
#include "string.h"
#include "mymath.h"
#include <stdlib.h>

static int check_header(char **tab, int *x, int *y)
{
    for (int i = 0; i < NAME; i++) {
        if (strlen(tab[i]) > MAX_STR || is_int(tab[i], "natural") == ERROR)
            return ERROR;
    }
    if (strlen(tab[NAME]) > MAX_NAME)
        return ERROR;
    *x = atoi(tab[X]);
    *y = atoi(tab[Y]);
    return SUCCESS;
}

static int check_line(char *line, int x)
{
    int count = 0;
    char *height = strtok(line, " ");

    while (height != NULL) {
        if (count > x)
            return ERROR;
        if (is_int(height, "integer") == ERROR)
            return ERROR;
        count++;
        height = strtok(NULL, " ");
    }
    if (count <= x)
        return ERROR;
    return SUCCESS;
}

static int check_body(char **tab, int x, int y)
{
    int i = 0;
    char *line = 0;

    while (tab[i] != NULL) {
        if (i > y)
            return ERROR;
        line = strdup(tab[i]);
        if (line == NULL)
            return ERROR;
        if (check_line(line, x) == ERROR) {
            free(line);
            return ERROR;
        }
        free(line);
        i++;
    }
    if (i <= y)
        return ERROR;
    return SUCCESS;
}

static int check_save(char **tab)
{
    int x = 0;
    int y = 0;

    if (check_header(tab, &x, &y) == ERROR
        || check_body(tab + NAME + 1, x, y) == ERROR)
        return ERROR;
    return SUCCESS;
}

static int initiate_body(char **tab, infos_map_t *info)
{
    char *line = NULL;
    char *nb = NULL;

    info->heights = malloc(sizeof(int *) * (info->size.y));
    if (info->heights == NULL)
        return ERROR;
    for (int i = 0; i < info->size.y; i++) {
        info->heights[i] = malloc(sizeof(int) * info->size.x);
        if (info->heights[i] == NULL) {
            free_random_heights(info->size, info->heights);
            return ERROR;
        }
        line = tab[i];
        nb = strtok(line, " ");
        for (int j = 0; nb != NULL; j++) {
            info->heights[i][j] = atoi(nb);
            nb = strtok(NULL, " ");
        }
    }
    return SUCCESS;
}

static int initiate_struct(char **tab, infos_map_t *info, textbox_t *text)
{
    info->size.x = atoi(tab[X]) + 1;
    info->size.y = atoi(tab[Y]) + 1;
    for (int i = 0; i < NAME; i++) {
        strcpy(text->str[i], tab[i]);
    }
    strcpy(text->name, tab[NAME]);
    if (initiate_body(tab + NAME + 1, info) == ERROR) {
        free_textbox(text);
        return ERROR;
    }
    return SUCCESS;
}

int get_save(char *file, infos_map_t *info, textbox_t *text)
{
    char *fd = open_file(file);
    char **tab = NULL;

    if (fd == NULL)
        return ERROR;
    tab = my_str_to_word_array(fd, "\n");
    if (tab == NULL)
        return ERROR;
    if (check_save(tab) == ERROR || initiate_struct(tab, info, text)) {
        free(fd);
        free_array(tab);
        return ERROR;
    }
    set_value(info, text, sfFalse);
    free(fd);
    free_array(tab);
    return SUCCESS;
}
