#include "vue.h"
#include "../lib/lib.h"


void affiche_plateau_triminos()
{
	POINT p1, p2;
	int i, j;
	
	rempli_ecran(bleuclair);
	
	p1.x = BORDURE; p1.y = 10; 
	p2.x = p1.x + LARGEUR_MAIN ; p2.y = p1.y + HAUTEUR_MAIN;
	dessine_rectangle_plein(p1,p2, lightgrey);
	dessine_rectangle(p1,p2,gris);
	
	p1.x = p2.x + 10; 
	p2.x = p1.x + LARGEUR_PIOCHE ; 
	dessine_rectangle_plein(p1,p2, lightgrey);	
	dessine_rectangle(p1,p2,gris);

	
	p1.x = BORDURE; p1.y = 20 + HAUTEUR_MAIN; 
	p2.x = p1.x + LARGEUR_PLATEAU ; p2.y= p1.y + HAUTEUR_PLATEAU;
	dessine_rectangle_plein(p1, p2, blanc);
	dessine_rectangle(p1,p2,gris);
	//actualise_affichage();
	//p1.x = BORDURE + 10; p1.y = HAUTEUR_MAIN; 
	//affiche_texte("Main", 12, p1, noir);
	
	//test_texte();
	p1.x = 20; p1.y = 820;
	p2.x = 1280; p2.y = 820;
	for (i=0 ; i< 14; i++)
	{
		dessine_ligne(p1,p2,gris);
		p1.y -=50;
		p2.y -=50;
	}
	
	p1.x = 20; p1.y = 820;
	p2.x = 20; p2.y = 120;
	for (i=0 ; i< 42; i++)
	{
		dessine_ligne(p1,p2,gris);
		p1.x +=30;
		p2.x +=30;
	}
	actualise_affichage();	
}



void affiche_triomino(int l, int c, EMPLACEMENT emp)
{
	POINT pointe, pGauche, pDroit;
	if (l%2 == 0 && c%2== 0) //triangle avec pointe vers le haut
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * c); pointe.y = 820 - (HAUTEUR_TUILE * l);
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y - HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y - HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,beige);
		dessine_triangle(pointe,pGauche,pDroit,noir);
		
		//placement des nombres
	}
	else //triangle avec pointe vers le bas 
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * c); pointe.y = 820 - (HAUTEUR_TUILE * (l+1));
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y + HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y + HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,beige);
		dessine_triangle(pointe,pGauche,pDroit,noir);
		
		//placement des nombres
	}	
	actualise_affichage();
}

void affich_emplacement_possible()
{
	
}
