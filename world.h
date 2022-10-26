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
    sprite_t *background;
    sprite_t *wall[1000];
};
typedef struct world_s world_t;


void init_data(world_t * world);

void init_valeurs(world_t* world);

void init_environnement(world_t* world);

void init_sprite(sprite_t *sprite,int x,int y,int h,int l);

int** generate_world(int ligne,int colonne);

int nb_murs(world_t*world);

#endif