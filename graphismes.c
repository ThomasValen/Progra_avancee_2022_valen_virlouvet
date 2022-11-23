#include <stdio.h>
#include <stdlib.h>
#include "graphismes.h"
#include "constante.h"
#include "world.h"
#include <math.h> 
#include "sdl2-light.h"

void clean_textures(textures_t *textures){
    clean_texture(textures->background) ;
    clean_texture(textures->sky);
    clean_texture(textures->wall);
    clean_texture(textures->player) ;
    clean_texture(textures->ligne) ;
    for(int j=0;j<512;j++){
        clean_texture( textures->bandes[j] );       
    }
    //SDL_FreeSurface(textures->surface);
}

void init_textures(SDL_Renderer * renderer, textures_t *textures){
    textures->background = load_image( "ressources/fond.bmp", renderer);
    textures->sky = load_image( "ressources/carre_gris.bmp", renderer);

    textures->wall = load_image( "ressources/carre_rouge.bmp", renderer) ;

    textures->player = load_image("ressources/carre_bleu.bmp", renderer);

    textures->ligne = load_image("ressources/carre_blanc.bmp", renderer);

    textures->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
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

void color_3d(SDL_Renderer * renderer,world_t* world, textures_t* textures){
    textures->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    //apply_texture(textures->sky,renderer,0,0);
    if(world->three_d_check==1){
    
        for(int j=0;j<512;j++){
            clean_texture( textures->bandes[j] );       
        }
    }
    int x_incr=0;
    for(int i=0;i<512;i++){
        textures->tab_bandes[i].w=2;
        textures->tab_bandes[i].h=30000/world->nb_point_ligne[i];//a modif
        textures->tab_bandes[i].x=x_incr;
        textures->tab_bandes[i].y=SCREEN_HEIGHT/2 - (30000/world->nb_point_ligne[i])/2;//a modif
        x_incr=x_incr+2;
        SDL_FillRect(textures->surface, &textures->tab_bandes[i], SDL_MapRGB(textures->surface->format, 255 - world->nb_point_ligne[i], 0, 0));
        //textures->bandes[i] = SDL_CreateTextureFromSurface(renderer, textures->surface);
        //apply_texture(textures->bandes[i],renderer,0,0);
    }
    for(int y=0;y<1;y++){
        textures->bandes[y] = SDL_CreateTextureFromSurface(renderer, textures->surface);
        apply_texture(textures->bandes[y],renderer,0,0);
    }

    world->three_d_check=1;
    SDL_FreeSurface(textures->surface);
    
}


void refresh_graphics(SDL_Renderer * renderer, world_t* world, textures_t* textures){
    clear_renderer(renderer) ;
    
    
    color_3d(renderer,world,textures);
    apply_background(renderer, textures->background) ;

    for(int i=0;i<world->nb_mur;i++){
        apply_wall(world->wall[i],renderer,textures->wall);
    }
    
    
    apply_sprite(renderer, textures->player, world->player) ;

    
    
    for(int j = 0 ; j < 512 ; j++){
        for(int i = 0 ; i < world->nb_point_ligne[j]; i++){
            apply_wall(world->ligne[j][i], renderer, textures->ligne) ;
        }
    }
    
    update_screen(renderer);
}