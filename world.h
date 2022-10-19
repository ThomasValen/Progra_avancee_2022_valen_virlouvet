#ifndef __WORLD__H__
#define __WORLD__H__

struct world_s{
int tab[][];
sprite_t background;
sprite_t wall;
};
typedef struct world_s world_t;

struct sprite_s{
    int x;
    int y;
    int h;
    int l;
};
typedef struct sprite_s sprite_t;


#endif