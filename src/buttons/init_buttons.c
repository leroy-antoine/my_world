/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** init_(*buttons)
*/

#include <stdio.h>

#include "buttons.h"
#include "mymath.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

static void create_buttons(button_t **to_create)
{
    sfVector2f position = {0, 0};

    to_create[BUTTON_PLUS] = create_button(&position,
        "PLUS", to_create[BUTTON_PLUS], STAY);
    to_create[BUTTON_MINUS] = create_button(&position,
        "MINUS", to_create[BUTTON_MINUS], STAY);
    to_create[BUTTON_RELOAD] = create_button(&position,
        "RELOAD", to_create[BUTTON_RELOAD], CLICK);
}

button_t **init_buttons(button_t ***buttons)
{
    (*buttons) = malloc(sizeof(button_t *) * NB_BUTTONS + 1);
    if ((*buttons) == NULL)
        return NULL;
    create_buttons((*buttons));
    for (int i = 0; i < NB_BUTTONS; i++)
        if ((*buttons)[i] == NULL)
            return NULL;
    return (*buttons);
}
