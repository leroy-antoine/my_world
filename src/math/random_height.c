/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** random_height
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "myworld.h"
#include "mymath.h"
#include <math.h>

static int my_rand(sfVector2i size)
{
    int random = rand();
    int feat = (size.x + size.y) / 2;

    if (random % feat == 0)
        return MAX_HEIGHT;
    return random % MIN_HEIGHT;
}

static int check_border(sfVector2i size, int **tab, int next_y, int next_x)
{
    if (next_x >= 0 && next_x < size.x
        && next_y >= 0 && next_y < size.y)
        return tab[next_y][next_x];
    return 0;
}

static int next_feat(sfVector2i size, int **tab, int i, int j)
{
    int sum = 0;

    for (int next_y = -1; next_y <= 1; next_y++) {
        for (int next_x = -1; next_x <= 1; next_x++) {
            sum += check_border(size, tab, i + next_y, j + next_x);
        }
    }
    return sum;
}

static void smooth_heights(sfVector2i size, int **tab)
{
    int **temp = malloc(sizeof(int *) * size.y);

    for (int i = 0; i < size.y; i++) {
        temp[i] = malloc(sizeof(int) * size.x);
        for (int j = 0; j < size.x; j++) {
            temp[i][j] = next_feat(size, tab, i, j) / NB_SQUARE;
        }
    }
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            tab[i][j] = temp[i][j];
        }
        free(temp[i]);
    }
    free(temp);
}

int **random_height(sfVector2i size, int seed)
{
    int **tab = malloc(sizeof(int *) * size.y);
    int max_i = (size.x + size.y) / NB_SMOOTH;

    if (tab == NULL)
        return NULL;
    srand(seed);
    for (int i = 0; i < size.y; i++) {
        tab[i] = malloc(sizeof(int) * size.x);
        if (tab[i] == NULL)
            return NULL;
        for (int j = 0; j < size.x; j++) {
            tab[i][j] = my_rand(size);
        }
    }
    if (max_i < MIN_SMOOTH)
        max_i = MIN_SMOOTH;
    for (int i = 0; i < max_i; i++)
        smooth_heights(size, tab);
    return tab;
}

void free_random_heights(sfVector2i size, int **height)
{
    for (int i = 0; i < size.y; i++)
        free(height[i]);
    free(height);
}
