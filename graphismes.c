#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphismes.h"
#include "constante.h"
#include "world.h"

void clean_textures(ressources_t *textures){
    clean_textures(textures->background) ;
}

void init_textures(SDL_Renderer * renderer, ressources_t *textures){
    textures->background = load_image( "ressources/fond.bmp", renderer);
}

void apply_background(SDL_Renderer * renderer, SDL_Texture * texture){
    if(texture != NULL){
        apply_texture(texture, renderer, 0,0) ;
    }
}

void refresh_graphics(SDL_Renderer * renderer, world_t *world, ressources_t *textures){
    clear_renderer(renderer) ;

    apply_background(renderer, textures->background) ;

    update_screen(renderer);
}

void clean(SDL_Window *window, SDL_Renderer **renderer, ressources_t *textures, world_t *world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer, window) ;

}

void init(SDL_Window **window, SDL_Renderer **renderer, ressources_t *textures, world_t *world){
    init_sdl(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer, textures) ;
}

    