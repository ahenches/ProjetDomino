#include "vue.h"


void affiche_plateau_triminos()
{
	POINT p1, p2;
	int i, j;
	
	rempli_ecran(beige);
	
	p1.x = 80; p1.y = 80; 
	p2.x = p1.x + LARG_PLATEAU_LARGE ; p2.y = p1.y + LARG_PLATEAU_LARGE; 
	draw_fill_rectangle(p1,p2,gris);
	
	for (i = 0; i < 8 ; i++)
	{
		p1.y = 90 + i * (LARG_CARRE_PLATEAU_LARGE + BORDURE_PLATEAU_LARGE);
		p2.y =(90 + LARG_CARRE_PLATEAU_LARGE)+ i*(LARG_CARRE_PLATEAU_LARGE + BORDURE_PLATEAU_LARGE);
		for (j = 0 ; j < 8 ; j++)
		{
			p1.x = 90 + j * (LARG_CARRE_PLATEAU_LARGE + BORDURE_PLATEAU_LARGE);
			p2.x =(90+LARG_CARRE_PLATEAU_LARGE)+j*(LARG_CARRE_PLATEAU_LARGE +BORDURE_PLATEAU_LARGE);
			draw_fill_rectangle(p1,p2,orange);			
		}		
	}	
	
