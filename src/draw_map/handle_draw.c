/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** handle_draw
*/

#include "mymath.h"
#include "myworld.h"
#include <stdlib.h>
#include "textbox.h"
#include "save.h"

static void set_texture(infos_map_t *infos, sfVector2i indice)
{
    float mean = infos->heights[indice.y][indice.x]
        + infos->heights[indice.y + 1][indice.x]
        + infos->heights[indice.y + 1][indice.x + 1]
        + infos->heights[indice.y][indice.x + 1];

    mean /= sizeof(enum texture);
    if (mean > height[SNOW])
        return sfConvexShape_setTexture(
        infos->convex.shape, infos->convex.texture[SNOW], sfFalse);
    if (mean > height[STONE])
        return sfConvexShape_setTexture(
        infos->convex.shape, infos->convex.texture[STONE], sfFalse);
    if (mean > height[GRASS])
        return sfConvexShape_setTexture(
        infos->convex.shape, infos->convex.texture[GRASS], sfFalse);
    return sfConvexShape_setTexture(
    infos->convex.shape, infos->convex.texture[WATER], sfFalse);
}

static void set_point_draw_it(
    game_t *game, infos_map_t *infos, sfVector2i indice, sfVector2f **iso_map)
{
    set_texture(infos, indice);
    sfConvexShape_setPointCount(
        infos->convex.shape, 4);
    sfConvexShape_setPoint(
        infos->convex.shape, 0, iso_map[indice.y][indice.x]);
    sfConvexShape_setPoint(
        infos->convex.shape, 1, iso_map[indice.y + 1][indice.x]);
    sfConvexShape_setPoint(
        infos->convex.shape, 2, iso_map[indice.y + 1][indice.x + 1]);
    sfConvexShape_setPoint(
        infos->convex.shape, 3, iso_map[indice.y][indice.x + 1]);
    sfRenderWindow_drawConvexShape(
        game->window, infos->convex.shape, NULL);
}

static void show_saving(game_t *game, infos_map_t *infos, textbox_t *text)
{
    sfTime micro = sfClock_getElapsedTime(game->clock);

    if (infos->save == sfTrue) {
        infos->save = sfFalse;
        sfClock_restart(game->clock);
    }
    if (micro.microseconds / MIC_SEC < 1) {
        sfText_setString(text->text, SAVING);
        sfText_setPosition(text->text,
            (sfVector2f){WIN_WIDTH - SAVEX, WIN_HEIGHT - SAVEY});
        sfRenderWindow_drawText(game->window, text->text, NULL);
    }
}

void draw_map(
    game_t *game, infos_map_t *infos, button_t **button, textbox_t *text)
{
    sfVector2f **iso_map = create_2d_map(infos);

    map_event(game, infos, iso_map, text);
    sfRenderWindow_clear(game->window, game->background);
    if (sfMusic_getStatus(game->music) == sfStopped)
        sfMusic_play(game->music);
    for (int y = 0; y < infos->size.y - 1; y++) {
        for (int x = 0; x < infos->size.x - 1; x++)
            set_point_draw_it(game, infos, (sfVector2i){x, y}, iso_map);
    }
    show_saving(game, infos, text);
    free_2d_map(infos->size, iso_map);
    draw_button(button, game->window);
    sfRenderWindow_display(game->window);
}
