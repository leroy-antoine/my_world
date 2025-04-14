/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** event
*/

#include "myworld.h"
#include "mymath.h"
#include "buttons.h"
#include "save.h"

static void modify_height(infos_map_t *infos, sfVector2i tile, int coef)
{
    infos->heights[tile.y][tile.x] += coef;
    infos->heights[tile.y + 1][tile.x] += coef;
    infos->heights[tile.y + 1][tile.x + 1] += coef;
    infos->heights[tile.y][tile.x + 1] += coef;
}

static void mouse_click(
    sfEvent event, game_t *game, infos_map_t *infos, sfVector2f **map)
{
    sfVector2i tile = {0, 0};

    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft &&
        infos->status_tile != NONE) {
        tile = which_tile(game, infos, map);
        if (infos->status_tile == UP && tile.x != -1 && tile.y != 1) {
            modify_height(infos, tile, 1);
            sfMusic_play(game->hammer);
        }
        if (infos->status_tile == DOWN && tile.x != -1 && tile.y != 1) {
            modify_height(infos, tile, -1);
            sfMusic_play(game->dig);
        }
    }
}

static void map_effect(sfEvent event, infos_map_t *infos)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyNum1) {
        if (infos->status_tile != UP)
            infos->status_tile = UP;
        else
            infos->status_tile = NONE;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyNum2) {
        if (infos->status_tile != DOWN)
            infos->status_tile = DOWN;
        else
            infos->status_tile = NONE;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyR) {
        free_random_heights(infos->size, infos->heights);
        infos->heights = random_height(infos->size, infos->seed);
    }
}

static void set_orientation(sfEvent event, infos_map_t *infos_map)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyLeft) {
        infos_map->rad.x -= MY_RAD;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyRight) {
        infos_map->rad.x += MY_RAD;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp) {
        infos_map->rad.y -= MY_RAD;
        if (infos_map->rad.y < -1.0)
            infos_map->rad.y = -1;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown) {
        infos_map->rad.y += MY_RAD;
        if (infos_map->rad.y > 1.0)
            infos_map->rad.y = 1;
    }
}

static void set_zoom(sfEvent event, infos_map_t *infos_map)
{
    float zoom = 0;

    if (event.type == sfEvtMouseWheelScrolled) {
        zoom = event.mouseWheelScroll.delta;
        if (zoom > 0)
            zoom = ZOOM * -1;
        else
            zoom = ZOOM;
        infos_map->zoom += zoom;
        if (infos_map->zoom > MAX_ZOOM)
            infos_map->zoom = MAX_ZOOM;
        if (infos_map->zoom < MIN_ZOOM)
            infos_map->zoom = MIN_ZOOM;
    }
}

static void move_map(sfEvent event, infos_map_t *infos_map)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyZ) {
        infos_map->posf.y -= MOVE;
        if (infos_map->posf.y < -1 * (WIN_HEIGHT / 2))
            infos_map->posf.y = -1 * (WIN_HEIGHT / 2);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS) {
        infos_map->posf.y += MOVE;
        if (infos_map->posf.y > WIN_HEIGHT / 2)
            infos_map->posf.y = WIN_HEIGHT / 2;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyQ) {
        infos_map->posf.x -= MOVE;
        if (infos_map->posf.x < -1 * (WIN_WIDTH / 2))
            infos_map->posf.x = -1 * (WIN_WIDTH / 2);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyD) {
        infos_map->posf.x += MOVE;
        if (infos_map->posf.x > WIN_WIDTH / 2)
            infos_map->posf.x = WIN_WIDTH / 2;
    }
}

static void reset_map(sfEvent event, infos_map_t *infos_map)
{
    static sfBool outline = sfFalse;

    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyA) {
        infos_map->posf = (sfVector2f){0, 0};
        infos_map->rad = (sfVector2f){ANGLE * MY_RAD, ANGLE_Y * MY_RAD};
        infos_map->zoom = 1;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyO) {
        if (outline == sfFalse) {
            sfConvexShape_setOutlineColor(infos_map->convex.shape, sfBlack);
            outline = sfTrue;
        } else {
            sfConvexShape_setOutlineColor(
                infos_map->convex.shape, sfTransparent);
            outline = sfFalse;
        }
    }
}

static void event_action(
    sfEvent event, infos_map_t *infos_map, textbox_t *text)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF5) {
        my_save(infos_map, text);
        infos_map->save = sfTrue;
    }
}

void map_event(
    game_t *game, infos_map_t *infos_map, sfVector2f **map, textbox_t *text)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(event, game);
        is_it_on_button(game->buttons, game->window, infos_map);
        music_setvolume(event, game);
        set_orientation(event, infos_map);
        map_effect(event, infos_map);
        mouse_click(event, game, infos_map, map);
        set_zoom(event, infos_map);
        move_map(event, infos_map);
        reset_map(event, infos_map);
        event_action(event, infos_map, text);
        change_scene(event, game);
    }
}
