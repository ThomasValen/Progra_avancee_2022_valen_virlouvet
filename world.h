#ifndef __WORLD__H__
#define __WORLD__H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "score.h"

struct sprite_s{
    float x;
    float y;
    int h;
    int l;
    int no_key;
    int placement_x;
    int placement_y;
    int is_looking_for;
    bool findPlayer ;
    bool ishitting;
};
typedef struct sprite_s sprite_t;

struct world_s{
    bool stop ;
    int gameover ;
    int direction;//1 = droite  2 = gauche  3 = bas 4 = haut
    int longueur_tab;
    int hauteur_tab;
    int nb_point_ligne[516] ;
    int **tab;
    int nb_mur ;
    int three_d_check ;
    float angle ;
    float mid_angle ;
    int nb_key ;
    int nb_enemy ;
    int nb_pv ;
    int attack ;
    int nb_key_recup ;
    int etat_menu ;
    float compteur_debut;//animation epee
    float compteur_debut2;//quand le joueur est touché
    float compteur_fin;
    int is_attacking;
    bool hideMap ;
    bool readScore ;
    int compteur_score ;

    int nb_bandes_sortie;
    int no_ligne_db_sortie;
    int top[5] ;
    score_t score ;
    sprite_t* background;
    sprite_t* compteur_key ;
    sprite_t*  wall;
    sprite_t* player ;
    sprite_t **ligne;
    sprite_t *view_player ;
    sprite_t *key ;//tableau
    sprite_t *enemy ;//tableau
    sprite_t *exit ;
    sprite_t *menu ;
    sprite_t *titre;
    sprite_t *play;
    sprite_t *button_exit ;
    sprite_t* epee ;
    sprite_t* pv ;
    sprite_t* you_died ;
};
typedef struct world_s world_t;


void init_data(world_t * world);

void init_valeurs(world_t* world);

void init_memoire(world_t* world);

void init_environnement(world_t* world); 

void init_sprite(sprite_t *sprite,float x,float y,int h,int l,int no_key);

sprite_t** creer_ligne(int ligne, int colonne) ;

sprite_t* creer_tableau(int nb_elements) ;

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

void setIsLooking(world_t* world,int numero_clef,int valeur);

void setIsLooking2(world_t* world,int numero_enemy,int valeur) ;


void ligne(world_t* world,float player_a, int numero_ligne) ;

void top5(score_t score, world_t* world) ;

void scorefin(world_t* world) ;


#endif