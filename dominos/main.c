#include "main.h"
#include "modele.h"
#include "controleur.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                             		   fonction main                	                //
//////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// début de la session graphique
	ouvre_fenetre(RESH_FENETRE, RESV_FENETRE);

	NB_JOUEURS nbJoueurs;
	JOUEUR tabJoueurs[TOT_JOUEURS];
	nbJoueurs = entre_nb_joueurs(nbJoueurs);
	entre_pseudos(tabJoueurs, nbJoueurs);
	main_dominos(tabJoueurs,nbJoueurs);

	attend_clic();
	ferme_fenetre();

	return 0;
}
