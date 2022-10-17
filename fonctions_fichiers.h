#ifndef __FONCTIONS_FICHIERS__H__
#define __FONCTIONS_FICHIERS__H__

char** allouer_tab_2D(int n, int m);

void desallouer_tab_2D(char** tab, int n);

void afficher_tab_2D(char** tab, int n, int m);

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);

char** lire_fichier(const char* nomFichier);

#endif
