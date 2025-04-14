/*
** EPITECH PROJECT, 2025
** buttons
** File description:
** buttons
*/

#ifndef BUTTONS_H_
    #define BUTTONS_H_

    #include <SFML/Graphics.h>

    #define SIZE_X_BUTTON 60.00
    #define SIZE_Y_BUTTON 60.00
    #define SIZE_TEXT_BUTTON 20
    #define NB_BUTTONS 3
    #define BUTTON_PLUS 0
    #define BUTTON_MINUS 1
    #define BUTTON_RELOAD 2
    #define CLICK -1
    #define B_OFFSETX 5
    #define STAY -2

typedef struct button_s {
    sfVector2f position;
    sfRectangleShape *shape;
    sfFont *font;
    sfText *text;
    sfFloatRect bounds;
    int type;
    int state;
} button_t;

void plus_button(void *infos);
void minus_button(void *infos);
void reload_button(void *infos);

typedef struct func_s {
    void(*func)(void *infos);
} func_t;

static const func_t func[] = {
    {&plus_button},
    {&minus_button},
    {&reload_button}};

enum button_state {
    DEFAULT,
    HOVER,
    PRESSED,
    RESET
};

button_t *create_button(sfVector2f *position, char *text, button_t *button,
    int type);
void draw_button(button_t **button, sfRenderWindow *window);
button_t **init_buttons(button_t ***buttons);
void destroy_buttons(button_t **button);
void is_it_on_button(button_t **buttons, sfRenderWindow *window,
    void *infos);

#endif
