#include "graphismes.h"
#include "world.h"
#include "constante.h"
#include "sdl2-light.h"
#include "eventsMain.h"



void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){ 
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures,world);
}   

void handle_events_player(SDL_Event *event, world_t *world){
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    switch (event-> type)
        {
        case SDL_KEYDOWN:
            if (keystates[SDL_SCANCODE_D]){
                world->player->y = world->ligne[513][MOVING_STEP].y - PLAYER_HEIGHT/2;
                world->player->x = world->ligne[513][MOVING_STEP].x - PLAYER_WIDTH/2;
            
                world->direction=1;
                return; 
            }
            if (keystates[SDL_SCANCODE_W]){

                world->player->y = world->ligne[256][MOVING_STEP].y - PLAYER_HEIGHT/2;
                world->player->x = world->ligne[256][MOVING_STEP].x - PLAYER_WIDTH/2;

                world->direction=4;
                return;
            }
            if (keystates[SDL_SCANCODE_S]){
                world->player->y = world->ligne[514][MOVING_STEP].y - PLAYER_HEIGHT/2;
                world->player->x = world->ligne[514][MOVING_STEP].x - PLAYER_WIDTH/2;
                world->direction=3;
                return ;
            }
            if (keystates[SDL_SCANCODE_A]){
                world->player->y = world->ligne[515][MOVING_STEP].y - PLAYER_HEIGHT/2;
                world->player->x = world->ligne[515][MOVING_STEP].x - PLAYER_WIDTH/2;
                world->direction=2;
                return ;
            }
            if (keystates[SDL_SCANCODE_E]){
                world->angle = world->angle + 3 ;
                if(world->angle >= 360){
                    world->angle = 0 ;
                }
                return ;
            }
            if (keystates[SDL_SCANCODE_Q]){
                world->angle = world->angle - 3 ;
                if(world->angle <= 0){
                    world->angle = 360 ;
                }
                return ;
            }
            if (keystates[SDL_SCANCODE_SPACE]){
                world->attack = 1 ;
            } 
            break;

        case SDL_KEYUP:
            world->direction=0;
            world->attack = 0 ;
            break;
        default:
            break;
        } 
}

void handle_events(SDL_Event *event,world_t *world){
    const Uint8 *keystates;

    
    while( SDL_PollEvent( event) ) {       
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