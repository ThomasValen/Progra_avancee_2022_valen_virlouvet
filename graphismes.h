#ifndef __FONCTIONS_SDL__H__
#define __FONCTIONS_SDL__H__
#include <SDL2/SDL.h>
#include "sdl2-light.h"
#include "world.h"



struct ressources_s
{
    SDL_Texture* background;
};
typedef struct ressources_s ressources_t;

void clean_textures(ressources_t *textures) ;

void init_textures(SDL_Renderer * renderer, ressources_t *textures);

void apply_background(SDL_Renderer * renderer, SDL_Texture * texture);

void refresh_graphics(SDL_Renderer * renderer, world_t *world, ressources_t *textures);

void clean(SDL_Window *window, SDL_Renderer **renderer, ressources_t *textures, world_t *world);

void init(SDL_Window **window, SDL_Renderer **renderer, ressources_t *textures, world_t *world);

#endif