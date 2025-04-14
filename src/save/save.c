/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** save
*/

#include "save.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"
#include <unistd.h>

static char *get_path(char *str)
{
    int len = strlen(str) + strlen(SAVE) + strlen(EXT) + 1;
    char *path = malloc(sizeof(char) * len);

    if (path == NULL)
        return NULL;
    path = strcpy(path, SAVE);
    path = strcat(path, str);
    path = strcat(path, EXT);
    return path;
}

static void ptint_infile(FILE *fd, infos_map_t *info, textbox_t *text)
{
    int i = 0;
    int j = 0;

    fprintf(fd, "%s\n%s\n%s\n%s\n",
        text->str[X], text->str[Y], text->str[SEED], text->name);
    while (i < info->size.y) {
        j = 0;
        while (j < info->size.x) {
            fprintf(fd, "%2d ", info->heights[i][j]);
            j++;
        }
        fprintf(fd, "\n");
        i++;
    }
}

void my_save(infos_map_t *info, textbox_t *text)
{
    char *path = get_path(text->name);
    FILE *fd = NULL;

    if (path == NULL)
        return;
    fd = fopen(path, "w");
    if (fd == NULL) {
        free(path);
        return;
    }
    ptint_infile(fd, info, text);
    free(path);
    fclose(fd);
}
