/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** event
*/

#include "myworld.h"
#include "save.h"
#include "textbox.h"
#include <string.h>
#include <stdlib.h>

static int select_save(sfEvent event, int start, int max)
{
    int nb = -1;

    if (event.type == sfEvtKeyPressed)
        if (event.key.code >= sfKeyNum1 && event.key.code <= sfKeyNum3)
            nb = event.key.code - sfKeyNum1 + start;
    if (nb != -1 && nb < max)
        return nb;
    return -1;
}

static void move_list(sfEvent event, int *start, int max)
{
    if (max < NB_SAVE)
        return;
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp) {
        (*start)--;
        if (*start < 0)
            *start = 0;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown) {
        (*start)++;
        if (*start + NB_SAVE > max && *start != 0)
            *start = max - NB_SAVE;
    }
}

static int load_map(
    game_t *game, textbox_t *text, infos_map_t *infos, char *str)
{
    int len = strlen(str) + strlen(SAVE) + 1;
    char *path = malloc(sizeof(char) * len);

    if (path == NULL)
        return ERROR;
    path = strcpy(path, SAVE);
    path = strcat(path, str);
    if (get_save(path, infos, text) == SUCCESS) {
        free(path);
        set_value(infos, text, sfFalse);
        game->old_scene = game->scene;
        game->scene = DRAW_MAP;
        game->start = 0;
        return SUCCESS;
    }
    free(path);
    return ERROR;
}

int save_event(game_t *game, textbox_t *text, infos_map_t *infos, char **str)
{
    sfEvent event;
    int save = 0;
    int return_value = SUCCESS;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(event, game);
        music_setvolume(event, game);
        change_scene(event, game);
        move_list(event, &game->start, game->max);
        save = select_save(event, game->start, game->max);
        if (save != -1)
            return_value = load_map(game, text, infos, str[save]);
    }
    return return_value;
}

void fail_event(game_t *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(event, game);
        music_setvolume(event, game);
        change_scene(event, game);
    }
}
