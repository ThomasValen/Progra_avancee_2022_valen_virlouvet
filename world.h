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
    int gameover ;
    int longueur_tab;
    int hauteur_tab;
    int **tab;
    sprite_t* background;
    sprite_t wall[500];
};
typedef struct world_s world_t;


void init_data(world_t * world);

void init_valeurs(world_t* world);

void init_memoire(world_t* world);

void init_environnement(world_t* world); 

void init_sprite(sprite_t *sprite,int x,int y,int h,int l);

void clean_data(world_t *world);

int** generate_world(int ligne,int colonne);

int nb_murs(world_t*world);

void changer_monde(int **tab,int ligne,int colonne) ;

sprite_t* cree_murs(int nb_elements) ;

void update_data(world_t *world) ;

void free_matrice(int** T, int taille1, int taille2) ;

void free_murs(sprite_t* T);

int is_game_over(world_t *world) ;

#endif