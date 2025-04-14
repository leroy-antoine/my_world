/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** create_coor
*/

#include "mymath.h"
#include "myworld.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

static sfVector2f project_iso_point(sfVector2f coor, int z, sfVector2f rad)
{
    sfVector2f coord = {0};
    float cos_x = cos(ANGLE_X * MY_RAD);
    float sin_y = sin(rad.y);

    coord.x = (cos_x * coor.x - cos_x * coor.y);
    coord.y = (sin_y * coor.y + sin_y * coor.x - z);
    return coord;
}

static sfVector2f rotate_point(
    sfVector2f point, sfVector2f center, float angle)
{
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    sfVector2f rotated = {0, 0};

    rotated.x = cos_a * (point.x - center.x)
                - sin_a * (point.y - center.y) + center.x;
    rotated.y = sin_a * (point.x - center.x)
                + cos_a * (point.y - center.y) + center.y;
    return rotated;
}

static sfVector2f **allocate_2d_map(sfVector2i size)
{
    sfVector2f **map = malloc(sizeof(sfVector2f *) * size.y);

    if (map == NULL)
        return NULL;
    for (int y = 0; y < size.y; y++) {
        map[y] = malloc(sizeof(sfVector2f) * size.x);
        if (map[y] == NULL)
            return NULL;
    }
    return map;
}

static sfVector2f get_projection(
    sfVector2i pos, int height, float coef, infos_map_t *infos)
{
    int x = pos.x * coef * infos->zoom;
    int y = pos.y * coef * infos->zoom;

    return project_iso_point(
        (sfVector2f){x, y}, height, infos->rad);
}

static void find_bounds(
    sfVector2f **map, sfVector2f *min, sfVector2f *max, sfVector2i ind)
{
    if (map[ind.y][ind.x].x < min->x)
        min->x = map[ind.y][ind.x].x;
    if (map[ind.y][ind.x].y < min->y)
        min->y = map[ind.y][ind.x].y;
    if (map[ind.y][ind.x].x > max->x)
        max->x = map[ind.y][ind.x].x;
    if (map[ind.y][ind.x].y > max->y)
        max->y = map[ind.y][ind.x].y;
}

static void rotate_map(sfVector2f **map, infos_map_t *infos,
    sfVector2f center, sfVector2f bound[2])
{
    for (int y = 0; y < infos->size.y; y++) {
        for (int x = 0; x < infos->size.x; x++) {
            map[y][x] = rotate_point(map[y][x], center, infos->rad.x);
            find_bounds(map, &bound[0], &bound[1], (sfVector2i){x, y});
        }
    }
}

static void apply_offset(
    sfVector2f **map, infos_map_t *infos, sfVector2f offset)
{
    for (int y = 0; y < infos->size.y; y++) {
        for (int x = 0; x < infos->size.x; x++) {
            map[y][x].x += offset.x + infos->posf.x;
            map[y][x].y += offset.y + infos->posf.y;
        }
    }
}

static void center_map(
    sfVector2f **map, infos_map_t *infos, sfVector2f bound[2])
{
    sfVector2f offset = {0, 0};
    sfVector2f center = {0, 0};

    center = (sfVector2f){(bound[0].x + bound[1].x) / 2,
                            (bound[0].y + bound[1].y) / 2};
    rotate_map(map, infos, center, bound);
    offset = (sfVector2f){WIN_WIDTH / 2 - (bound[0].x + bound[1].x) / 2,
                            WIN_HEIGHT / 2 - (bound[0].y + bound[1].y) / 2};
    apply_offset(map, infos, offset);
}

sfVector2f **create_2d_map(infos_map_t *infos)
{
    sfVector2f **map = allocate_2d_map(infos->size);
    sfVector2f min = {INFINITY, INFINITY};
    sfVector2f max = {0 - INFINITY, 0 - INFINITY};
    sfVector2f bound[2] = {min, max};

    if (map == NULL)
        return NULL;
    for (int y = 0; y < infos->size.y; y++) {
        for (int x = 0; x < infos->size.x; x++) {
            map[y][x] = get_projection(
                (sfVector2i){x, y}, infos->heights[y][x],
                infos->coef, infos);
                find_bounds(map, &bound[0], &bound[1], (sfVector2i){x, y});
        }
    }
    center_map(map, infos, bound);
    return map;
}

void free_2d_map(sfVector2i size, sfVector2f **map)
{
    for (int i = 0; i < size.y; i++) {
        free(map[i]);
    }
    free(map);
}
