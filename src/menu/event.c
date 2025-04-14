/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** event
*/

#include "myworld.h"

void menu_event(game_t *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(event, game);
        music_setvolume(event, game);
        change_scene(event, game);
    }
}
