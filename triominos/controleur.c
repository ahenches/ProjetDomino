#include <stdio.h>
#include "../lib/lib.h"
#include "controleur.h"
#include "vue.h"
#include "modele.h"



int main_triominos()
{
	TRIOMINO trio1;
	POINT clic;
	trio1.min = 1; trio1.sec = 2; trio1.der = 3;
	EMPLACEMENT emp;
	emp.trio = trio1;
	emp.pointe = 's';
	
	CASE case1;
	case1.l = 6; case1.c = 20;

	TRIOMINO mainJ1 [15];
	for(int i=0; i<14;i++)
	{
		mainJ1[i] = trio1;
	}
	
	affiche_plateau_triminos();
	clic = attend_clic();
	
	//test affichage plateau
	//~ affiche_triomino(case1,emp);
	//~ case1.l = 7;
	//~ affiche_triomino(case1,emp);
	
	//~ case1.l = 6; case1.c = 19;
	//~ affiche_triomino(case1,emp);
	
	//~ case1.l = 6; case1.c = 18;
	//~ affiche_emplacement_possible_triominos(case1);
	
	//~ case1.l = 6; case1.c = 18;
	//~ affiche_triomino(case1,emp);
	
	//~ affiche_main_triominos(mainJ1);
	
	//~ actualise_affichage();
	//~ attend_clic();
	
	//~ efface_main_triominos();
	
	//~ actualise_pioche_triominos(0);
	
	//~ actualise_affichage();
	
	//test les fonction verifie clic
	//~ for (int i=0; i<5;i++)
	//~ {
		//~ if (clic_dans_main_triominos(clic))
		//~ printf("main ok\n");
		
		//~ if(clic_dans_pioche_triominos(clic)) 
		//~ printf("pioche ok\n");
		
		//~ if(clic_dans_plateau_triominos(clic)) 
		//~ printf("plateau ok\n");
		//~ clic=attend_clic();
	//~ }
	
	//test transforme point en case
	//~ for(int j=0; j<5;j++)
	//~ {
		//~ case1 = transforme_point_en_case(attend_clic());
		//~ printf("l : %d  c : %d  \n",case1.l, case1.c);
	//~ }
	
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

//précondition le clic doit etre dans le plateau
CASE transforme_point_en_case(POINT clic)
{
	CASE caseClic;
	caseClic.l = (HAUTEUR_PLATEAU - (clic.y - (BORDURE + HAUTEUR_MAIN))) / HAUTEUR_TUILE;
	caseClic.c = (clic.x -BORDURE) / (LARGEUR_TUILE / 2);
	return caseClic;
}
