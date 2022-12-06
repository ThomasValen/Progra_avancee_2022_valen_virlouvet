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
    clean_texture( textures->bandes );
    clean_texture(textures->key);
    clean_texture(textures->exit);
    clean_texture(textures->enemy) ;
}

void init_textures(SDL_Renderer * renderer, textures_t *textures){
    textures->background = load_image( "ressources/fond.bmp", renderer);
    textures->sky = load_image( "ressources/carre_gris.bmp", renderer);

    textures->wall = load_image( "ressources/wall.bmp", renderer) ;

    textures->player = load_image("ressources/carre_bleu.bmp", renderer);

    textures->ligne = load_image("ressources/carre_blanc.bmp", renderer);

    textures->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

    textures->key = load_image("ressources/key.bmp", renderer) ;

    textures->exit = load_image("ressources/carre_marron.bmp", renderer);

    textures->enemy =load_image("ressources/carre_rouge.bmp", renderer) ;
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
    int couleur;
    textures->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    
    if(world->three_d_check==1){
    
        clean_texture( textures->bandes );       
    
    }
    int x_incr=0;
    for(int i=0;i<513;i++){
        textures->tab_bandes[i].w=2;
        textures->tab_bandes[i].h=32000/world->nb_point_ligne[i]/*/cos((i*0.16+world->angle)*PI/180-(256*0.16+world->angle)*PI/180)*/;//a modif
        if(textures->tab_bandes[i].h<0){
            textures->tab_bandes[i].h=textures->tab_bandes[i].h*(-1);
        }
        textures->tab_bandes[i].x=x_incr;
        textures->tab_bandes[i].y=SCREEN_HEIGHT/2 - (32000/world->nb_point_ligne[i]/*/cos((i*0.16+world->angle)*PI/180-(256*0.16+world->angle)*PI/180)*/)/2;//a modif
        x_incr=x_incr+2;
        
        //textures->bandes[i] = SDL_CreateTextureFromSurface(renderer, textures->surface);
        //apply_texture(textures->bandes[i],renderer,0,0);
    }

    SDL_Rect couleur_fond;
    couleur_fond.h=SCREEN_HEIGHT;
    couleur_fond.w=SCREEN_WIDTH;
    couleur_fond.x=0;
    couleur_fond.y=0;
    SDL_FillRect(textures->surface, &couleur_fond, SDL_MapRGB(textures->surface->format, 0, 255, 0));

    for(int y=0;y<513;y++){
        couleur = 255 - world->nb_point_ligne[y];
        if(couleur<0){
            couleur=0;
        }
        SDL_FillRect(textures->surface, &textures->tab_bandes[y], SDL_MapRGB(textures->surface->format, couleur, 0, 0));
        
    }
    
    
    Uint32 colorkey = SDL_MapRGB( textures->surface->format, 0, 255, 0 );


    SDL_Rect test;
    test.x = SCREEN_WIDTH/2;
    test.y = SCREEN_HEIGHT/2;
    test.w = 200;
    test.h = 200;
    SDL_RenderCopy(renderer,textures->wall,NULL,&test);
    SDL_FillRect(textures->surface, &test,SDL_MapRGB(textures->surface->format, 0, 255, 0) );


    SDL_SetColorKey( textures->surface, SDL_RLEACCEL , colorkey );
    textures->bandes = SDL_CreateTextureFromSurface(renderer, textures->surface);
    apply_texture(textures->bandes,renderer,0,0);

    world->three_d_check=1;
    SDL_FreeSurface(textures->surface);
    


    
}


void refresh_graphics(SDL_Renderer * renderer, world_t* world, textures_t* textures){
    clear_renderer(renderer) ;
    
    apply_texture(textures->sky,renderer,0,SCREEN_HEIGHT/2);
    color_3d(renderer,world,textures);
    apply_background(renderer, textures->background) ;

    for(int i=0;i<world->nb_mur;i++){
        apply_wall(world->wall[i],renderer,textures->wall);
    }

    for(int j = 0 ; j < 513 ; j++){
        for(int i = 0 ; i < world->nb_point_ligne[j]; i++){
            apply_wall(world->ligne[j][i], renderer, textures->ligne) ;
        }
    }

    for(int i = 0 ; i < world->nb_key; i++){
        apply_wall(world->key[i],renderer, textures->key) ;
    }
    
    for(int i = 0 ; i < world->nb_enemy ; i++){
        apply_wall(world->enemy[i],renderer, textures->enemy) ;
    }    
    apply_sprite(renderer, textures->player, world->player) ;
    apply_sprite(renderer, textures->exit, world->exit) ;

    
    
    update_screen(renderer);
}