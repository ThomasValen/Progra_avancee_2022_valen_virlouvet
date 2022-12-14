#include <stdio.h>
#include <stdlib.h>
#include "graphismes.h"
#include "constante.h"
#include "sdl2-ttf-light.h"
#include "world.h"
#include <math.h> 
#include "score.h"
#include "sdl2-light.h"

void clean_textures(textures_t *textures){
    clean_texture(textures->background) ;
    clean_texture(textures->sky);
    clean_texture(textures->ground) ;
    clean_texture(textures->wall);
    clean_texture(textures->player) ;
    clean_texture(textures->ligne) ;
    clean_texture( textures->bandes );
    clean_texture(textures->key);
    clean_texture(textures->exit);
    clean_texture(textures->enemy) ;
    free(textures->keys);
    clean_texture(textures->fond_ecran);
    clean_texture(textures->titre) ;
    clean_texture(textures->play) ;
    clean_texture(textures->play_active);
    clean_texture(textures->button_exit) ;
    clean_texture(textures->button_exit_active);
    clean_texture(textures->epee1) ;
    clean_texture(textures->epee2) ;
    clean_texture(textures->epee3) ;
    clean_texture(textures->epee4) ;
    clean_texture(textures->compteur_key) ;
    clean_texture(textures->pv) ;
    clean_texture(textures->you_died) ;
    clean_texture(textures->you_escaped) ;
    clean_texture(textures->squelette);
    free(textures->enemys);
    clean_font(textures->font) ;
}

void init_textures(SDL_Renderer * renderer, textures_t *textures, world_t* world){
    textures->background = load_image( "ressources/fond.bmp", renderer);
    textures->sky = load_image( "ressources/carre_gris.bmp", renderer);
    textures->ground = load_image("ressources/carre_gris_reverse.bmp", renderer);

    textures->wall = load_image( "ressources/wall.bmp", renderer) ;

    textures->player = load_image("ressources/carre_bleu.bmp", renderer);

    textures->ligne = load_image("ressources/carre_blanc.bmp", renderer);

    //textures->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

    textures->key = load_image("ressources/key.bmp", renderer) ;

    textures->exit = load_image("ressources/carre_marron.bmp", renderer);

    textures->enemy =load_image("ressources/carre_rouge.bmp", renderer) ;

    textures->keys = (SDL_Rect*)malloc(world->nb_key*sizeof(SDL_Rect));
    textures->fond_ecran = load_image("ressources/fond_ecran.bmp", renderer) ;
    textures->titre = load_image("ressources/titre.bmp",renderer) ;
    textures->play = load_image("ressources/play.bmp", renderer) ;
    textures->play_active = load_image("ressources/play_active.bmp", renderer) ;
    textures->button_exit = load_image("ressources/exit.bmp", renderer) ;
    textures->button_exit_active = load_image("ressources/exit_active.bmp",renderer);
    textures->pv = load_image("ressources/coeur.bmp", renderer) ;
    textures->squelette=load_image("ressources/skeleton.bmp", renderer) ;
    textures->you_died = load_image("ressources/you_died.bmp", renderer) ;
    textures->you_escaped = load_image("ressources/you_escaped.bmp", renderer) ;
    textures->enemys = (SDL_Rect*)malloc(world->nb_enemy*sizeof(SDL_Rect));


    textures->epee1 =load_image("ressources/epees1.bmp", renderer) ;

    textures->epee2 =load_image("ressources/epees2.bmp", renderer) ;

    textures->epee3 =load_image("ressources/epees3.bmp", renderer) ;

    textures->epee4 =load_image("ressources/epees4.bmp", renderer) ;

    textures->compteur_key = load_image("ressources/compteur_key.bmp", renderer);

    textures->font = load_font("ressources/arial.ttf", 14);


}

void apply_background(SDL_Renderer * renderer, SDL_Texture * texture){//applique le fond
    if(texture != NULL){
        apply_texture(texture, renderer, 0,0) ;
    }
}
//erreur pointeur
void apply_wall(sprite_t sprite, SDL_Renderer * renderer, SDL_Texture * texture){//applique les murs
    if(texture!=NULL){
        apply_texture(texture, renderer,sprite.x,sprite.y) ;
    }
}

void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t *sprite){
    if(texture!=NULL){
        apply_texture(texture, renderer,sprite->x,sprite->y) ;
    }
}

void color_3d(SDL_Renderer * renderer,world_t* world, textures_t* textures){//affiche les murs 3ds, les ennemies et les clees
    int couleur;
    int couleur2;
    textures->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    
    if(world->three_d_check==1){
    
        clean_texture( textures->bandes );       
    
    }
    int x_incr=0;
    for(int i=0;i<513;i++){
        textures->tab_bandes[i].w=2;
        textures->tab_bandes[i].h=30000/world->nb_point_ligne[i]/*/cos((i*0.16+world->angle)*PI/180-(256*0.16+world->angle)*PI/180)*/;//a modif
        if(textures->tab_bandes[i].h<0){
            textures->tab_bandes[i].h=textures->tab_bandes[i].h*(-1);
        }
        textures->tab_bandes[i].x=x_incr;
        textures->tab_bandes[i].y=SCREEN_HEIGHT/2 - (30000/world->nb_point_ligne[i]/*/cos((i*0.16+world->angle)*PI/180-(256*0.16+world->angle)*PI/180)*/)/2;//a modif
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
        couleur = 254 - world->nb_point_ligne[y];
        if(couleur<0){
            couleur=0;
        }
        SDL_FillRect(textures->surface, &textures->tab_bandes[y], SDL_MapRGB(textures->surface->format, couleur, 0, 0));
        //printf("%d\n",world->no_ligne_db_sortie);
        if(y==world->no_ligne_db_sortie){
            couleur2 = 255 - world->nb_point_ligne[y];
            if(couleur2<0){
                couleur2=0;
            }
            for(int f=0;f<world->nb_bandes_sortie;f++){
                if(world->nb_key_recup==world->nb_key){
                    SDL_FillRect(textures->surface, &textures->tab_bandes[y], SDL_MapRGBA(textures->surface->format, 0, 255, 0,0));
                }else{
                    SDL_FillRect(textures->surface, &textures->tab_bandes[y], SDL_MapRGB(textures->surface->format, 0, couleur2, 0));
                }
                
                y++;
            }
        }
        
    }
    //SDL_FillRect(textures->surface, &textures->tab_bandes[100], SDL_MapRGB(textures->surface->format, 0, 255, 0));
    //SDL_FillRect(textures->surface, &textures->tab_bandes[101], SDL_MapRGB(textures->surface->format, 0, 255, 0));
    
    
    Uint32 colorkey = SDL_MapRGB( textures->surface->format, 0, 255, 0 );
    SDL_SetColorKey( textures->surface, SDL_RLEACCEL , colorkey );
    textures->bandes = SDL_CreateTextureFromSurface(renderer, textures->surface);
    apply_texture(textures->bandes,renderer,0,0);

    SDL_Surface* surface2 = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    for(int u=0;u<world->nb_key;u++){
        if(world->key[u].is_looking_for==1){
            textures->keys[u].w = 10000/(world->key[u].placement_y);
            textures->keys[u].h = 10000/(world->key[u].placement_y);
            textures->keys[u].x = world->key[u].placement_x*2-textures->keys[u].w/2;
            textures->keys[u].y = SCREEN_HEIGHT/2;
            SDL_FillRect(surface2, &textures->keys[u],SDL_MapRGBA(surface2->format, 0, 254, 0,255) );
            SDL_RenderCopy(renderer,textures->key,NULL,&textures->keys[u]);
        }
    }
    for(int s=0;s<world->nb_enemy;s++){
        if(world->enemy[s].is_looking_for==1){
            textures->enemys[s].w = 10000/(world->enemy[s].placement_y)*2;
            textures->enemys[s].h = 10000/(world->enemy[s].placement_y)*3;
            textures->enemys[s].x = world->enemy[s].placement_x*2-textures->enemys[s].w/2;
            textures->enemys[s].y = SCREEN_HEIGHT/2-textures->enemys[s].w/3;
            SDL_FillRect(surface2, &textures->enemys[s],SDL_MapRGBA(surface2->format, 0, 254, 0,255) );
            SDL_RenderCopy(renderer,textures->squelette,NULL,&textures->enemys[s]);
        }
    }

    world->three_d_check=1;
    SDL_FreeSurface(textures->surface);
    SDL_FreeSurface(surface2);


    
}

void animation_epee(SDL_Renderer * renderer, world_t* world, textures_t* textures){//animation de l'epee
    if(world->is_attacking==1){
        if((int)(((float)(SDL_GetTicks()/1000.)-world->compteur_debut)*4) %4 ==0){
            apply_sprite(renderer,textures->epee1, world->epee) ;
        }else if((int)(((float)(SDL_GetTicks()/1000.)-world->compteur_debut)*4) %4 ==1){
            apply_sprite(renderer,textures->epee2, world->epee) ;
        }
        else if((int)(((float)(SDL_GetTicks()/1000.)-world->compteur_debut)*4) %4 ==2){
            world->attack = 1 ;
            apply_sprite(renderer,textures->epee3, world->epee) ;
        }else if((int)(((float)(SDL_GetTicks()/1000.)-world->compteur_debut)*4) %4 ==3){
            world->attack = 1 ;
            apply_sprite(renderer,textures->epee4, world->epee) ;
        }
    }else{
        apply_sprite(renderer,textures->epee1, world->epee) ;
    }

}

void afficher_miniMap(SDL_Renderer * renderer, world_t* world, textures_t* textures){//affiche minimap en appuyant sur ,
    apply_sprite(renderer, textures->background, world->background) ;
    for(int j = 0 ; j < 513 ; j++){
        for(int i = 0 ; i < world->nb_point_ligne[j]; i++){
            apply_wall(world->ligne[j][i], renderer, textures->ligne) ;
        }
    }
    for(int i=0;i<world->nb_mur;i++){
        apply_wall(world->wall[i],renderer,textures->wall);
    }
    for(int i = 0 ; i < world->nb_key; i++){
        apply_wall(world->key[i],renderer, textures->key) ;
    }
    for(int i = 0 ; i < world->nb_enemy ; i++){
        apply_wall(world->enemy[i],renderer, textures->enemy) ;
    }    
    apply_sprite(renderer, textures->player, world->player) ;
    apply_sprite(renderer, textures->exit, world->exit) ;
}


void refresh_graphics(SDL_Renderer * renderer, world_t* world, textures_t* textures){
    clear_renderer(renderer) ;
    
    apply_texture(textures->sky,renderer,0,SCREEN_HEIGHT/2);
    apply_texture(textures->ground,renderer, 0, 0) ;
    


    for(int z=0;z<world->nb_key;z++){
            //printf("mur : %d      clef : %d\n",world->nb_point_ligne[world->key[z].placement_x],world->key[z].placement_y);
            if(world->key[z].placement_y>=0 && world->key[z].placement_x >=0){
                if( world->nb_point_ligne[world->key[z].placement_x]<=world->key[z].placement_y  ){
                    setIsLooking(world,z,0);
                }
            }
            
        if(world->key[z].placement_x==512 ||world->key[z].placement_x==0 ){
            setIsLooking(world,z,0);
        }
    }

    for(int t=0;t<world->nb_enemy;t++){
        if(world->enemy[t].placement_x>510){
            setIsLooking2(world,t,0);
        }
    }

    color_3d(renderer,world,textures);


    for(int t=0;t<world->nb_enemy;t++){
        if(world->enemy[t].is_looking_for==1){
            //printf("mur : %d      clef : %d\n",world->nb_point_ligne[world->key[z].placement_x],world->key[z].placement_y);
            if(world->enemy[t].placement_y>=0 && world->enemy[t].placement_x >=0){
                if( world->nb_point_ligne[world->enemy[t].placement_x]<world->enemy[t].placement_y  ){
                    setIsLooking2(world,t,0);
                }
            }
            //printf("x : %d\n",world->enemy[t].placement_x);
            if(world->enemy[t].placement_x< textures->enemys[t].w/8 ){
                setIsLooking2(world,t,0);
            }
        }
    }

    animation_epee(renderer,world,textures);

    if(!world->hideMap){
        afficher_miniMap(renderer, world, textures) ;
    }
    
    apply_sprite(renderer, textures->compteur_key, world->compteur_key) ;
    char nbkey[10] ;
    sprintf(nbkey," %d/%d ", world->nb_key_recup, world->nb_key) ;
    apply_text(renderer,SCREEN_WIDTH - 150, 100,50 , 50, nbkey,textures->font) ;
    
    for(int p = 0 ; p < world->nb_pv ; p++){
        apply_wall( world->pv[p], renderer,textures->pv);
    }

    if((float)(SDL_GetTicks()/1000.)- world->compteur_debut > 1.0){
        world->is_attacking=0;
    }

    if(world->etat_menu < 3){
        if(world->nb_pv == 0){
            apply_sprite(renderer, textures->you_died, world->you_died) ;
        }else if(world->nb_key_recup == world->nb_key){
            apply_sprite(renderer, textures->you_escaped, world->you_died) ;
            char score[1000];
            sprintf(score, "Votre score : %d", world->compteur_score) ;
            apply_text(renderer, SCREEN_WIDTH/2-200, SCREEN_HEIGHT- 250, 200, 50, score,textures->font) ;
        }
        
    }
    

    //printf("compteur_debut : %f   is_attacking : %d\n",world->compteur_debut,world->is_attacking);
    
    update_screen(renderer);
}

void refresh_graphics_menu(SDL_Renderer* renderer, world_t* world,textures_t* textures){//textures du menu
    //on vide le renderer
    clear_renderer(renderer);
    //application des textures dans le renderer
    if(world->etat_menu == 0){
        apply_sprite(renderer, textures->fond_ecran,world->menu);
        apply_sprite(renderer, textures->titre,world->titre);
        apply_sprite(renderer, textures->play_active,world->play);
        apply_sprite(renderer, textures->button_exit,world->button_exit);
    }    
    if(world->etat_menu == 1){
        apply_sprite(renderer, textures->fond_ecran,world->menu);
        apply_sprite(renderer, textures->titre,world->titre);
        apply_sprite(renderer, textures->play,world->play);
        apply_sprite(renderer, textures->button_exit_active,world->button_exit);
    }
    
    char text_score[1000];
    char score[1000];
    top5(world->score, world) ;
    sprintf(text_score, "Score :") ;
    apply_text(renderer, 50, 250, 200, 50, text_score,textures->font) ;
    for(int i=0; i<5; i++){
        sprintf(score, "%d-     %d",i+1,world->top[i]);
        apply_text(renderer,100,300 + 60 *i, 100, 50, score,textures->font);
    }
    

    // on met ?? jour l'??cran
    update_screen(renderer);
}

void affichage_score(SDL_Renderer* renderer, world_t* world){
    FILE* fichier = NULL;
    char chara ;
    char nombre[1000] ;
    int score_joueur = 0 ;
    int incr = 0 ;
    fichier =fopen("score.txt", "r");
    if(fichier !=NULL){
       do{
            chara = fgetc(fichier);
            if(chara!=EOF){
                if(chara == '*'){
                    score_joueur = atoi(nombre) ;
                    world->score = ajouter_score(score_joueur, world->score) ;
                    memset(nombre, 0, incr) ;
                    incr = 0 ;
                }else{
                    nombre[incr] = chara ;
                    incr++ ;
                }    
            }
            
            
        } while (chara!=EOF);
        fclose(fichier); 
    }
    top5(world->score, world) ;
}

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){ 
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_ttf() ;
    init_textures(*renderer,textures,world);

}  