#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "score.h"
#include "world.h"

score_t cons_empty(){
    return NULL ;
}


 score_t cons(int nombre, score_t suivant){
    score_t score = (score_t)malloc(sizeof(score_t));

    score->nombre = nombre ;
    score->suivant = suivant ;

    return score;
}

int is_empty(score_t score){
    return score == NULL;
}


int nombre(score_t score){
    if(!is_empty(score)){
        int nombre = score->nombre ;
        return nombre ;
    }else{
        exit(EXIT_FAILURE);
    }
}

score_t suivant(score_t score){
    if (!is_empty(score->suivant))
    {
        return score->suivant ;
    }else {
        return NULL;
    }
}

void change_value(int new_score, score_t score){
    if(is_empty(score)){
        score->nombre = new_score ;
    }
}

void change_suivant(score_t score, score_t new_score){
    if(is_empty(score)){
        score->suivant = new_score ;
    }
}

void free_score(score_t score){
    if(is_empty(score)){
        free_score(suivant(score)) ;
    }
    free(score) ;
}

void ajouter_score(int new_score, score_t score){
    score = cons(new_score,suivant(score)) ;
}

void toString(score_t score){
    while(!is_empty(score)){
        printf("nombre : %d \n", score->nombre) ;
        suivant(score) ;
    }
}


