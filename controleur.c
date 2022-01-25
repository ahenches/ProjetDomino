#include <stdio.h>
#include "lib/lib.h"
#include "vue.h"
#include "triominos/controleur.h"

int main()
{

	ouvre_fenetre(1300, 900);

	//main_triominos();
	affiche_menu_accueil();
	actualise_affichage();
	attend_clic();

	attend_clic();

	return 0;
}
