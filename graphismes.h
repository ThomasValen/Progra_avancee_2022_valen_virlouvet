#ifndef __FONCTIONS_SDL__H__
#define __FONCTIONS_SDL__H__
#include "sdl2-light.h"
#include "world.h"



struct textures_s
{
    SDL_Texture* background;
    SDL_Texture* sky;
    SDL_Texture* bandes[513];
    SDL_Texture* wall;
    SDL_Texture* player ;
    SDL_Texture* ligne ;
    SDL_Surface* surface;
    SDL_Rect tab_bandes[513];
};
typedef struct textures_s textures_t;

void clean_textures(textures_t *textures) ;

void init_textures(SDL_Renderer * renderer, textures_t *textures);

void apply_background(SDL_Renderer * renderer, SDL_Texture * texture);

void refresh_graphics(SDL_Renderer * renderer, world_t *world, textures_t *textures);


#endif