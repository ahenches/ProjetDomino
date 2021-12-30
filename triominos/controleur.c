#include <stdio.h>
#include "../lib/lib.h"
#include "controleur.h"
#include "vue.h"
#include "modele.h"



int main_triominos()
{

	main_second();

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
CASE transforme_point_en_case_triominos(POINT clic)
{
	CASE caseClic;

	caseClic.l = (HAUTEUR_PLATEAU - (clic.y - (BORDURE + HAUTEUR_MAIN))) / HAUTEUR_TUILE;
	caseClic.c = (clic.x -BORDURE) / (LARGEUR_TUILE / 2);

	return caseClic;
}

//precondition le clic doit etre dans la main
TRIOMINO transforme_selection_en_triominos(POINT clic, MAIN_TRIOMINOS mainJoueurCourant)
{
	TRIOMINO trioSelectionne;
	int indice;

	indice = (clic.x - BORDURE) / (LARGEUR_TUILE + 10);
	trioSelectionne = mainJoueurCourant.tab[indice];

	return trioSelectionne;
}
