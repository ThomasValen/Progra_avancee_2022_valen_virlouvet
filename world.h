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
    int three_d_check;
    int gameover ;
    int direction;//1 = droite  2 = gauche  3 = bas 4 = haut
    int longueur_tab;
    int hauteur_tab;
    int nb_point_ligne[515] ;
    int **tab;
    int nb_mur ;
    float angle ;
    sprite_t* background;
    sprite_t wall[100];
    sprite_t* player ;
    sprite_t **ligne;
    sprite_t *view_player ;
};
typedef struct world_s world_t;


void init_data(world_t * world);

void init_valeurs(world_t* world);

void init_memoire(world_t* world);

void init_environnement(world_t* world); 

void init_sprite(sprite_t *sprite,int x,int y,int h,int l);

sprite_t** creer_ligne(int ligne, int colonne) ;

void clean_data(world_t *world);

int** changer_monde(world_t *world,int ligne,int colonne);

sprite_t * cree_murs(int nb_elements);

void free_matrice(int** T, int taille1, int taille2);

void free_murs(sprite_t* T);

int sethauteur();

int setlongueur();

int nb_murs(int **tab,int hauteur_tab,int longueur_tab);

void update_data(world_t *world) ;

int is_game_over(world_t *world);

int PointIsInWalls(int x,int y,world_t*world) ;

int PointIsInWall(int x,int y,sprite_t wall) ;

int sprites_collide_ligne(sprite_t sp1, sprite_t sp2);


void ligne(world_t* world,float player_a, int numero_ligne) ;


#endif