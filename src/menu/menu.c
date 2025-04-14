/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** menu
*/

#include "myworld.h"
#include "textbox.h"
#include "lib.h"
#include <stdlib.h>

void loop_menu(game_t *game, sfText *text)
{
    char *menu = open_file(MY_MENU);
    int pos = MT_Y * 2;

    sfRenderWindow_clear(game->window, game->background);
    menu_event(game);
    if (sfMusic_getStatus(game->music) == sfStopped)
        sfMusic_play(game->music);
    sfText_setString(text, "menu");
    sfText_setPosition(text, (sfVector2f){MT_X, MT_Y});
    sfRenderWindow_drawText(game->window, text, NULL);
    if (menu != NULL) {
        sfText_setString(text, menu);
        sfText_setPosition(text, (sfVector2f){pos, pos});
        sfText_setCharacterSize(text, MT_SIZE);
        sfRenderWindow_drawText(game->window, text, NULL);
        free(menu);
    }
    sfText_setCharacterSize(text, SIZE_TEXT);
    sfRenderWindow_display(game->window);
}
