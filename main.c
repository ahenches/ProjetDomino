#include <stdio.h>
#include "lib/lib.h"
#include "triominos/vue.h"

BOOL clic_dans_main_triominos(POINT clic);
BOOL clic_dans_pioche_triominos(POINT clic);
BOOL clic_dans_plateau_triominos(POINT clic);


int main() {
	TRIOMINO trio1;
	trio1.premier = 1; trio1.second = 2; trio1.dernier = 3;
	EMPLACEMENT emp;
	emp.triomino = trio1;
	emp.pointe = 's';
	
	CASE case1;
	case1.l = 6; case1.c = 20;

	TRIOMINO mainJ1 [15];
	for(int i=0; i<14;i++)
	{
		mainJ1[i] = trio1;
	}
	
	ouvre_fenetre(1300,900);
	affiche_plateau_triminos();
	attend_clic();
	
	affiche_triomino(case1,emp);
	case1.l = 7;
	affiche_triomino(case1,emp);
	
	case1.l = 6; case1.c = 19;
	affiche_triomino(case1,emp);
	
	case1.l = 6; case1.c = 18;
	affiche_emplacement_possible_triominos(case1);
	
	case1.l = 6; case1.c = 18;
	affiche_triomino(case1,emp);
	
	affiche_main_triominos(mainJ1);
	
	actualise_affichage();
	attend_clic();
	
	efface_main_triominos();
	
	actualise_pioche_triominos(0);
	
	actualise_affichage();
	attend_clic();
	
	return 0;
}


BOOL clic_dans_main_triominos(POINT clic)
{
	if(clic.x > BORDURE && clic.x < BORDURE + LARGEUR_MAIN)
		if (clic.y > 10 && clic.y < 10 + HAUTEUR_MAIN )
			return TRUE;	
	return FALSE;
}

BOOL clic_dans_pioche_triominos(POINT clic)
{
	if(clic.x > BORDURE+LARGEUR_MAIN+10 && clic.x < BORDURE+LARGEUR_MAIN+LARGEUR_PIOCHE+10)
		if (clic.y > 10 && clic.y < 10 + HAUTEUR_MAIN )
			return TRUE;	
	return FALSE;
}

BOOL clic_dans_plateau_triominos(POINT clic)
{
	if(clic.x > BORDURE && clic.x < BORDURE+LARGEUR_PLATEAU)
		if (clic.y > BORDURE + HAUTEUR_MAIN && clic.y < BORDURE + HAUTEUR_MAIN + HAUTEUR_PLATEAU)
			return TRUE;	
	return FALSE;
}
