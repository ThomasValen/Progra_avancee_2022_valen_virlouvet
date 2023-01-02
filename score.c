#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "score.h"
#include "world.h"

//creer une liste vide
score_t cons_empty(){
    return NULL ;
}

//ajoute une valeur dans la liste
score_t cons(int nombre, score_t suivant){
    score_t score = (score_t)malloc(sizeof(score_t));

    score->nombre = nombre ;
    score->suivant = suivant ;

    return score;
}

//regarde si la liste est vide
int is_empty(score_t score){
    return score == NULL;
}

//retourne la valeur dans la liste
int nombre(score_t score){
    if(!is_empty(score)){
        int nombre = score->nombre ;
        return nombre ;
    }else{
        exit(EXIT_FAILURE);
    }
}

//retourne la liste suivante
score_t suivant(score_t score){
    if (!is_empty(score->suivant))
    {
        return score->suivant ;
    }else {
        return NULL;
    }
}

//change la valeur actuelle
void change_value(int new_score, score_t score){
    if(is_empty(score)){
        score->nombre = new_score ;
    }
}

//change la liste suivante
void change_suivant(score_t score, score_t new_score){
    if(is_empty(score)){
        score->suivant = new_score ;
    }
}

//libere la liste
void free_score(score_t score){
    if(is_empty(score)){
        free_score(suivant(score)) ;
    }
    free(score) ;
}

//ajoute le score a la liste
score_t ajouter_score(int new_score, score_t score){
    score = cons(new_score,score) ;
    return score ;
}


//affiche la liste
void toString(score_t score){
    if(!is_empty(score)){
        while(!is_empty(score)){
            printf("nombre : %d \n", score->nombre) ;
            score = suivant(score) ;
        }
    }else{
        printf("je suis vide") ;
    }    
}


