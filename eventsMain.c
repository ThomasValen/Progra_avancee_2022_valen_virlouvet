#include "graphismes.h"
#include "world.h"
#include "constante.h"
#include "sdl2-light.h"
#include "eventsMain.h"



void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){ 
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}   

void handle_events_player(SDL_Event *event, world_t *world){
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    switch (event-> type)
        {
        case SDL_KEYDOWN:
            if (keystates[SDL_SCANCODE_RIGHT]){
                world->player->x = world->player->x + MOVING_STEP;
                world->direction=1;
            }
            if (keystates[SDL_SCANCODE_UP]){
                world->player->y = world->player->y - MOVING_STEP;
                world->direction=4;
            }
            if (keystates[SDL_SCANCODE_DOWN]){
                world->player->y = world->player->y + MOVING_STEP;
                world->direction=3;
            }
            if (keystates[SDL_SCANCODE_LEFT]){
                world->player->x = world->player->x - MOVING_STEP;
                world->direction=2;
            }
            break;

        case SDL_KEYUP:
            world->direction=0;
            break;
        default:
            break;
        } 
}

void handle_events(SDL_Event *event,world_t *world){
    const Uint8 *keystates;

    
    while( SDL_PollEvent( event ) ) {       
        handle_events_player(event, world) ;
        //Si l'utilisateur a cliqué sur le X de la fenêtre 
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
			if(event->key.keysym.sym == SDLK_ESCAPE){ //si la touche appuyée est 'Echap'
				world->gameover = 1;
            }
         }
    }

}