/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** dispatch
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../include/save.h"
#include "../include/buttons.h"
#include "../include/mymath.h"
#include "../include/textbox.h"
#include "../include/myworld.h"

static int handle_errors(game_t *game, infos_map_t *infos_map,
    textbox_t *text)
{
    if (initiate_game(game) == ERROR)
        return ERROR;
    if (initiate_infos_map(infos_map) == ERROR
        || initiate_textbox(text) == ERROR) {
        destroy_game(game);
        return ERROR;
    }
    return SUCCESS;
}

static void check_textbox(textbox_t *textbox)
{
    srand(time(NULL));
    if (textbox->str[X][0] == '\0')
        textbox->str[X][0] = '1';
    if (textbox->str[Y][0] == '\0')
        textbox->str[Y][0] = '1';
    if (textbox->str[SEED][0] == '\0')
        sprintf(textbox->str[SEED], "%d", rand() / 10);
}

void set_value(infos_map_t *infos, textbox_t *textbox, sfBool height)
{
    char *endptr = NULL;

    check_textbox(textbox);
    infos->size.x = (int)strtol(textbox->str[X], &endptr, DECIMAL) + 1;
    infos->size.y = (int)strtol(textbox->str[Y], &endptr, DECIMAL) + 1;
    infos->seed = (int)strtol(textbox->str[SEED], &endptr, DECIMAL);
    if (height == sfTrue)
        infos->heights = random_height(infos->size, infos->seed);
    infos->coef = fmin((float)(WIN_WIDTH - (2 * MARGIN)) / infos->size.x,
                        (float)(WIN_HEIGHT - (2 * MARGIN)) / infos->size.y);
}

void dispatch_function(game_t *game, infos_map_t *infos, textbox_t *textbox,
    button_t **button)
{
    if (game->scene == MENU)
        loop_menu(game, textbox->text);
    if (game->scene == TEXTBOX)
        draw_textbox(game, textbox, infos);
    if (game->scene == DRAW_MAP) {
        draw_map(game, infos, button, textbox);
    }
    if (game->scene == MY_SAVE)
        saves_loop(game, textbox, infos);
}

int my_starter(void)
{
    game_t game = {0};
    infos_map_t infos_map = {0};
    textbox_t textbox = {0};
    button_t **buttons = NULL;

    if (handle_errors(&game, &infos_map, &textbox) == ERROR)
        return ERROR;
    init_buttons(&buttons);
    if (buttons == NULL)
        return ERROR;
    game.buttons = buttons;
    while (sfRenderWindow_isOpen(game.window))
        dispatch_function(&game, &infos_map, &textbox, buttons);
    destroy_game(&game);
    destroy_infos(&infos_map);
    destroy_textbox(&textbox);
    destroy_buttons(buttons);
    return SUCCESS;
}
