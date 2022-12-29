#ifndef __GRAPHISMES__H__
#define __GRAPHISMES__H__
#include "sdl2-light.h"
#include "world.h"



struct textures_s
{
    SDL_Texture* background;
    SDL_Texture* sky;
    SDL_Texture* bandes;
    SDL_Texture* squelette;
    SDL_Texture* wall;
    SDL_Texture* key ;
    SDL_Texture* exit;
    SDL_Texture* enemy;
    SDL_Texture* player ;
    SDL_Texture* ligne ;
    SDL_Texture* fond_ecran ;
    SDL_Texture* titre ;
    SDL_Texture* play ;
    SDL_Texture* play_active ;
    SDL_Texture* button_exit ;
    SDL_Texture* button_exit_active ;
    SDL_Surface* surface;
    SDL_Rect * keys;
    SDL_Rect * enemys;
    SDL_Texture* epee1;
    SDL_Texture* epee2;
    SDL_Texture* epee3;
    SDL_Texture* epee4;
    SDL_Rect tab_bandes[513];
};
typedef struct textures_s textures_t;

void clean_textures(textures_t *textures) ;

void init_textures(SDL_Renderer * renderer, textures_t *textures, world_t* world);
void animation_epee(SDL_Renderer * renderer, world_t* world, textures_t* textures);

void apply_background(SDL_Renderer * renderer, SDL_Texture * texture);

void refresh_graphics(SDL_Renderer * renderer, world_t *world, textures_t *textures);

void refresh_graphics_menu(SDL_Renderer * renderer, world_t *world, textures_t *textures);


#endif