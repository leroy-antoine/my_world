/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** save
*/

#ifndef SAVE_H_
    #define SAVE_H_

    #include "textbox.h"

    #define SAVE "save/"
    #define EXT ".legend"

    #define MIC_SEC 1000000

    #define ERROR_WIDTH 250
    #define ERROR_HEIGHT 100
    #define ERROR_MSG "Can't load the save !!!\n\tTry again!!"

    #define NO_SAVE "NO SAVE"

    #define NB_SAVE 3

    #define S_POSX 500
    #define S_POSY 300
    #define S_OFSSETX 50
    #define S_OFFSETY 150

void fail_event(game_t *game);
int get_save(char *file, infos_map_t *info, textbox_t *text);
int save_event(game_t *game, textbox_t *text, infos_map_t *infos, char **str);
void saves_loop(game_t *game, textbox_t *text, infos_map_t *infos);
void my_save(infos_map_t *info, textbox_t *text);
#endif
