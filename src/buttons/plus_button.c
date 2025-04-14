/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** plus_button
*/

#include <stdio.h>

#include "../../include/myworld.h"
#include "../../include/buttons.h"

void plus_button(void *data)
{
    infos_map_t *infos = (infos_map_t *)data;

    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (infos->status_tile == UP) {
            infos->status_tile = NONE;
        } else {
            infos->status_tile = UP;
        }
    }
}
