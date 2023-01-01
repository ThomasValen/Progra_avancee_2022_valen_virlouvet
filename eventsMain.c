#include "graphismes.h"
#include "score.h"
#include "sdl2-ttf-light.h"
#include "world.h"
#include "constante.h"
#include "sdl2-light.h"
#include "eventsMain.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_scancode.h>



void handle_events_menu(SDL_Event *event, world_t *world){
     const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        SDL_Rect box ;
        switch (event->type)
        {
        case SDL_KEYDOWN:
            //SDL_Log("+key");
            /*if(event->motion.y > 0 && event->motion.x > 0 && event->motion.y < 100 && event->motion.x < 100){
                world->etat_menu = 0 ;
            }else {
                world->etat_menu = 1 ;
            }*/

            if (keystates[SDL_SCANCODE_S] && world->etat_menu == 0){
                //SDL_Log("Keycode fleche bas"); // Affiche un message
                world->etat_menu++;
            }else{
                if (keystates[SDL_SCANCODE_S] && world->etat_menu == 1){
                    //SDL_Log("Keycode fleche bas"); // Affiche un message
                    world->etat_menu--;
                }else{
                    if (keystates[SDL_SCANCODE_W] && world->etat_menu == 0){
                        //SDL_Log("Keycode fleche haut"); // Affiche un message
                        world->etat_menu++;
                    }else{
                        if (keystates[SDL_SCANCODE_W] && world->etat_menu == 1){
                            //SDL_Log("Keycode fleche haut"); // Affiche un message
                            world->etat_menu--;
                        }
                    }
                }
            }
            if(keystates[SDL_SCANCODE_RETURN] && world->etat_menu == 0){
                world->etat_menu = 3;
            }
            if(keystates[SDL_SCANCODE_RETURN] && world->etat_menu == 1){
                world->gameover = 1; 
            }
            if (keystates[SDL_SCANCODE_ESCAPE]) {
                world->gameover = 1 ;
            }
            if(keystates[SDL_QUIT]){
                world->gameover = 1 ;
            }
        break;
    }
}

void handle_events_player(SDL_Event *event, world_t *world){
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    switch (event-> type)
        {
        case SDL_KEYDOWN:
            
            if(!world->stop){
                if (keystates[SDL_SCANCODE_D]){
                    world->player->y = world->ligne[513][MOVING_STEP].y - PLAYER_HEIGHT/2;
                    world->player->x = world->ligne[513][MOVING_STEP].x - PLAYER_WIDTH/2;
                
                    world->direction=1;
                    if (keystates[SDL_SCANCODE_SPACE]){
                        if(world->is_attacking==0){
                            world->is_attacking=1;
                            world->compteur_debut = (float)(SDL_GetTicks()/1000.);
                        }
                    }
                    if(keystates[SDL_SCANCODE_M]){
                        world->hideMap = !world->hideMap ;
                        world->stop = !world->stop ;
                    } 
                    if (keystates[SDL_SCANCODE_E]){
                        world->angle = world->angle + 3 ;
                        if(world->angle >= 360){
                            world->angle = 0 ;
                        }
                    }
                    if (keystates[SDL_SCANCODE_Q]){
                        world->angle = world->angle - 3 ;
                        if(world->angle <= 0){
                            world->angle = 360 ;
                        } 
                    }      
                    return; 
                }
                if (keystates[SDL_SCANCODE_W]){

                    world->player->y = world->ligne[256][MOVING_STEP].y - PLAYER_HEIGHT/2;
                    world->player->x = world->ligne[256][MOVING_STEP].x - PLAYER_WIDTH/2;

                    world->direction=4;
                    if (keystates[SDL_SCANCODE_SPACE]){
                        if(world->is_attacking==0){
                            world->is_attacking=1;
                            world->compteur_debut = (float)(SDL_GetTicks()/1000.);
                        }
                    }
                    if(keystates[SDL_SCANCODE_M]){
                        world->hideMap = !world->hideMap ;
                        world->stop = !world->stop ;
                    } 
                    if (keystates[SDL_SCANCODE_E]){
                        world->angle = world->angle + 3 ;
                        if(world->angle >= 360){
                            world->angle = 0 ;
                        }
                    } 
                    if (keystates[SDL_SCANCODE_Q]){
                        world->angle = world->angle - 3 ;
                        if(world->angle <= 0){
                            world->angle = 360 ;
                        } 
                    }  
                    return;
                }
                if (keystates[SDL_SCANCODE_S]){
                    world->player->y = world->ligne[514][MOVING_STEP].y - PLAYER_HEIGHT/2;
                    world->player->x = world->ligne[514][MOVING_STEP].x - PLAYER_WIDTH/2;
                    world->direction=3;
                    if (keystates[SDL_SCANCODE_SPACE]){
                        if(world->is_attacking==0){
                            world->is_attacking=1;
                            world->compteur_debut = (float)(SDL_GetTicks()/1000.);
                        }
                    }
                    if(keystates[SDL_SCANCODE_M]){
                        world->hideMap = !world->hideMap ;
                        world->stop = !world->stop ;
                    } 
                    if (keystates[SDL_SCANCODE_E]){
                        world->angle = world->angle + 3 ;
                        if(world->angle >= 360){
                            world->angle = 0 ;
                        }
                    }
                    if (keystates[SDL_SCANCODE_Q]){
                        world->angle = world->angle - 3 ;
                        if(world->angle <= 0){
                            world->angle = 360 ;
                        } 
                    }   
                    
                    return ;
                }
                if (keystates[SDL_SCANCODE_A]){
                    world->player->y = world->ligne[515][MOVING_STEP].y - PLAYER_HEIGHT/2;
                    world->player->x = world->ligne[515][MOVING_STEP].x - PLAYER_WIDTH/2;
                    world->direction=2;
                    if (keystates[SDL_SCANCODE_SPACE]){
                        if(world->is_attacking==0){
                            world->is_attacking=1;
                            world->compteur_debut = (float)(SDL_GetTicks()/1000.);
                        }
                    }
                    if(keystates[SDL_SCANCODE_M]){
                        world->hideMap = !world->hideMap ;
                        world->stop = !world->stop ;
                    } 
                    if (keystates[SDL_SCANCODE_E]){
                        world->angle = world->angle + 3 ;
                        if(world->angle >= 360){
                            world->angle = 0 ;
                        }
                    }
                    if (keystates[SDL_SCANCODE_Q]){
                        world->angle = world->angle - 3 ;
                        if(world->angle <= 0){
                            world->angle = 360 ;
                        } 
                    } 
                    if (keystates[SDL_SCANCODE_W]){

                        world->player->y = world->ligne[256][MOVING_STEP].y - PLAYER_HEIGHT/2;
                        world->player->x = world->ligne[256][MOVING_STEP].x - PLAYER_WIDTH/2;   
                    }    
                    return ;
                }
                if (keystates[SDL_SCANCODE_E]){
                    world->angle = world->angle + 3 ;
                    if(world->angle >= 360){
                        world->angle = 0 ;
                    }
                    if (keystates[SDL_SCANCODE_SPACE]){
                        if(world->is_attacking==0){
                            world->is_attacking=1;
                            world->compteur_debut = (float)(SDL_GetTicks()/1000.);
                        }
                    }
                    if (keystates[SDL_SCANCODE_W]){

                        world->player->y = world->ligne[256][MOVING_STEP].y - PLAYER_HEIGHT/2;
                        world->player->x = world->ligne[256][MOVING_STEP].x - PLAYER_WIDTH/2;   
                    }
                    return ;
                }
                if (keystates[SDL_SCANCODE_Q]){
                    world->angle = world->angle - 3 ;
                    if(world->angle <= 0){
                        world->angle = 360 ;
                    }
                    if (keystates[SDL_SCANCODE_SPACE]){
                        if(world->is_attacking==0){
                            world->is_attacking=1;
                            world->compteur_debut = (float)(SDL_GetTicks()/1000.);
                        }
                    }
                    return ;
                }
                if (keystates[SDL_SCANCODE_SPACE]){
                    if(world->is_attacking==0){
                        world->is_attacking=1;
                        world->compteur_debut = (float)(SDL_GetTicks()/1000.);
                    }
                }
                if(keystates[SDL_SCANCODE_M]){
                    world->hideMap = !world->hideMap ;
                    world->stop = !world->stop ;
                } 
                if(keystates[SDL_SCANCODE_ESCAPE]){ //si la touche appuyée est 'Echap'
                    world->etat_menu = 0;
                }
                break;
            }else {
                if(keystates[SDL_SCANCODE_M]){
                    world->hideMap = !world->hideMap ;
                    world->stop = !world->stop ;
                } 
            }   
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
        if(world->etat_menu < 3){
            handle_events_menu(event,world) ;
        }else {
            handle_events_player(event, world) ;
        }
       
        //Si l'utilisateur a cliqué sur le X de la fenêtre 
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
         //si une touche est appuyée

    }

}