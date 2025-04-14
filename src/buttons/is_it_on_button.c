/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** is_it_on_button
*/

#include <stdbool.h>
#include <stdio.h>
#include "buttons.h"
#include "myworld.h"

static void handle_active(int index, infos_map_t *infos,
    button_t *buttons)
{
    if (index == BUTTON_PLUS) {
        if (infos->status_tile == UP)
            buttons->state = PRESSED;
        else
            buttons->state = DEFAULT;
    }
    if (index == BUTTON_MINUS) {
        if (infos->status_tile == DOWN)
            buttons->state = PRESSED;
        else
            buttons->state = DEFAULT;
    }
}

static void set_colors(infos_map_t *infos,
    button_t *buttons, int index)
{
    handle_active(index, infos, buttons);
    if (buttons->state == DEFAULT)
        sfRectangleShape_setFillColor(buttons->shape, sfBlue);
    if (buttons->state == PRESSED)
        sfRectangleShape_setFillColor(buttons->shape, sfRed);
}

void is_it_on_button(button_t **buttons, sfRenderWindow *window,
    void *infos)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    bool is_inside = 0;

    for (int i = 0; i < NB_BUTTONS; i++) {
        is_inside = sfFloatRect_contains(&buttons[i]->bounds,
            mouse_pos.x, mouse_pos.y);
        if (is_inside) {
            func[i].func(infos);
            sfRectangleShape_setFillColor(buttons[i]->shape, sfGreen);
        }
        if (!is_inside)
            set_colors(infos, buttons[i], i);
    }
}
