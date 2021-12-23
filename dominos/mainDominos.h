#ifndef MAINDOMINOS_H
#define MAINDOMINOS_H

#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>

typedef enum ORIENTATION
{
	HAUT, DROITE, BAS, GAUCHE, RIEN
}ORIENTATION;

typedef enum BOOL{
	FAUX, VRAI
} BOOL;


typedef struct DOMINO
{
	int valeur1; // Valeur Bas ou Gauche du domino
	int valeur2; // Valeur Haut ou Droite du domino
	ORIENTATION orientation;
}DOMINO;

typedef struct POINT
{
	int x;
	int y;
}POINT;



void affiche_domino();
void init_fenetre(int largeur, int hauteur);
void ferme_fenetre();
void _teste_arret();
void actualise();
void initialise_plateau();
void affiche_plateau();
POINT attendre_clic();
void ferme_fenetre();



#endif