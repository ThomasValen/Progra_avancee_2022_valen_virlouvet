#include <stdio.h>
#include <stdlib.h>
#include "graphismes.h"
#include "constante.h"
#include "world.h"
#include "sdl2-light.h"

void clean_textures(textures_t *textures){
    clean_texture(textures->background) ;
    clean_texture(textures->wall) ;
}

void init_textures(SDL_Renderer * renderer, textures_t *textures){
    textures->background = load_image( "ressources/fond.bmp", renderer);

    textures->wall = load_image( "ressources/wall.bmp", renderer) ;
}

void apply_background(SDL_Renderer * renderer, SDL_Texture * texture){
    if(texture != NULL){
        apply_texture(texture, renderer, 0,0) ;
    }
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite ){
    if(texture != NULL){
        apply_texture(texture, renderer, sprite->x, sprite->y) ;
    }
}

void refresh_graphics(SDL_Renderer * renderer, world_t *world, textures_t *textures){
    clear_renderer(renderer) ;

    apply_background(renderer, textures->background) ;
    for(int i = 0; i < 500 ; i++){
      apply_sprite(renderer,textures->wall, &(world->wall[i])) ;
    }

    update_screen(renderer);
}

    