#ifndef __WORLD__H__
#define __WORLD__H__

struct sprite_s{
    int x;
    int y;
    int h;
    int l;
};
typedef struct sprite_s sprite_t;

struct world_s{
    int longueur_tab;
    int hauteur_tab;
    int **tab;
    sprite_t background;
    sprite_t wall[1000];
};
typedef struct world_s world_t;

#endif