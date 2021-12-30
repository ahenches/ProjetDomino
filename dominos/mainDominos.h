#ifndef MAINDOMINOS_H
#define MAINDOMINOS_H

typedef enum ORIENTATION
{
	HORIZONTALE, VERTICALE, RIEN
}ORIENTATION;


typedef struct DOMINO
{
	int valeur1; // Valeur Bas ou Gauche du domino
	int valeur2; // Valeur Haut ou Droite du domino
	ORIENTATION orientation;
}DOMINO;

typedef struct NB_JOUEURS
{
	int nbJoueurHumain; // Nombre de joueur humain
	int nbJoueurIA; // Nombre de joueur IA
}NB_JOUEURS;



void main_dominos(NB_JOUEURS joueurs, char* tabPseudo[]);
void affiche_domino();
void initialise_plateau();
void affiche_plateau();
void genere_pioche();
int determine_nb_dominos_main(int totJoueur);
void distribue_premiers_dominos(int totJoueur);
DOMINO prend_domino_pour_distribue();
void affiche_mains(int totJoueur);
void affiche_pioche();
void affiche_pseudos(char* tabPseudo[]);
#endif