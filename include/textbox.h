/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** textbox
*/

#ifndef TEXTBOX_H_
    #define TEXTBOX_H_

    #include "myworld.h"

    #define NB_STR 3
    #define MAX_STRLEN 9
    #define MAX_NAME 25
    #define SIZE_TEXT 50

    #define T_POSX 400
    #define T_POSY 300
    #define T_OFFSETX 150
    #define T_OFFSETY 150

enum str {
    X,
    Y,
    SEED,
    NAME
};

static const char *def_str[] UNUSED = {
    "X:",
    "Y:",
    "Seed:",
    "Name:"
};

typedef struct textbox {
    int status;
    char **str;
    sfText *text;
    sfFont *font;
    char *name;
} textbox_t;

void map_event(
    game_t *game, infos_map_t *infos_map, sfVector2f **map, textbox_t *text);
void draw_map(
    game_t *game, infos_map_t *infos, button_t **button, textbox_t *text);
void set_value(infos_map_t *infos, textbox_t *textbox, sfBool height);
void free_textbox(textbox_t *text);
void draw_textbox(game_t *game, textbox_t *text, infos_map_t *infos);
void textbox_event(game_t *game, textbox_t *text);
int initiate_string(textbox_t *text);
int initiate_textbox(textbox_t *text);
void destroy_textbox(textbox_t *text);
#endif
