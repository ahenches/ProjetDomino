#ifndef DOMINOS_H
#define DOMINOS_H

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

// headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/lib.h"

// defines
#define TAILLE_TAB_DOMINOS 28 // 28 dominos en longueur ou largeur
#define RESH_FENETRE 600
#define RESV_FENETRE 626
#define TOT_JOUEURS 4
#define SDL_TTF_OK // police

// Structures et enums
typedef enum ORIENTATION
{
	HORIZONTALE,
	VERTICALE,
	RIEN
} ORIENTATION;

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

// variables globales
extern DOMINO plateau[TAILLE_TAB_DOMINOS][TAILLE_TAB_DOMINOS]; // Plateau de jeu
extern DOMINO pioche[TAILLE_TAB_DOMINOS];
extern DOMINO mainJoueurs[4][7];

// Prototype Contôleur
void main_dominos(NB_JOUEURS joueurs, char *tabPseudos[]);

// Prototypes Modèle
void initialise_plateau();
NB_JOUEURS entre_nb_joueurs(NB_JOUEURS joueurs);
void entre_pseudos(char *tabPseudos[], NB_JOUEURS joueurs);
void genere_pioche();
int determine_nb_dominos_main(int totJoueur);
void distribue_premiers_dominos(int totJoueur);
DOMINO prend_domino_pour_distribue();
int compte_double_pioche();
int est_double(DOMINO domino);
void definit_premier_joueur(char *tabPseudos[], int nbDominosMain);
int determine_joueur_suivant(int tour, int totJoueur, char *tabPseudos[]);
DOMINO recupere_choix_domino_main(DOMINO mainActive[]);

// Prototypes Vue
void affiche_domino();
void affiche_plateau();
void affiche_mains(int totJoueur, char *tabPseudos[]);
void affiche_pioche();
void affiche_pseudos(char *tabPseudos[], int totJoueur);

#endif