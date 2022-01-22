#include "dominos.h"

// variables globales
DOMINO plateau[TAILLE_TAB_DOMINOS][TAILLE_TAB_DOMINOS]; // Plateau de jeu
DOMINO pioche[TAILLE_TAB_DOMINOS];
DOMINO mainJoueurs[4][7];

//////////////////////////////////////////////////////////////////////////////////////////
//                             		   fonction main                	                //
//////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// début de la session graphique
	ouvre_fenetre(RESH_FENETRE, RESV_FENETRE);

	NB_JOUEURS joueurs;
	char *tabPseudos[TOT_JOUEURS];

	joueurs = entre_nb_joueurs(joueurs);
	entre_pseudos(tabPseudos, joueurs);
	main_dominos(joueurs, tabPseudos);

	attend_clic();
	ferme_fenetre();

	return 0;
}
