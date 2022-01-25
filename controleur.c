#include <stdio.h>
#include "lib/lib.h"
#include "vue.h"
#include "triominos/controleur.h"

BOOL est_clic_sur_jouer_menu_accueil(POINT clic);

int main()
{
	POINT clic;
	ouvre_fenetre(1300, 900);

	//main_triominos();
	// affiche_menu_accueil();
	// actualise_affichage();
	// attend_clic();
	//
	// affiche_menu_nombre_joueurs();
	// actualise_affichage();
	// attend_clic();
	//
	// affiche_menu_pseudo(2);
	// actualise_affichage();
	// attend_clic();
	//
	// affiche_menu_choix_jeu();
	// actualise_affichage();
	// attend_clic();

	//On attend que l'utilisateur clique sur Jouer
	affiche_menu_accueil();
	actualise_affichage();
	do {
		clic = attend_clic();
	} while( !est_clic_sur_jouer_menu_accueil(clic) );

	//On affiche le menu du choix du nombre de joueurs
	affiche_menu_nombre_joueurs();
	actualise_affichage();





	attend_clic();

	return 0;
}


BOOL est_clic_sur_jouer_menu_accueil(POINT clic)
{
	if (clic.x > 450 && clic.x < 450+400 && clic.y < 500 && clic.y > 500-200 )
		return TRUE;
	else
		return FALSE;
}
