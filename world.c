#include <SDL2/SDL.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "world.h"
#include <math.h> 
#include "score.h"
#include "constante.h"

void init_data(world_t * world){
    //on n'est pas à la fin du jeu

	//Initialisation de valeurs 
	init_valeurs(world);

	// Allocation de mémoire
	init_memoire(world);

	//initialisation des sprites
	init_environnement(world) ;

}

void init_memoire(world_t* world){
    world->background = (sprite_t*)malloc(sizeof(sprite_t));
    world->player = (sprite_t*)malloc(sizeof(sprite_t));
    world->view_player = (sprite_t*)malloc(sizeof(sprite_t)) ;
    world->exit = (sprite_t*)malloc(sizeof(sprite_t)) ;
    world->menu = (sprite_t*)malloc(sizeof(sprite_t)) ;
    world->titre = (sprite_t*)malloc(sizeof(sprite_t));
    world->play = (sprite_t*)malloc(sizeof(sprite_t));
    world->button_exit = (sprite_t*)malloc(sizeof(sprite_t)) ;
    world->epee = (sprite_t*)malloc(sizeof(sprite_t)) ;
    world->compteur_key = (sprite_t*)malloc(sizeof(sprite_t)) ;
    world->you_died = (sprite_t*) malloc(sizeof(sprite_t)) ;
    world->score = cons_empty() ;
    
    

    //world->wall = cree_murs(500);
    world->tab = changer_monde(world,world->hauteur_tab,world->longueur_tab );
    world->key = creer_tableau(world->nb_key) ;
    world->enemy = creer_tableau(world->nb_enemy) ;
    world->wall = creer_tableau(world->nb_mur) ;
    world->pv = creer_tableau(world->nb_pv) ;
    world->ligne = creer_ligne(516,2000) ;
}

void init_valeurs(world_t* world){
	//Initialisation de valeurs 
    world->hauteur_tab=sethauteur();
    world->longueur_tab=setlongueur();
    world->gameover=0;
    world->direction=0;
    for (int i = 0; i < 516; i++)
    {
        world->nb_point_ligne[i] = 0 ;
    }

    world->nb_mur = 0 ;

    world->angle = 180 ;

    world->nb_bandes_sortie=0;
    world->no_ligne_db_sortie=-1;

    world->three_d_check=0;

    world->nb_key = 0 ;
    world->nb_key_recup = 0 ;

    world->nb_enemy = 0 ;

    world->attack = 0 ;

    world->nb_pv = 3 ;

    world->compteur_score = 0 ;

    world->stop = false ;

    world->is_attacking=0;

    world->hideMap = true ;
    world->readScore = true ;

    world->compteur_debut2=10000;
    
    
}

void init_environnement(world_t* world){
	//initialisation des sprites
	init_sprite(world->background,0,0, world->hauteur_tab*WALL_HEIGHT, world->longueur_tab*WALL_WIDTH,0);
    init_sprite(world->menu, 0 , 0 ,SCREEN_HEIGHT, SCREEN_WIDTH,0);
    init_sprite(world->titre, SCREEN_WIDTH/2-300, 100, SCREEN_HEIGHT, SCREEN_WIDTH,0);
    init_sprite(world->play, SCREEN_WIDTH/2 -90, 300, SCREEN_HEIGHT, SCREEN_WIDTH,0);
    init_sprite(world->button_exit, SCREEN_WIDTH/2 -90, 500, SCREEN_HEIGHT, SCREEN_WIDTH,0);
    init_sprite(world->epee, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, 0, 0, 0) ;
    init_sprite(world->compteur_key, SCREEN_WIDTH - 100, 100,50 , 150, 0);
    init_sprite(world->you_died, 0, 0, 300, 700, 0) ;
    for (int p = 0; p < 3; p++) {
        init_sprite(&(world->pv[p]),(50*p)+ 50 , SCREEN_HEIGHT-200, PV_HEIGHT, PV_WIDTH, 0) ;
    }

    int indice_wall=0;
    int indice_key = 0 ;
    int indice_enemy = 0 ;
	for(int i=0;i<(world->hauteur_tab);i++){
        for(int j = 0;j<(world->longueur_tab);j++){
            if(world->tab[i][j]==1){
                init_sprite(&(world->wall[indice_wall]),(j*WALL_WIDTH),(i*WALL_HEIGHT),WALL_HEIGHT,WALL_WIDTH,0);
                indice_wall++;
            }else if(world->tab[i][j]== 2){
                init_sprite(world->player,(2*j*PLAYER_WIDTH+WALL_WIDTH/4),(2*i*PLAYER_HEIGHT+WALL_HEIGHT/4),PLAYER_HEIGHT, PLAYER_WIDTH,0);
            }
            else if(world->tab[i][j] == 4){
                init_sprite(&(world->key[indice_key]),(j*KEY_WIDTH - PLAYER_WIDTH ),(i*KEY_HEIGHT - PLAYER_HEIGHT),KEY_HEIGHT, KEY_WIDTH,indice_key+1);
                world->key[indice_key].placement_x=-1;
                world->key[indice_key].placement_y=-1;
                indice_key++ ;
            }
            else if(world->tab[i][j] == 3){
                init_sprite(world->exit,(j*WALL_WIDTH),(i*WALL_HEIGHT),WALL_HEIGHT,WALL_WIDTH,0);
            }
            else if(world->tab[i][j]== 5){
                init_sprite(&(world->enemy[indice_enemy]),(2*j*PLAYER_WIDTH+WALL_WIDTH/4),(2*i*PLAYER_HEIGHT+WALL_HEIGHT/4),PLAYER_HEIGHT, PLAYER_WIDTH,0);
                world->enemy[indice_enemy].findPlayer = false ;
                world->enemy[indice_enemy].ishitting = false ;
                indice_enemy++ ;
                
            }
        }
    }
    float angle = world->angle ;
    for (int i = 0; i < 513; i++)
    {
        ligne(world, angle, i) ;
        angle = angle + 0.15;//0.15
    }


    //direction deplacements
    angle = world->angle + 90 ;
    ligne(world, angle, 513) ;
    angle = world->angle +180 ;
    ligne(world,angle, 514) ;
    angle = world->angle + 270 ;
    ligne(world,angle,515) ;



}

void clean_data(world_t *world){
    free(world->background);
    free(world->player) ;
    free(world->exit) ;
    free(world->play) ;
    free(world->button_exit) ;
    free(world->titre) ;
    free(world->menu) ;
    free(world->epee) ;
    free(world->compteur_key);
    free(world->you_died) ;
    //free_score(world->score) ;
    //free_matrice(world->tab,world->longueur_tab,world->hauteur_tab);
    //free_murs(world->wall);
}


void init_sprite(sprite_t *sprite,float x,float y,int h,int l,int no_key){
    sprite->x=x;
    sprite->y=y;
    sprite->h=h;
    sprite->l=l;
    sprite->no_key=no_key;
}

int sethauteur(){
    FILE* fichier=NULL;
    char chara;
    int lignes=0;
    int count=0;
    fichier =fopen("map.txt","r");
    if (fichier != NULL){
        do{
            count++;
            chara = fgetc(fichier);
            if(chara=='\n'){
                lignes++;
            }
        } while (chara!=EOF);
        fclose(fichier);
    }
    return lignes;
}

int setlongueur(){
    FILE* fichier=NULL;
    char chara;
    int max=0;
    int colonnes=0;
    fichier =fopen("map.txt","r");
    if (fichier != NULL){        
        do{
            chara = fgetc(fichier);
            if(chara=='\n'){
                colonnes=0;
            }else{
                colonnes++;
            }
            if(max<colonnes){
                max=colonnes;
            }
        } while (chara!=EOF);
        fclose(fichier);
    }
    return max;
}

int** changer_monde(world_t* world,int ligne,int colonne){
    int ** T = malloc(ligne*sizeof(int*));
    if(T == NULL)
        exit(EXIT_FAILURE);
    for(int i = 0; i < ligne ; i++)
        T[i] = malloc(colonne*sizeof(int));

    FILE* fichier=NULL;
    char chara;
    int lignes = 0;
    int colonnes = 0;
    fichier =fopen("map.txt","r");
    int sortie = 0 ;

 
    if (fichier != NULL){
        do{
            chara = fgetc(fichier);
            if(chara!=EOF){
                if(chara == '#'){
                    T[lignes][colonnes]=1;
                    world->nb_mur++ ;
                }else if(chara == 'p'){

                    T[lignes][colonnes]= 2;

                }else if(chara == '*'){
                    T[lignes][colonnes] = 4 ;
                    world->nb_key++ ;
                }else if(chara == 's'){
                    if (sortie == 0) {
                        T[lignes][colonnes]= 3;
                        sortie++ ;
                    }else{
                        T[lignes][colonnes]=1;
                        world->nb_mur++ ;
                    }
                    

                }else if(chara == 'e'){
                    T[lignes][colonnes] = 5 ;
                    world->nb_enemy++ ;
                }else{
                    T[lignes][colonnes]=0;
                }
                if(chara=='\n'){
                    lignes++;
                    colonnes=0;
                }else{
                    colonnes++;
                }
            }
            
        } while (chara!=EOF);
        fclose(fichier);
    }
    printf("\n") ;
    return T;

}

sprite_t* suppr(sprite_t* tab, sprite_t sprite, int nb_element){
    for(int i = 0 ; i < nb_element; i++ ){
        if(tab[i].x == sprite.x){
            if(tab[i].y == sprite.y){
                tab[i] = tab[i+1] ;
            }  
        }
    }
    return tab ;
}


sprite_t* creer_tableau(int nb_elements){
    sprite_t* T = (sprite_t*)malloc(nb_elements*sizeof(sprite_t));
    if(T == NULL) exit(EXIT_FAILURE);
    return T;
}

sprite_t** creer_ligne(int ligne, int colonne){
    sprite_t ** T = malloc(ligne*sizeof(sprite_t*));
    if(T == NULL)
        exit(EXIT_FAILURE);
    for(int i = 0; i < ligne ; i++)
        T[i] = malloc(colonne*sizeof(sprite_t));
    return T ;
}

int nb_murs(int **tab,int hauteur_tab,int longueur_tab){
    int count =0;
    for(int i=0;i<(longueur_tab);i++){
        for(int j = 0;j<(hauteur_tab);j++){
            if(tab[j][i]==1){
                count++;
            }
        }
    }
    return count;
}

int two_sprites_collide(sprite_t *sp1, sprite_t *sp2){
    int w1 = sp1->l ;
    int w2 = sp2->l ;
    int h1 = sp1->h;
    int h2 = sp2->h;
    int x1 = sp1->x ;
    int x2 = sp2->x ;
    int y1 = sp1->y ;
    int y2 = sp2->y ;


	return x1 +w1 > x2 && x1 < x2 + w2 && y1 +h1 >y2 && y1 <y2 +h2;
    //return (abs(x1 - x2) <= (w1 + w2) / 2) && (abs(y1 - y2) <= (h1 + h2) / 2);
}

int sprites_collide(sprite_t *sp1, sprite_t sp2)
{
    int w1 = sp1->l ;
    int w2 = sp2.l ;
    int h1 = sp1->h;
    int h2 = sp2.h;
    int x1 = sp1->x ;
    int x2 = sp2.x ;
    int y1 = sp1->y ;
    int y2 = sp2.y ;


	return x1 +w1 > x2 && x1 < x2 + w2 && y1 +h1 >y2 && y1 <y2 +h2;
    //return (abs(x1 - x2) <= (w1 + w2) / 2) && (abs(y1 - y2) <= (h1 + h2) / 2);
}

int sprites_collide_ligne(sprite_t sp1, sprite_t sp2)
{
    int w1 = sp1.l ;
    int w2 = sp2.l ;
    int h1 = sp1.h;
    int h2 = sp2.h;
    int x1 = sp1.x ;
    int x2 = sp2.x ;
    int y1 = sp1.y ;
    int y2 = sp2.y ;


	return x1 +w1 > x2 && x1 < x2 + w2 && y1 +h1 >y2 && y1 <y2 +h2;
    //return (abs(x1 - x2) <= (w1 + w2) / 2) && (abs(y1 - y2) <= (h1 + h2) / 2);
}

void handle_sprites_collision(sprite_t *sp1, sprite_t sp2, world_t *world)
{
    int collision = sprites_collide(sp1, sp2);
    if (collision == 1)
    {
        if(world->direction==1){
            sp1->x = world->ligne[513][0].x - PLAYER_WIDTH/2;
            sp1->y = world->ligne[513][0].y - PLAYER_HEIGHT/2;
        }
        if(world->direction==2){
            sp1->x = world->ligne[515][0].x - PLAYER_HEIGHT/2;
            sp1->y = world->ligne[515][0].y - PLAYER_HEIGHT/2;
        }
        if(world->direction==3){
            sp1->y = world->ligne[514][0].y - PLAYER_HEIGHT/2;
            sp1->x =  world->ligne[514][0].x - PLAYER_HEIGHT/2;
        }
        if(world->direction==4){
            sp1->y = world->ligne[256][0].y - PLAYER_HEIGHT/2;
            sp1->x = world->ligne[256][0].x - PLAYER_HEIGHT/2;
        }
        
    }
}

void handle_two_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t *world)
{
    int collision = two_sprites_collide(sp1, sp2);
    if (collision == 1)
    {
        if(world->direction==1){
            sp1->x = world->ligne[513][0].x - PLAYER_WIDTH/2;
            sp1->y = world->ligne[513][0].y - PLAYER_HEIGHT/2;
        }
        if(world->direction==2){
            sp1->x = world->ligne[515][0].x - PLAYER_HEIGHT/2;
            sp1->y = world->ligne[515][0].y - PLAYER_HEIGHT/2;
        }
        if(world->direction==3){
            sp1->y = world->ligne[514][0].y - PLAYER_HEIGHT/2;
            sp1->x =  world->ligne[514][0].x - PLAYER_HEIGHT/2;
        }
        if(world->direction==4){
            sp1->y = world->ligne[256][0].y - PLAYER_HEIGHT/2;
            sp1->x = world->ligne[256][0].x - PLAYER_HEIGHT/2;
        }
        
    }
}

int PointIsInWall(int x,int y,sprite_t wall){
    if(wall.x<=x<=wall.x+WALL_WIDTH){
        if(wall.y<=y<=wall.y+WALL_HEIGHT){
            return 1;
        }
    }
    return 0;
}

int PointIsInWalls(int x,int y,world_t*world){
    for(int i=0;i<nb_murs(world->tab,world->hauteur_tab,world->longueur_tab);i++){
        if(PointIsInWall(x,y,world->wall[i])==1){
            return 1;
        }
    }
    return 0;
}



void free_matrice(int** T, int taille1, int taille2) {
    for(int i = 0; i < taille1; i++)
        free(T[i]);
    free(T);
    T = NULL;
}

void free_murs(sprite_t* T) {
    free(T);
    T = NULL;
}

void enemyAttack(world_t *world){
    for(int i = 0; i < world->nb_enemy ; i++){
        if(sprites_collide(world->player, world->enemy[i])){
            world->nb_pv = world->nb_pv - 1 ;
            //for (int j = 0;  j < world->nb_mur; j++) {
               // for (int recule = RECULE; recule > 0; recule--) {
                    //if (!sprites_collide_ligne(world->ligne[514][RECULE], world->wall[i])) {
                        world->player->y = world->ligne[514][RECULE].y - PLAYER_HEIGHT/2;
                        world->player->x =  world->ligne[514][RECULE].x - PLAYER_HEIGHT/2;
                        world->enemy[i].ishitting=true;
                        world->compteur_debut2 = (float)(SDL_GetTicks()/1000.);
                   // }
                    if(world->nb_pv == 0){
                        world->etat_menu = 0 ;
                    }
                //}
            //}    
        }
    }
}

void enemyCollision(world_t *world){
    for (int j = 0; j < world->nb_enemy; j++) {
        for(int i=0;i<nb_murs(world->tab,world->hauteur_tab,world->longueur_tab);i++){
            if(sprites_collide(&(world->enemy[j]),world->wall[i])){
                world->enemy[j].x = world->enemy[j].x - 2;
                if(sprites_collide(&(world->enemy[j]),world->wall[i])){
                    world->enemy[j].x = world->enemy[j].x + 4;
                }else if(sprites_collide(&(world->enemy[j]),world->wall[i])){
                    world->enemy[j].y = world->enemy[j].y - 10;
                    if(sprites_collide(&(world->enemy[j]),world->wall[i])){
                        world->enemy[j].y = world->enemy[j].y + 10;
                    }
                }
            }
        }
    }    
}

void mouvementEnemy(world_t *world){
    for(int i = 0 ; i < world->nb_enemy ; i++){
        for(int j = 0 ; j < 513 ; j++){
            for(int z = 0 ; z < world->nb_point_ligne[j]; z++){
                if(sprites_collide_ligne(world->enemy[i], world->ligne[j][z])){
                    printf("%d",world->enemy[i].ishitting);
                    if((float)(SDL_GetTicks()/1000.)- world->compteur_debut2 > 2.0){
                        printf("truc : %f\n\n",(float)(SDL_GetTicks()/1000.)- world->compteur_debut2);
                        world->enemy[i].ishitting=false;
                    }
                    printf("%d",world->enemy[i].ishitting);
                    if(world->enemy[i].ishitting==false){
                        world->enemy[i].findPlayer = true ;
                    }else{
                        world->enemy[i].findPlayer = false;
                    }
                }
            }
        }        
    }
    
}

void position(world_t *world,int numero_enemy){
    if(world->enemy[numero_enemy].findPlayer){
        if(world->enemy[numero_enemy].y > world->player->y){
            world->enemy[numero_enemy].y = world->enemy[numero_enemy].y - MOVING_ENEMY;
        }else if(world->enemy[numero_enemy].y < world->player->y){
            world->enemy[numero_enemy].y = world->enemy[numero_enemy].y + MOVING_ENEMY;
        }
        if(world->enemy[numero_enemy].x > world->player->x){
            world->enemy[numero_enemy].x = world->enemy[numero_enemy].x - MOVING_ENEMY ;
        }else if(world->enemy[numero_enemy].x < world->player->x){
            world->enemy[numero_enemy].x = world->enemy[numero_enemy].x + MOVING_ENEMY ;
        }
    }

}

void update_data(world_t *world){

    for(int i=0;i<nb_murs(world->tab,world->hauteur_tab,world->longueur_tab);i++){
        handle_sprites_collision(world->player,world->wall[i],world);
    }
    float angle = world->angle ;
    float mid_angle = 0 ;
    
    world->nb_bandes_sortie=0;
    for (int i = 0; i < 513; i++)
    {
        ligne(world, angle, i) ;
        angle = angle + POV/513;//0.15
        if(i == 256){
            mid_angle = angle ;
        }
    }

    for(int i = 0; i < world->nb_key ; i++){
        if(sprites_collide(world->player, world->key[i])){
            world->key[i].x = -50 ;
            world->key[i].y = -50 ;
            world->nb_key_recup++ ;
            setIsLooking(world,i,0);
        }
    }

    enemyAttack(world) ;
    mouvementEnemy(world) ;
    enemyCollision(world) ;
    for(int i = 0 ; i < world->nb_enemy ; i++){
        position(world, i) ;
    }
    if(world->attack == 1 ){
        for(int i = 240 ; i < 280 ; i++){
            for(int j = 8; j < 40 ; j++){
                for(int z = 0 ; z < world->nb_enemy ; z++){
                    if(sprites_collide_ligne(world->enemy[z], world->ligne[i][j])){
                        world->enemy[z].x = -50 ;
                        world->enemy[z].y = -50 ;
                        setIsLooking2(world,z,0);
                        world->enemy[z].findPlayer = false ;
                        world->compteur_score = world->compteur_score + 50 ;
                    }
                }
            }

        }
    }



    if(two_sprites_collide(world->player, world->exit)){
        if(world->nb_key_recup == world->nb_key){
            world->etat_menu = 0 ;
        }else{
            handle_two_sprites_collision(world->player, world->exit, world) ;
        }
    }
    angle = mid_angle + 90;
    ligne(world, angle, 513) ;
    angle = mid_angle + 180 ;
    ligne(world,angle, 514) ;
    angle = mid_angle + 270 ;
    ligne(world,angle,515) ;


}

int is_game_over(world_t *world){
    return world->gameover;
}

int is_looking(world_t* world, sprite_t sprite){
    for(int i=0;i<513;i++){
        for(int j=0;j<world->nb_point_ligne[i];j++){
            int is_looking=sprites_collide_ligne(world->ligne[i][j], sprite);
            if(is_looking==1){
                return 1;
            }
        }
    }
    return 0;
}

void setIsLooking(world_t* world,int numero_clef,int valeur){
    world->key[numero_clef].is_looking_for=valeur;
}

void setIsLooking2(world_t* world,int numero_enemy,int valeur){
    world->enemy[numero_enemy].is_looking_for=valeur;
}

void ligne(world_t* world,float player_a, int numero_ligne){
    float angle_radian = player_a*PI/180;
    float cx = world->player->x ;
    float cy = world->player->y ;
    int is_over = 0 ;
    int incr=0;
    float vcos = cos(angle_radian);
    float vsin = sin(angle_radian);

    while(is_over != 1){
        cx = world->player->x + incr*vcos +PLAYER_WIDTH/2 ;
        cy = world->player->y + incr*vsin +PLAYER_HEIGHT/2 ;
        
        init_sprite(&(world->ligne[numero_ligne][incr]),cx, cy, 1, 1,0);
        for(int i =0 ; i < world->nb_mur; i++){
            if (sprites_collide_ligne(world->ligne[numero_ligne][incr], world->wall[i])){
                is_over = 1 ;
            }
        }    

        if(sprites_collide(world->exit, world->ligne[numero_ligne][incr])){
            is_over = 1; 
            if(world->nb_bandes_sortie == 0){
                world->no_ligne_db_sortie=numero_ligne;
                //printf("%d   %d\n",world->no_ligne_db_sortie,numero_ligne*2);
                
                
            }printf("%d  %d\n",world->nb_bandes_sortie,world->no_ligne_db_sortie);
            world->nb_bandes_sortie++;
        }


        int a=0;
            if(world->nb_key > world->nb_enemy){
                for(int t=0;t<world->nb_key;t++){
                    if(numero_ligne<513){
                        if (sprites_collide_ligne(world->ligne[numero_ligne][incr], world->key[t])){
                            world->key[t].placement_x=numero_ligne;//numero_ligne;
                            world->key[t].placement_y=incr;//incr;
                            world->key[t].is_looking_for=1;
                        }
                        if(a<world->nb_enemy){
                            if (sprites_collide_ligne(world->ligne[numero_ligne][incr], world->enemy[a])){
                                world->enemy[a].placement_x=numero_ligne;//numero_ligne;
                                world->enemy[a].placement_y=incr;//incr;
                                world->enemy[a].is_looking_for=1;
                            }
                        }
                        
                    }
                    a++;
                }
                
            }else{
                for(int t=0;t<world->nb_enemy;t++){
                    if(numero_ligne<513){
                        if(a<world->nb_key){
                            if (sprites_collide_ligne(world->ligne[numero_ligne][incr], world->key[a])){
                                
                                world->key[a].placement_x=numero_ligne;//numero_ligne;
                                world->key[a].placement_y=incr;//incr;
                                world->key[a].is_looking_for=1;
                            }
                        }
                        
                        if (sprites_collide_ligne(world->ligne[numero_ligne][incr], world->enemy[t])){
                            world->enemy[t].placement_x=numero_ligne;//numero_ligne;
                            world->enemy[t].placement_y=incr;//incr;
                            world->enemy[t].is_looking_for=1;
                        }
                    }
                    a++;
                }
            }
        
        incr++ ;
    }
    world->nb_point_ligne[numero_ligne] = incr ;  

    
}

void top5(score_t score, world_t* world){
    int top5 = 0, top4 = 0, top3 = 0, top2 = 0, top1 = 0;
    int transition = 0 ;
    while (!is_empty(score)) {
        if(top5 < score->nombre){
            top5 = score->nombre ;
        }
        if(top4 < top5){
            transition = top4 ;
            top4 = top5 ;
            top5 = transition ; 
        }
        if(top3 < top4){
            transition = top3 ;
            top3 = top4 ;
            top4 = transition ; 
        }if(top2 < top3){
            transition = top2 ;
            top2 = top3 ;
            top3 = transition ; 
        }
        if(top1 < top2){
            transition = top1 ;
            top1 = top2 ;
            top2 = transition ; 
        }
        score = suivant(score) ;
    }
    world->top[0] = top1 ;
    world->top[1] = top2 ;
    world->top[2] = top3 ;
    world->top[3] = top4 ;
    world->top[4] = top5 ;

    
}

void scorefin(world_t* world){
    world->score = ajouter_score(world->compteur_score, world->score) ;

    FILE *fichier ;
    fichier = fopen("score.txt", "w") ;
    if(fichier != NULL){
        while(!is_empty(world->score)){
            fprintf(fichier, "%d* \n", world->score->nombre);
            world->score =suivant(world->score) ;
        }
        fclose(fichier) ;
    }


}



    


