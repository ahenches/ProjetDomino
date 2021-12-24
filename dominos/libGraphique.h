#ifndef LIBGRAPHIQUE_H
#define LIBGRAPHIQUE_H


#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include <time.h>

typedef struct NB_JOUEURS
{
	int nbJoueurHumain; // Nombre de joueur humain
	int nbJoueurIA; // Nombre de joueur IA
}NB_JOUEURS;

typedef struct POINT
{
	int x;
	int y;
}POINT;

typedef enum BOOL{
	FAUX, VRAI
} BOOL;

void init_fenetre(int largeur, int hauteur);
void ferme_fenetre();
void _teste_arret();
void actualise();
POINT attendre_clic();
void ferme_fenetre();
void affiche_image(char *nom, POINT coin);


#endif