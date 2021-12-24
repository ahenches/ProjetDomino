#include "vue.h"


void affiche_plateau_triminos()
{
	POINT p1, p2;
	int i, j;
	
	rempli_ecran(beige);
	
	p1.x = BORDURE; p1.y = 10; 
	p2.x = p1.x + LARGEUR_MAIN ; p2.y = p1.y + HAUTEUR_MAIN;
	dessine_rectangle_plein(p1,p2, noir);
	
	p1.x = p2.x + 10; 
	p2.x = p1.x + LARGEUR_PIOCHE ; 
	dessine_rectangle_plein(p1,p2, gris);
	
	p1.x = BORDURE; p1.y = 20 + HAUTEUR_MAIN; 
	p2.x = p1.x + LARGEUR_PLATEAU ; p2.y= p1.y + HAUTEUR_PLATEAU;
	
	dessine_rectangle_plein(p1, p2, blanc);
	
	actualise_affichage();
	
	
}
