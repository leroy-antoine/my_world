/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** destroy_buttons
*/

#include <stdlib.h>
#include "buttons.h"
#include "myworld.h"

void destroy_buttons(button_t **button)
{
    for (int i = 0; i < NB_BUTTONS; i++) {
        sfFont_destroy(button[i]->font);
        sfRectangleShape_destroy(button[i]->shape);
        sfText_destroy(button[i]->text);
        free(button[i]);
    }
    free(button);
}
