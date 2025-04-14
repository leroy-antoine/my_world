/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** mymath
*/

#ifndef MYMATH_H_
    #define MYMATH_H_

    #include "myworld.h"

    #define M_PI 3.14159265358979323846
    #define MY_RAD M_PI / 180
    #define ANGLE 0
    #define ANGLE_X 45.00
    #define ANGLE_Y 35.00

    #define NB_SQUARE 9

    #define MAX_HEIGHT 1000
    #define MIN_HEIGHT 5

    #define NB_SMOOTH 20
    #define MIN_SMOOTH 3

sfVector2i which_tile(game_t *game, infos_map_t *infos, sfVector2f **map);
void free_2d_map(sfVector2i size, sfVector2f **map);
void free_random_heights(sfVector2i size, int **height);
sfVector2f **create_2d_map(infos_map_t *infos);
int **random_height(sfVector2i size, int seed);
#endif
