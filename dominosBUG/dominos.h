#ifndef DOMINOS_H
#define DOMINOS_H

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

// headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../lib/lib.h"

// defines
#define TAILLE_TAB_DOMINOS 28 // 28 dominos en longueur ou largeur
#define RESH_FENETRE 600
#define RESV_FENETRE 626
#define TOT_JOUEURS 4
#define NB_MAX_DOMINO_MAIN 21
#define SDL_TTF_OK // police
#define VRAI 1
#define FAUX 0

// Structures et enums
typedef enum ORIENTATION
{
	HORIZONTALE,
	VERTICALE,
	RIEN
} ORIENTATION;

typedef enum EXTREMITE_COMPATIBLE
{
	GAUCHE,
	DROITE,
	LES_DEUX,
	AUCUN,
} EXTREMITE_COMPATIBLE;

typedef struct DOMINO
{
	int valeur1; // Valeur Bas ou Gauche du domino
	int valeur2; // Valeur Haut ou Droite du domino
	ORIENTATION orientation;
} DOMINO;

typedef struct NB_JOUEURS
{
	int nbJoueurHumain; // Nombre de joueurs humains
	int nbJoueurIA;		// Nombre d'IA
} NB_JOUEURS;

typedef struct JOUEUR
{
	char pseudo[20];					   // pseudo du joueur
	DOMINO mainJoueur[NB_MAX_DOMINO_MAIN]; // main du joueur
	int score;							   // score du joueur
} JOUEUR;

typedef struct COORDONNEES
{
	int ligne;
	int colonne;
} COORDONNEES;

typedef struct AIDE_PLACEMENT // aide la fonction place_domino à placer ou non un domino et à quelle extrémité
{
	BOOL compatible;
	int extremite;

} AIDE_PLACEMENT;

// variables globales
extern DOMINO plateau[TAILLE_TAB_DOMINOS][TAILLE_TAB_DOMINOS]; // Plateau de jeu [ligne][colonne]
extern DOMINO pioche[TAILLE_TAB_DOMINOS];

#endif