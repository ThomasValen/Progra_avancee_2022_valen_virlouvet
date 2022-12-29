#ifndef __SCORE__H__
#define __SCORE__H__

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "constante.h"

struct score_s{
    int nombre;
    //score_s *suivant;
};
typedef struct score_s *score_t;

score_t cons_empty() ;

score_t cons(int nombre, score_t suivant) ;

int is_empty(score_t score) ;

int nombre(score_t score) ;

score_t suivant(score_t score) ;

void change_value(int new_score, score_t score) ;

void change_suivant(score_t score, score_t new_score) ;

void free_score(score_t score) ;

void ajouter_score(int new_score, score_t score) ;


#endif
