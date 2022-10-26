#ifndef __EVENTSMAIN__H__
#define __EVENTSMAIN__H__
#include "world.h"
#include "graphisme.h"
#include "sdl2-light.h"
#include "sdl2-ttf-light.h"


/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world);


/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world); 


#endif
