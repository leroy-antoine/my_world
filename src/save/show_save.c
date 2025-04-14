/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** show_save
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "save.h"

static int nb_save(DIR *dir)
{
    struct dirent *next;
    int count = 0;

    next = readdir(dir);
    while (next != NULL) {
        if (next->d_name[0] != '.')
            count++;
        next = readdir(dir);
    }
    rewinddir(dir);
    return count;
}

static int pass_file(DIR *dir, struct dirent **next)
{
    if ((*next)->d_name[0] == '.') {
        *next = readdir(dir);
        return 0;
    }
    return 1;
}

static char **get_saves(DIR *dir, int nb_file)
{
    char **tab = malloc(sizeof(char *) * (nb_file + 1));
    struct dirent *next = NULL;
    int i = 0;

    if (tab == NULL)
        return NULL;
    next = readdir(dir);
    while (next != NULL) {
        if (pass_file(dir, &next) == 0)
            continue;
        tab[i] = strdup(next->d_name);
        if (tab[i] == NULL) {
            free_array(tab);
            return NULL;
        }
        next = readdir(dir);
        i++;
    }
    tab[i] = NULL;
    return tab;
}

static char **initiate_save(int *max)
{
    DIR *dir = opendir(SAVE);
    char **tab = NULL;
    int nb_file = 0;

    if (dir == NULL)
        return NULL;
    nb_file = nb_save(dir);
    if (nb_file <= 0)
        return NULL;
    tab = get_saves(dir, nb_file);
    if (tab == NULL)
        return NULL;
    closedir(dir);
    *max = nb_file;
    return tab;
}

static void show_save(game_t *game, sfText *text, char **saves)
{
    char nb[NB_SAVE] = {'\0', ':', '\0'};
    int i = 0;

    while (i < NB_SAVE && saves[i] != NULL) {
        nb[0] = i + 1 + '0';
        sfText_setString(text, nb);
        sfText_setPosition(text, (sfVector2f){S_POSX, S_OFFSETY * i + S_POSY});
        sfRenderWindow_drawText(game->window, text, NULL);
        sfText_setString(text, saves[i + game->start]);
        sfText_setPosition(text, (sfVector2f)
            {S_POSX + S_OFSSETX, S_OFFSETY * i + S_POSY});
        sfRenderWindow_drawText(game->window, text, NULL);
        i++;
    }
}

static void draw_string(game_t *game, sfText *text, char **saves)
{
    if (game->max == 0 || saves == NULL) {
        sfText_setString(text, NO_SAVE);
        sfText_setPosition(text, (sfVector2f)
            {S_POSX + S_OFSSETX, S_OFFSETY + S_POSY});
        sfRenderWindow_drawText(game->window, text, NULL);
    } else {
        show_save(game, text, saves);
    }
}

static void show_fail(game_t *game, sfText *text)
{
    sfTime micro = {0};

    sfClock_restart(game->clock);
    micro = sfClock_getElapsedTime(game->clock);
    while (micro.microseconds / MIC_SEC < 2 && game->scene == MY_SAVE) {
        fail_event(game);
        sfRenderWindow_clear(game->window, game->background);
        sfText_setString(text, ERROR_MSG);
        sfText_setPosition(text, (sfVector2f)
            {WIN_WIDTH / 2 - ERROR_WIDTH, WIN_HEIGHT / 2 - ERROR_HEIGHT});
        sfText_setColor(text, sfRed);
        sfRenderWindow_drawText(game->window, text, NULL);
        sfRenderWindow_display(game->window);
        micro = sfClock_getElapsedTime(game->clock);
    }
    sfText_setColor(text, sfBlack);
}

void saves_loop(game_t *game, textbox_t *text, infos_map_t *infos)
{
    char **saves = NULL;

    if (text == NULL)
        return;
    saves = initiate_save(&game->max);
    if (save_event(game, text, infos, saves) == ERROR)
        show_fail(game, text->text);
    sfRenderWindow_clear(game->window, game->background);
    draw_string(game, text->text, saves);
    sfRenderWindow_display(game->window);
    if (saves != NULL)
        free_array(saves);
}
