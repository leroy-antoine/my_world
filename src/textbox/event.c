/*
** EPITECH PROJECT, 2024
** radar
** File description:
** event handling
*/

#include "textbox.h"
#include "myworld.h"
#include <string.h>

static void nb_textbox(sfEvent event, char *str, int *status)
{
    int len = strlen(str);

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyBackspace && len > 0)
            str[len - 1] = '\0';
        if (event.key.code >= sfKeyNum0 && event.key.code <= sfKeyNum9
            && len < MAX_STRLEN)
            str[len] = event.key.code + '0' - sfKeyNum0;
        if (event.key.code == sfKeyApostrophe && len < MAX_STRLEN)
            str[len] = '4';
        if (event.key.code == sfKeyHyphen && len < MAX_STRLEN)
            str[len] = '6';
        if (event.key.code == sfKeyEnter)
            (*status)++;
    }
}

static void text_textbox(sfEvent event, char *str, int *status)
{
    int len = strlen(str);

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyBackspace && len > 0)
            str[len - 1] = '\0';
        if (event.key.code >= sfKeyA && event.key.code <= sfKeyZ
            && len < MAX_NAME) {
            str[len] = event.key.code + 'a' - sfKeyA;
            str[len + 1] = '\0';
        }
        if (event.key.code == sfKeyEnter)
            (*status)++;
    }
}

void move_textbox(sfEvent event, textbox_t *text)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp) {
        text->status--;
        if (text->status < -1)
            text->status = -1;
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown) {
        text->status++;
        if (text->status > 2)
            text->status = 2;
    }
}

void textbox_event(game_t *game, textbox_t *text)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(event, game);
        music_setvolume(event, game);
        change_scene(event, game);
        move_textbox(event, text);
        if (text->status < 0)
            text_textbox(event, text->name, &text->status);
        else
            nb_textbox(event, text->str[text->status], &text->status);
    }
}
