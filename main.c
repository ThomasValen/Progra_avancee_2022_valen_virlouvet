#include "score.h"
#include "sdl2-light.h"
#include "world.h"
#include "graphismes.h"
#include "constante.h"
#include "eventsMain.h"


/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);


void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
    
}




int main( int argc, char* args[] ){
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;
    sprite_t *sprite;

    world.gameover = 0 ;
    world.etat_menu = 0 ;

      do{
        init(&window,&renderer,&textures,&world); //initialisation du jeu

        while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
          if(world.etat_menu < 3 ){
            handle_events(&event, &world) ;

            update_data(&world); 

            refresh_graphics_menu(renderer, &world,&textures) ;
          }else{
            handle_events(&event,&world);

            update_data(&world) ;

            //rafraichissement de l'écran
            refresh_graphics(renderer,&world,&textures);
            if(world.etat_menu < 3){
              printf("je rentre dans la fin") ;
              ajouter_score(world.compteur_score, world.score) ;
              toString(world.score) ;
              
            }
            // pause de 10 ms pour controler la vitesse de rafraichissement
            pause(10);
          }
        }
      }while(!is_game_over(&world));   //tant que le joueur n'a pas décider d'arrêter de jouer


      //pause a la fin du jeu de 3sec
      pause(1500);
      //nettoyage final
      clean(window,renderer,&textures,&world);

      return 0;
}
	
