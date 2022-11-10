#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "world.h"
#include "constante.h"

void init_data(world_t * world){
    //on n'est pas à la fin du jeu

	//Initialisation de valeurs 
	init_valeurs(world);

	// Allocation de mémoire
	init_memoire(world);

	//initialisation des sprites
	init_environnement(world) ;

}

void init_memoire(world_t* world){
    world->background = (sprite_t*)malloc(sizeof(sprite_t));
    //world->wall = cree_murs(500);
    changer_monde(world->tab, world->longueur_tab, world->hauteur_tab);
}

void init_valeurs(world_t* world){
	//Initialisation de valeurs 
    world->hauteur_tab=6;
    world->longueur_tab=12;
    world->gameover=0;
}

void init_environnement(world_t* world){
	//initialisation des sprites
	init_sprite(world->background,0,0, SCREEN_HEIGHT, SCREEN_WIDTH);
    int indice_wall=0;
	for(int i=0;i<(world->longueur_tab);i++){
        for(int j = 0;j<(world->hauteur_tab);j++){
            if(world->tab[i][j]==1){
                init_sprite(&(world->wall[indice_wall]),(i*WALL_WIDTH),(j*WALL_HEIGHT),WALL_HEIGHT,WALL_WIDTH);
                indice_wall++;
            }
        }
    }

}

void clean_data(world_t *world){
    free(world->background);
    free_matrice(world->tab,world->longueur_tab,world->hauteur_tab);
    //free_murs(world->wall);
}


void init_sprite(sprite_t *sprite,int x,int y,int h,int l){
    sprite->x=x;
    sprite->y=y;
    sprite->h=h;
    sprite->l=l;
}

void changer_monde(int **tab,int ligne,int colonne){
    if(tab!=NULL){
        free_matrice(tab,colonne,ligne);
    }
    tab = generate_world(colonne,ligne);
    for(int i=0;i<(colonne);i++){//A CHANGER
        for(int j = 0;j<(ligne);j++){
            tab[i][j]=1;
        }
    }
}

int** generate_world(int longueur,int hauteur) {
    int ** T = malloc(longueur*sizeof(int*));
    if(T == NULL)
        exit(EXIT_FAILURE);
    for(int i = 0; i < longueur ; i++)
        T[i] = malloc(hauteur*sizeof(int));
    return T;
}

/*sprite_t * cree_murs(int nb_elements) {
    sprite_t * tab[nb_elements] = malloc(nb_elements*sizeof(sprite_t));
    if(T == NULL)
        exit(EXIT_FAILURE);
    return T;
}*/

int nb_murs(world_t*world){
    int count =0;
    for(int i=0;i<(world->longueur_tab);i++){
        for(int j = 0;j<(world->hauteur_tab);j++){
            if(world->tab[i][j]==1){
                count++;
            }
        }
    }
    return count;
}

void free_matrice(int** T, int taille1, int taille2) {
    for(int i = 0; i < taille1; i++)
        free(T[i]);
    free(T);
    T = NULL;
}

void free_murs(sprite_t* T) {
    free(T);
    T = NULL;
}

void updata_data(world_t *world){

}

int is_game_over(world_t *world){
    return world->gameover;
}


