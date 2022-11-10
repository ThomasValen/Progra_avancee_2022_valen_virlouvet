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
    for(int i=0;i<world->hauteur_tab*world->longueur_tab;i++){
        world->wall[i]= (sprite_t*)malloc(sizeof(sprite_t));
    }
    world->tab = malloc(sizeof(int)*world->hauteur_tab*world->longueur_tab);
}

void init_valeurs(world_t* world){
	//Initialisation de valeurs 
    world->hauteur_tab=6;
    world->longueur_tab=12;
    generate_world(world->tab,world->hauteur_tab,world->longueur_tab);    
}

void init_environnement(world_t* world){
	//initialisation des sprites
	init_sprite(world->background,0,0, SCREEN_HEIGHT, SCREEN_WIDTH);
    int indice_wall=0;
	for(int i=0;i<(world->longueur_tab);i++){
        for(int j = 0;j<(world->hauteur_tab);j++){
            if(world->tab[i][j]==1){
                init_sprite(world->wall[indice_wall],(i*WALL_WIDTH),(j*WALL_HEIGHT),WALL_HEIGHT,WALL_WIDTH);
                indice_wall++;
            }
        }
    }

}

void clean_data(world_t *world){
    free(world->background);
    for(int i=0;i<world->hauteur_tab*world->longueur_tab;i++){
        free(world->wall[i]);
    }
    //bug git
}



void init_sprite(sprite_t *sprite,int x,int y,int h,int l){
    sprite->x=x;
    sprite->y=y;
    sprite->h=h;
    sprite->l=l;
}

void generate_world(int **tab,int ligne,int colonne){
    for(int i=0;i<(colonne);i++){//A CHANGER
        for(int j = 0;j<(ligne);j++){
            tab[i][j]=1;
        }
    }
}

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

int isGameOver(){

}

