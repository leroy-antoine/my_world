/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** reload_button
*/


#include "myworld.h"
#include "buttons.h"
#include "mymath.h"

void reload_button(void *infos)
{
    infos_map_t *data = (infos_map_t *) infos;

    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        data->heights = random_height(data->size, data->seed);
    }
}
