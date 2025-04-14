/*
** EPITECH PROJECT, 2024
** radar
** File description:
** function to provent leak
*/

#include <stdlib.h>
#include "myworld.h"
#include "textbox.h"
#include "mymath.h"

void destroy_game(game_t *game)
{
    sfMusic_destroy(game->music);
    sfMusic_destroy(game->dig);
    sfMusic_destroy(game->hammer);
    sfClock_destroy(game->clock);
    sfRenderWindow_destroy(game->window);
}

void destroy_textbox(textbox_t *text)
{
    sfFont_destroy(text->font);
    sfText_destroy(text->text);
    for (int i = 0; i < NB_STR; i++)
        free(text->str[i]);
    free(text->str);
    free(text->name);
}

void destroy_infos(infos_map_t *infos)
{
    for (long unsigned int i = 0; i < sizeof(enum texture); i++)
        sfTexture_destroy(infos->convex.texture[i]);
    sfConvexShape_destroy(infos->convex.shape);
    if (infos->heights != NULL)
        free_random_heights(infos->size, infos->heights);
}
