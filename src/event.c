/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** event handling
*/

#include "myworld.h"
#include "mymath.h"
#include "textbox.h"

void music_setvolume(sfEvent event, game_t *game)
{
    float volume = sfMusic_getVolume(game->music);

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF1) {
        if (volume < 1)
            volume = VOL_MAX;
        else
            volume = VOL_MIN;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF2) {
        if (volume > VOL_MIN + VOL_GAP)
            volume -= VOL_GAP;
        else
            volume = 0.0;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF3
        && volume < VOL_MAX - VOL_GAP)
        volume += VOL_GAP;
    sfMusic_setVolume(game->music, volume);
    sfMusic_setVolume(game->dig, volume);
    sfMusic_setVolume(game->hammer, volume);
}

static void next_scene(sfEvent event, game_t *game)
{
    int tmp = 0;

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF8) {
        if (game->scene != MY_SAVE)
            game->old_scene = game->scene;
        game->scene = MY_SAVE;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF9) {
        tmp = game->old_scene;
        game->old_scene = game->scene;
        game->scene = tmp;
    }
}

void change_scene(sfEvent event, game_t *game)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF7) {
        if (game->scene != TEXTBOX)
            game->old_scene = game->scene;
        game->scene = TEXTBOX;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyTab) {
        if (game->scene != MENU)
            game->old_scene = game->scene;
        game->scene = MENU;
    }
    next_scene(event, game);
}

void close_window(sfEvent event, game_t *game)
{
    if ((event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        || event.type == sfEvtClosed)
        sfRenderWindow_close(game->window);
}
