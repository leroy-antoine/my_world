/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** myworld
*/

#ifndef MYWORLD_H_
    #define MYWORLD_H_

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include "buttons.h"

    #define USAGE "include/usage.txt"
    #define MY_MENU "src/menu/menu.txt"

    #define UNUSED __attribute__((unused))

    #define WIN_HEIGHT 1080
    #define WIN_WIDTH 1920
    #define WIN_BITS 64
    #define WIN_FRAME 60
    #define OUTLINE 0.5
    #define WIN_NAME "my_world"

    #define MARGIN 150

    #define ERROR 84
    #define SUCCESS 0

    #define VOL_MAX 100.0
    #define VOL_MIN 0.0
    #define VOL_GAP 5.0

    #define MAX_STR 9

    #define DECIMAL 10
    #define FONT "images_and_sounds/FREEDOM.ttf"

    #define SAVING "saving ..."
    #define SAVEX 250
    #define SAVEY 150

    #define COLOR 200

    #define MT_SIZE 25
    #define MT_X 900
    #define MT_Y 100

    #define MAX_ZOOM 3.0
    #define MIN_ZOOM 0.2
    #define ZOOM 0.1

    #define MOVE 5

static const float height[] UNUSED = {0.0, 0.0, 10.0, 20.0};

enum texture {
    WATER,
    GRASS,
    STONE,
    SNOW
};

static const char *texture_path[] UNUSED = {
    "PNG/water.jpg",
    "PNG/grass.jpg",
    "PNG/stone.jpg",
    "PNG/snow.jpg",
};

enum music {
    MUSIC,
    DIG,
    HAMMER,
};

static const char *music_path[] UNUSED = {
    "images_and_sounds/Meadow.ogg",
    "images_and_sounds/dig.ogg",
    "images_and_sounds/hammer.ogg",
};

typedef struct game {
    button_t **buttons;
    sfRenderWindow *window;
    sfClock *clock;
    sfMusic *music;
    sfMusic *dig;
    sfMusic *hammer;
    sfColor background;
    int scene;
    int old_scene;
    int start;
    int max;
} game_t;

typedef struct convex_s {
    sfTexture *texture[4];
    sfConvexShape *shape;
} convex_t;

enum scene {
    TEXTBOX,
    DRAW_MAP,
    MY_SAVE,
    MENU
};

enum tile {
    NONE,
    UP,
    DOWN
};

typedef struct infos_map_s {
    int **heights;
    int seed;
    sfVector2i size;
    sfVector2f rad;
    convex_t convex;
    float coef;
    float zoom;
    int status_tile;
    sfVector2f posf;
    sfBool save;
} infos_map_t;

int initiate_infos_map(infos_map_t *infos);
int initiate_game(game_t *game);
int my_starter(void);
void music_setvolume(sfEvent event, game_t *game);
void close_window(sfEvent event, game_t *game);
void destroy_game(game_t *game);
sfRenderWindow *create_window(void);
void destroy_infos(infos_map_t *infos);
void menu_event(game_t *game);
void loop_menu(game_t *game, sfText *text);
void change_scene(sfEvent event, game_t *game);
#endif
