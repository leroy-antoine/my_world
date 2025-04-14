/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** draw_button
*/

#include <stdio.h>
#include "buttons.h"
#include "myworld.h"

void draw_button(button_t **button, sfRenderWindow *window)
{
    if (button == NULL)
        return;
    for (int i = 0; i < NB_BUTTONS; i++) {
        sfRenderWindow_drawRectangleShape(window, button[i]->shape, NULL);
        sfRenderWindow_drawText(window, button[i]->text, NULL);
    }
}
