#include <stdio.h>
#include <stdlib.h>
#include "graphismes.h"
#include "constante.h"
#include "world.h"
#include <math.h> 
#include "sdl2-light.h"

void clean_textures(textures_t *textures){
    clean_texture(textures->background) ;
    clean_texture(textures->wall);
    clean_texture(textures->player) ;
}

void init_textures(SDL_Renderer * renderer, textures_t *textures){
    textures->background = load_image( "ressources/fond.bmp", renderer);

    textures->wall = load_image( "ressources/carre_rouge.bmp", renderer) ;

    textures->player = load_image( "ressources/carre_bleu.bmp", renderer) ;
}

void apply_background(SDL_Renderer * renderer, SDL_Texture * texture){
    if(texture != NULL){
        apply_texture(texture, renderer, 0,0) ;
    }
}
//erreur pointeur
void apply_wall(sprite_t sprite, SDL_Renderer * renderer, SDL_Texture * texture){
    if(texture!=NULL){
        apply_texture(texture, renderer,sprite.x,sprite.y) ;
    }
}

void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t *sprite){
    if(texture!=NULL){
        apply_texture(texture, renderer,sprite->x,sprite->y) ;
    }
}


void refresh_graphics(SDL_Renderer * renderer, world_t* world, textures_t* textures){
    clear_renderer(renderer) ;

    apply_background(renderer, textures->background) ;
    
    for(int i=0;i<nb_murs(world->tab,world->hauteur_tab,world->longueur_tab);i++){
        apply_wall(world->wall[i],renderer,textures->wall);
    }

    apply_sprite(renderer, textures->player, world->player) ;

    ligne(world);

    update_screen(renderer);
}

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b) {
    const uint8_t a=255; 
    return (a<<24) + (b<<16) + (g<<8) + r;
}

void unpack_color(const uint32_t color, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    r = (color >>  0) & 255;
    g = (color >>  8) & 255;
    b = (color >> 16) & 255;
    a = (color >> 24) & 255;
}

void ligne(world_t *world){
    uint32_t framebuffer[1000];
    float player_a =  0;
    for (float t = 0 ; t<20 ; t+= .05){
        float cx = world->player->x + t*cos(player_a) ;
        float cy = world->player->y + t*sin(player_a) ;

        size_t pixel_x = cx*32 ;
        size_t pixel_y = cy*32 ;
        framebuffer[pixel_x + pixel_y*1280] = pack_color(255, 255, 255);
    }
}

    