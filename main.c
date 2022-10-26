#include "sdl2-light.h"
#include "world.h"
#include "graphismes.h"
#include "constante.h"

int main( int argc, char* args[] ){

    SDL_Event event;
    world_t world;
    ressources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;
    sprite_t *sprite;

      do{

        init(&window,&renderer,&textures,&world); //initialisation du jeu

        while(&world){ //tant que le jeu n'est pas fini
          //gestion des évènements
          //handle_events(&event,&world);

          //mise à jour des données liée à la physique du monde
          //update_data(&world);

          //rafraichissement de l'écran
          refresh_graphics(renderer,&world,&textures);

          // pause de 10 ms pour controler la vitesse de rafraichissement
          pause(10);
        }



      }while(&world);   //tant que le joueur n'a pas décider d'arrêter de jouer


      //pause a la fin du jeu de 3sec
      pause(1500);
      //nettoyage final
      clean(window,&renderer,&textures,&world);

      return 0;
}
	
