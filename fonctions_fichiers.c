#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "fonctions_fichiers.h"

char** allouer_tab_2D(int n, int m){
    char ** tab = malloc(n*sizeof(char*)); 
    for(int i=0;i<n;i++){
        tab[i]=malloc(m*sizeof(char));
    }

    for(int li=0;li<n;li++){
        for(int co=0;co<m;co++){
            tab[li][co]=' ';
        }
    }

    return tab;

}

void desallouer_tab_2D(char** tab, int n){
    for(int i=0;i<n;i++){
        free(tab[i]);
    }
    free(tab);
}

void afficher_tab_2D(char** tab, int n, int m){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%c ",tab[i][j]);
        }
        printf("\n");
    }
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){

}

