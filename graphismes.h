#ifndef __FONCTIONS_SDL__H__
#define __FONCTIONS_SDL__H__
#include "sdl2-light.h"
#include "world.h"



struct textures_s
{
    SDL_Texture* background;
    SDL_Texture* wall;
    SDL_Texture* player ;
};
typedef struct textures_s textures_t;

void clean_textures(textures_t *textures) ;

void init_textures(SDL_Renderer * renderer, textures_t *textures);

void apply_background(SDL_Renderer * renderer, SDL_Texture * texture);

void refresh_graphics(SDL_Renderer * renderer, world_t *world, textures_t *textures);

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b) ;

void unpack_color(const uint32_t color, uint8_t r, uint8_t g, uint8_t b, uint8_t a) ;

void ligne(world_t *world);

#endif