/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** text_box
*/

#include "textbox.h"
#include "lib.h"
#include <stdlib.h>

void free_textbox(textbox_t *text)
{
    sfText_destroy(text->text);
    sfFont_destroy(text->font);
    free_array(text->str);
    free(text->name);
}

static void draw_name(game_t *game, textbox_t *text)
{
    if (text->status == -1)
        sfText_setFillColor(text->text, sfBlue);
    else
        sfText_setFillColor(text->text, sfBlack);
    sfText_setString(text->text, def_str[NAME]);
    sfText_setPosition(text->text, (sfVector2f){T_POSX, T_OFFSETY});
    sfRenderWindow_drawText(game->window, text->text, NULL);
    sfText_setString(text->text, text->name);
    sfText_setPosition(text->text,
        (sfVector2f){T_POSX + T_OFFSETX, T_OFFSETY});
    sfRenderWindow_drawText(game->window, text->text, NULL);
}

static void draw_string(game_t *game, textbox_t *text)
{
    draw_name(game, text);
    for (int i = 0; i < NB_STR; i++) {
        if (text->status == i)
            sfText_setFillColor(text->text, sfBlue);
        else
            sfText_setFillColor(text->text, sfBlack);
        sfText_setString(text->text, def_str[i]);
        sfText_setPosition(text->text, (sfVector2f)
            {T_POSX, T_OFFSETX * i + T_POSY});
        sfRenderWindow_drawText(game->window, text->text, NULL);
        sfText_setString(text->text, text->str[i]);
        sfText_setPosition(text->text, (sfVector2f)
            {T_POSX + T_OFFSETX, T_OFFSETX * i + T_POSY});
        sfRenderWindow_drawText(game->window, text->text, NULL);
    }
}

void draw_textbox(game_t *game, textbox_t *text, infos_map_t *infos)
{
    textbox_event(game, text);
    if (text->status >= NB_STR) {
        text->status = -1;
        game->scene = DRAW_MAP;
        game->old_scene = TEXTBOX;
        set_value(infos, text, sfTrue);
        sfText_setFillColor(text->text, sfBlack);
        return;
    }
    if (sfMusic_getStatus(game->music) == sfStopped)
        sfMusic_play(game->music);
    sfRenderWindow_clear(game->window, game->background);
    draw_string(game, text);
    sfRenderWindow_display(game->window);
}
