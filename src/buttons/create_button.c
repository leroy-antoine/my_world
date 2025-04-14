/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** create_button
*/

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include "myworld.h"
#include "buttons.h"

static sfRectangleShape *button_set_position(sfVector2f position)
{
    sfVector2f size = {0};
    sfRectangleShape *shape = sfRectangleShape_create();

    size.x = SIZE_X_BUTTON;
    size.y = SIZE_Y_BUTTON;
    if (shape == NULL)
        return NULL;
    sfRectangleShape_setPosition(shape, position);
    sfRectangleShape_setSize(shape, size);
    sfRectangleShape_setOutlineThickness(shape, 1);
    sfRectangleShape_setOutlineColor(shape, sfBlack);
    sfRectangleShape_setFillColor(shape, sfBlue);
    return shape;
}

static sfVector2f calculate_middle(sfFloatRect rect, sfFloatRect text,
    sfVector2f pos)
{
    sfVector2f position = {0};

    position.y = pos.y + (rect.height / 2 - text.height);
    position.x = pos.x + (rect.width - text.width) / 2;
    return position;
}

static sfText *button_set_text(char *str, sfFont *font, button_t *button)
{
    sfText *text = sfText_create();
    sfFloatRect size_text = {0};

    if (text == NULL || font == NULL)
        return NULL;
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, SIZE_TEXT_BUTTON);
    size_text = sfText_getGlobalBounds(text);
    sfText_setPosition(text,
        calculate_middle(button->bounds, size_text, button->position));
    return text;
}

static button_t *init_button(sfVector2f position, char *text,
    int type)
{
    button_t *button = malloc(sizeof(button_t));

    if (button == NULL)
        return NULL;
    button->position = position;
    button->shape = button_set_position(button->position);
    if (button->shape == NULL)
        return NULL;
    button->bounds = sfRectangleShape_getGlobalBounds(button->shape);
    button->font = sfFont_createFromFile(FONT);
    if (button->font == NULL)
        return NULL;
    button->text = button_set_text(text, button->font, button);
    button->type = type;
    button->state = DEFAULT;
    return button;
}

button_t *create_button(sfVector2f *position, char *text, button_t *button,
    int type)
{
    button = malloc(sizeof(button_t));
    if (text == NULL || button == NULL)
        return NULL;
    button = init_button(*position, text, type);
    if (button == NULL)
        return NULL;
    position->x += (float)SIZE_X_BUTTON + B_OFFSETX;
    return button;
}
