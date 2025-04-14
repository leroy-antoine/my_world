/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** initiate
*/

#include "textbox.h"
#include "mymath.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

static int initiate_texture(infos_map_t *infos)
{
    infos->convex.texture[WATER] =
        sfTexture_createFromFile(texture_path[WATER], NULL);
    infos->convex.texture[GRASS] =
        sfTexture_createFromFile(texture_path[GRASS], NULL);
    infos->convex.texture[STONE] =
        sfTexture_createFromFile(texture_path[STONE], NULL);
    infos->convex.texture[SNOW] =
        sfTexture_createFromFile(texture_path[SNOW], NULL);
    for (long unsigned int i = 0; i < sizeof(enum texture); i++) {
        if (infos->convex.texture[i] == NULL)
            return ERROR;
    }
    return SUCCESS;
}

int initiate_infos_map(infos_map_t *infos)
{
    infos->heights = 0;
    infos->size = (sfVector2i){0, 0};
    infos->rad = (sfVector2f){ANGLE * MY_RAD, ANGLE_Y * MY_RAD};
    infos->coef = 0;
    infos->status_tile = NONE;
    infos->seed = 0;
    infos->zoom = 1;
    infos->save = sfFalse;
    infos->posf = (sfVector2f){0, 0};
    infos->convex.shape = sfConvexShape_create();
    if (infos->convex.shape == NULL)
        return ERROR;
    if (initiate_texture(infos) == ERROR)
        return ERROR;
    sfConvexShape_setOutlineColor(infos->convex.shape, sfTransparent);
    sfConvexShape_setOutlineThickness(infos->convex.shape, OUTLINE);
    return SUCCESS;
}

int initiate_game(game_t *game)
{
    game->window = create_window();
    if (game->window == NULL)
        return ERROR;
    game->clock = sfClock_create();
    game->background = sfColor_fromRGBA(COLOR, COLOR, COLOR, 1);
    game->music = sfMusic_createFromFile(music_path[MUSIC]);
    game->dig = sfMusic_createFromFile(music_path[DIG]);
    game->hammer = sfMusic_createFromFile(music_path[HAMMER]);
    if (game->music == NULL || game->dig == NULL
        || game->hammer == NULL) {
        sfRenderWindow_destroy(game->window);
        return ERROR;
    }
    game->start = 0;
    game->max = 0;
    game->scene = MENU;
    game->old_scene = MENU;
    return SUCCESS;
}

static char **get_tabstr(void)
{
    char **tab = malloc(sizeof(char *) * (NB_STR + 1));

    if (tab == NULL)
        return NULL;
    for (int i = 0; i < NB_STR; i++) {
        tab[i] = malloc(sizeof(char) * (MAX_STRLEN + 1));
        if (tab[i] == NULL) {
            free_array(tab);
            return NULL;
        }
        for (int j = 0; j < MAX_STRLEN + 1; j++)
            tab[i][j] = '\0';
    }
    tab[NB_STR] = NULL;
    return tab;
}

int initiate_string(textbox_t *text)
{
    text->name = malloc(sizeof(char) * (MAX_NAME + 1));
    if (text->name == NULL)
        return ERROR;
    for (int i = 0; i < MAX_NAME + 1; i++)
        text->name[i] = '\0';
    text->str = get_tabstr();
    if (text->str == NULL) {
        free(text->name);
        return ERROR;
    }
    return SUCCESS;
}

int initiate_textbox(textbox_t *text)
{
    text->text = sfText_create();
    if (text->text == NULL)
        return ERROR;
    text->font = sfFont_createFromFile(FONT);
    if (text->font == NULL) {
        sfText_destroy(text->text);
        return ERROR;
    }
    if (initiate_string(text) == ERROR) {
        sfText_destroy(text->text);
        sfFont_destroy(text->font);
        return ERROR;
    }
    sfText_setColor(text->text, sfBlack);
    sfText_setCharacterSize(text->text, SIZE_TEXT);
    sfText_setFont(text->text, text->font);
    text->status = -1;
    return SUCCESS;
}
