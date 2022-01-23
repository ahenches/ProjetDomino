#include "dominos.h"
#include "modele.h"
#include "controleur.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                             		   fonction main                	                //
//////////////////////////////////////////////////////////////////////////////////////////

// variables globales
DOMINO plateau[TAILLE_TAB_DOMINOS][TAILLE_TAB_DOMINOS]; // Plateau de jeu, [ligne][colonne]
DOMINO pioche[TAILLE_TAB_DOMINOS];

int main(int argc, char *argv[])
{
	// début de la session graphique
	ouvre_fenetre(RESH_FENETRE, RESV_FENETRE);

	NB_JOUEURS nbJoueurs;
	JOUEUR mains_joueurs[TOT_JOUEURS];
	nbJoueurs = entre_nb_joueurs(nbJoueurs);
	entre_pseudos(mains_joueurs, nbJoueurs);
	main_dominos(mains_joueurs, nbJoueurs);

	attend_clic();
	ferme_fenetre();

	return 0;
}
