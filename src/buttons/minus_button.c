/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** minus_button
*/

#include <stdio.h>

#include "myworld.h"
#include "buttons.h"

void minus_button(void *data)
{
    infos_map_t *infos = (infos_map_t *)data;

    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (infos->status_tile == DOWN) {
            infos->status_tile = NONE;
        } else {
            infos->status_tile = DOWN;
        }
    }
}
