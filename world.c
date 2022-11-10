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
    world->tab = changer_monde(world->hauteur_tab,world->longueur_tab );
}

void init_valeurs(world_t* world){
	//Initialisation de valeurs 
    world->hauteur_tab=sethauteur();
    world->longueur_tab=setlongueur();
    world->gameover=0;
}

void init_environnement(world_t* world){
	//initialisation des sprites
	init_sprite(world->background,0,0, SCREEN_HEIGHT, SCREEN_WIDTH);
    int indice_wall=0;
	for(int i=0;i<(world->hauteur_tab);i++){
        for(int j = 0;j<(world->longueur_tab);j++){
            if(world->tab[i][j]==1){
                init_sprite(&(world->wall[indice_wall]),(j*WALL_WIDTH),(i*WALL_HEIGHT),WALL_HEIGHT,WALL_WIDTH);
                indice_wall++;
            }
        }
    }
}

void clean_data(world_t *world){
    free(world->background);
    //free_matrice(world->tab,world->longueur_tab,world->hauteur_tab);
    //free_murs(world->wall);
}


void init_sprite(sprite_t *sprite,int x,int y,int h,int l){
    sprite->x=x;
    sprite->y=y;
    sprite->h=h;
    sprite->l=l;
}

int sethauteur(){
    FILE* fichier=NULL;
    char chara;
    int lignes=0;
    int count=0;
    fichier =fopen("map.txt","r");
    if (fichier != NULL){
        do{
            count++;
            chara = fgetc(fichier);
            if(chara=='\n'){
                lignes++;
            }
        } while (chara!=EOF);
        fclose(fichier);
    }
    return lignes;
}

int setlongueur(){
    FILE* fichier=NULL;
    char chara;
    int max=0;
    int colonnes=0;
    fichier =fopen("map.txt","r");
    if (fichier != NULL){        
        do{
            chara = fgetc(fichier);
            if(chara=='\n'){
                colonnes=0;
            }else{
                colonnes++;
            }
            if(max<colonnes){
                max=colonnes;
            }
        } while (chara!=EOF);
        fclose(fichier);
    }
    return max;
}

int** changer_monde(int ligne,int colonne){
    int ** T = malloc(ligne*sizeof(int*));
    if(T == NULL)
        exit(EXIT_FAILURE);
    for(int i = 0; i < ligne ; i++)
        T[i] = malloc(colonne*sizeof(int));

    FILE* fichier=NULL;
    char chara;
    int lignes = 0;
    int colonnes = 0;
    fichier =fopen("map.txt","r");

 
    if (fichier != NULL){
        do{
            chara = fgetc(fichier);
            if(chara!=EOF){
                if(chara == '#'){
                    T[lignes][colonnes]=1;
                }else{
                    T[lignes][colonnes]=0;
                }
                if(chara=='\n'){
                    lignes++;
                    colonnes=0;
                }else{
                    colonnes++;
                }
            }
            
        } while (chara!=EOF);
        fclose(fichier);
    }
    return T;
}

int nb_murs(int **tab,int hauteur_tab,int longueur_tab){
    int count =0;
    for(int i=0;i<(longueur_tab);i++){
        for(int j = 0;j<(hauteur_tab);j++){
            if(tab[j][i]==1){
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


