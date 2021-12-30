#include "vue.h"
#include "modele.h"
#include "controleur.h"
#include "../lib/lib.h"


void affiche_plateau_triminos()
{
	POINT p1, p2;
	int i, j;
	
	rempli_ecran(bleuclair);
	
	//Affiche main
	p1.x = BORDURE; p1.y = 10; 
	p2.x = p1.x + LARGEUR_MAIN ; p2.y = p1.y + HAUTEUR_MAIN;
	dessine_rectangle_plein(p1,p2, lightgrey);
	dessine_rectangle(p1,p2,gris);
	
	//Affiche pioche
	p1.x = p2.x + 10; 
	p2.x = p1.x + LARGEUR_PIOCHE ; 
	dessine_rectangle_plein(p1,p2, lightgrey);	
	dessine_rectangle(p1,p2,gris);

	//Affiche plateau
	p1.x = BORDURE; p1.y = 20 + HAUTEUR_MAIN; 
	p2.x = p1.x + LARGEUR_PLATEAU ; p2.y= p1.y + HAUTEUR_PLATEAU;
	dessine_rectangle_plein(p1, p2, blanc);
	dessine_rectangle(p1,p2,gris);
	
	
	//actualise_affichage();
	p1.x = BORDURE + 10; p1.y = HAUTEUR_MAIN; 
	char texte[25] = "Main";
	//affiche_texte(texte, 12, p1, noir);
	
	//test_texte();
	
	// permet d afficher le quadrillage dans le plateau 
	//~ p1.x = 20; p1.y = 820;
	//~ p2.x = 1280; p2.y = 820;
	//~ for (i=0 ; i< 14; i++)
	//~ {
		//~ dessine_ligne(p1,p2,gris);
		//~ p1.y -=50;
		//~ p2.y -=50;
	//~ }
	
	//~ p1.x = 20; p1.y = 820;
	//~ p2.x = 20; p2.y = 120;
	//~ for (i=0 ; i< 42; i++)
	//~ {
		//~ dessine_ligne(p1,p2,gris);
		//~ p1.x +=30;
		//~ p2.x +=30;
	//~ }
	actualise_affichage();	
}



void affiche_triomino(CASE caseP, EMPLACEMENT emp)
{
	POINT pointe, pGauche, pDroit;
	if (caseP.l%2 == 0 && caseP.c%2== 0) //triangle avec pointe vers le haut
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseP.c); pointe.y = 820 - (HAUTEUR_TUILE * caseP.l);
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y - HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y - HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,beige);
		dessine_triangle(pointe,pGauche,pDroit,noir);
		
		//placement des nombres
	}
	else //triangle avec pointe vers le bas 
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseP.c); pointe.y = 820 - (HAUTEUR_TUILE * (caseP.l+1));
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y + HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y + HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,beige);
		dessine_triangle(pointe,pGauche,pDroit,noir);
		
		//placement des nombres
	}	
	actualise_affichage();
}

void affiche_emplacement_possible_triominos(CASE caseP)
{
	POINT pointe, pGauche, pDroit;
	
	if (caseP.l%2 == 0 && caseP.c%2== 0) //triangle avec pointe vers le haut
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseP.c); pointe.y = 820 - (HAUTEUR_TUILE * caseP.l);
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y - HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y - HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,orange);
	}
	else //triangle avec pointe vers le bas 
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseP.c); pointe.y = 820 - (HAUTEUR_TUILE * (caseP.l+1));
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y + HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y + HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,orange);
	}	
	
	actualise_affichage();
}

void efface_main_triominos()
{
	POINT p1,p2;
	
	p1.x = BORDURE + 1 ; p1.y = 11 ;
	p2.x = BORDURE + LARGEUR_MAIN -1 ; p2.y = HAUTEUR_TUILE + 22 ;
	dessine_rectangle_plein(p1,p2,lightgrey);
}

void actualise_pioche_triominos(int nbPioche)
{
	POINT p1,p2;
	
	p1.x = BORDURE + LARGEUR_MAIN + 11 ; p1.y = 11 ;
	p2.x = p1.x + LARGEUR_PIOCHE -2 ; p2.y = HAUTEUR_MAIN - 22 ;
	dessine_rectangle_plein(p1, p2, lightgrey);
	//affiche le nouveau score
}

void affiche_main_triominos(TRIOMINO mainJoueur[]) // main joueur contient au max 15 tuiles
{
	POINT pointe, pGauche, pDroit;
	
	efface_main_triominos();
	pointe.x = BORDURE + 5 + LARGEUR_TUILE/2; pointe.y = BORDURE + HAUTEUR_TUILE;
	pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y - HAUTEUR_TUILE;
	pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pGauche.y;

	for (int i = 0; i<15 ; i++)
	{
		dessine_triangle_plein(pointe,pGauche,pDroit,beige);
		dessine_triangle(pointe,pGauche,pDroit,noir);	
		pointe.x += LARGEUR_TUILE + 10; 
		pGauche.x += LARGEUR_TUILE + 10; 
		pDroit.x += LARGEUR_TUILE + 10;	
	}
}

