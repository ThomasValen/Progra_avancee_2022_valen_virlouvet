#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"

int main(int argc, char *argv[])
{
    char** tab = allouer_tab_2D(5,6);
    afficher_tab_2D(tab,5,6);
}