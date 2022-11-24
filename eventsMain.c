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
            if (keystates[SDL_SCANCODE_D]){
                world->player->y = world->ligne[512][MOVING_STEP].y;
                world->player->x = world->ligne[512][MOVING_STEP].x;
            
                world->direction=1;
            }else{
                if (keystates[SDL_SCANCODE_W]){
                    world->player->y = world->ligne[256][MOVING_STEP].y;
                    world->player->x = world->ligne[256][MOVING_STEP].x;

                    world->direction=4;
                }else{
                    if (keystates[SDL_SCANCODE_S]){
                        world->player->y = world->ligne[513][MOVING_STEP].y;
                        world->player->x = world->ligne[513][MOVING_STEP].x;
                        world->direction=3;
                    }else{
                        if (keystates[SDL_SCANCODE_A]){
                            world->player->y = world->ligne[514][MOVING_STEP].y;
                            world->player->x = world->ligne[514][MOVING_STEP].x;
                            world->direction=2;
                        }else{
                            if (keystates[SDL_SCANCODE_E]){
                                world->angle = world->angle + 3 ;
                                if(world->angle >= 360){
                                    world->angle = 0 ;
                                }
                            }else{
                                if (keystates[SDL_SCANCODE_Q]){
                                world->angle = world->angle - 3 ;
                                if(world->angle <= 0){
                                    world->angle = 360 ;
                                }
                            }
                            }
                        }

                    }
                    
                }
                
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