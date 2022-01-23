#include "../lib/lib.h"
#include "controleur.h"
#include "vue.h"
#include "modele.h"

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


	//Textes a afficher
	p1.x = BORDURE + 5; p1.y = HAUTEUR_MAIN + 5;
	affiche_texte("Main", 18, p1, noir);

	p1.x += LARGEUR_MAIN + 10;
	affiche_texte("Pioche", 18, p1, noir);

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
}

void affiche_triomino(CASE caseP, EMPLACEMENT emp)
{
	POINT pointe, pGauche, pDroit;

	//triangle avec pointe vers le haut
	if ((caseP.l%2 == 0 && caseP.c%2== 0) || (caseP.l%2 == 1 && caseP.c%2== 1))
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseP.c); pointe.y = 820 - (HAUTEUR_TUILE * caseP.l);
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y - HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y - HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,beige);
		dessine_triangle(pointe,pGauche,pDroit,noir);

		//Affichage des nombres
		pointe.x -= 4; pointe.y -= 12;
		pGauche.x += 10; pGauche.y += 19;
		pDroit.x -= 19; pDroit.y +=19;

		switch (emp.pointe)
		{
			case 'm':
				affiche_entier(emp.trio.min,10, pointe, noir);
				affiche_entier(emp.trio.sec,10, pDroit, noir);
				affiche_entier(emp.trio.der,10, pGauche, noir);
				break;
			case 's' :
				affiche_entier(emp.trio.sec,10, pointe, noir);
				affiche_entier(emp.trio.der,10, pDroit, noir);
				affiche_entier(emp.trio.min,10, pGauche, noir);
				break;
			default :
				affiche_entier(emp.trio.der,10, pointe, noir);
				affiche_entier(emp.trio.min,10, pDroit, noir);
				affiche_entier(emp.trio.sec,10, pGauche, noir);
		}
	}

	//triangle avec pointe vers le bas
	else
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseP.c); pointe.y = 820 - (HAUTEUR_TUILE * (caseP.l+1));
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y + HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y + HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,beige);
		dessine_triangle(pointe,pGauche,pDroit,noir);

		//Affichage des nombres
		pointe.x -= 4; pointe.y += 23;
		pGauche.x += 10; pGauche.y -= 4;
		pDroit.x -= 19; pDroit.y -= 4;

		switch (emp.pointe)
		{
			case 'm':
				affiche_entier(emp.trio.min,10, pointe, noir);
				affiche_entier(emp.trio.sec,10, pGauche, noir);
				affiche_entier(emp.trio.der,10, pDroit, noir);
				break;
			case 's' :
				affiche_entier(emp.trio.sec,10, pointe, noir);
				affiche_entier(emp.trio.der,10, pGauche, noir);
				affiche_entier(emp.trio.min,10, pDroit, noir);
				break;
			default :
				affiche_entier(emp.trio.der,10, pointe, noir);
				affiche_entier(emp.trio.min,10, pGauche, noir);
				affiche_entier(emp.trio.sec,10, pDroit, noir);
		}
	}
}

void affiche_emplacement_possible_triominos(CASE caseP)
{
	POINT pointe, pGauche, pDroit;

	//triangle avec pointe vers le haut
	if ((caseP.l%2 == 0 && caseP.c%2== 0) || (caseP.l%2 == 1 && caseP.c%2== 1))
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseP.c); pointe.y = 820 - (HAUTEUR_TUILE * caseP.l);
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y - HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y - HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,orange);
	}

	//triangle avec pointe vers le bas
	else
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseP.c); pointe.y = 820 - (HAUTEUR_TUILE * (caseP.l+1));
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y + HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; pDroit.y = pointe.y + HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,orange);
	}
}

void actualise_pioche_triominos(int nbPioche)
{
	POINT p1,p2;

	//Efface le nombre precedent
	p1.x = BORDURE + LARGEUR_MAIN + 11 ; p1.y = 11 ;
	p2.x = p1.x + LARGEUR_PIOCHE -2 ; p2.y = HAUTEUR_MAIN - 22 ;
	dessine_rectangle_plein(p1, p2, lightgrey);

	//Affiche le nouveau nombre
	p1.x = BORDURE + LARGEUR_MAIN + 90 ; p1.y = 75 ;
	affiche_entier(nbPioche, 35,p1, noir );
}

void efface_main_triominos()
{
	POINT p1,p2;

	//efface triominos de la main
	p1.x = BORDURE + 1 ; p1.y = 11 ;
	p2.x = BORDURE + LARGEUR_MAIN -1 ; p2.y = HAUTEUR_TUILE + 22 ;
	dessine_rectangle_plein(p1,p2,lightgrey);

	//efface nom du joueur
	p1.x += 75 ; p1.y = HAUTEUR_MAIN + 9 ;
	dessine_rectangle_plein(p1, p2, lightgrey);
}

void affiche_main_triominos(JOUEUR_TRIOMINOS joueur, int partieMain)
{
	POINT pointe,pointeN, pGauche, pGaucheN, pDroit, pDroitN;

	efface_main_triominos();
	affiche_joueur_main_triominos(joueur);

	pointe.x = BORDURE + 5 + LARGEUR_TUILE/2; pointe.y = BORDURE + HAUTEUR_TUILE;
	pGauche.x = pointe.x - LARGEUR_TUILE/2;	pGauche.y = pointe.y - HAUTEUR_TUILE;
	pDroit.x = pointe.x + LARGEUR_TUILE/2; 	pDroit.y = pGauche.y;

	for (int i = 0 + partieMain*14; i < 14 + partieMain*14 ; i++)
	{
		if (joueur.mainJoueur.taille > i)
		{
			dessine_triangle_plein(pointe,pGauche,pDroit,beige);
			dessine_triangle(pointe,pGauche,pDroit,noir);

			//Affichage des nombres
			pointeN.x = pointe.x - 4; 		pointeN.y = pointe.y - 12;
			pGaucheN.x = pGauche.x + 10; 	pGaucheN.y = pGauche.y + 19;
			pDroitN.x = pDroit.x - 19; 		pDroitN.y = pDroit.y + 19;

			affiche_entier(joueur.mainJoueur.tab[i].min,10, pointeN, noir);
			affiche_entier(joueur.mainJoueur.tab[i].sec,10, pDroitN, noir);
			affiche_entier(joueur.mainJoueur.tab[i].der,10, pGaucheN, noir);
		}

		pointe.x += LARGEUR_TUILE + 10;
		pGauche.x += LARGEUR_TUILE + 10;
		pDroit.x += LARGEUR_TUILE + 10;
	}

	//Affichage de la flèche de navigation
	if (partieMain == DEBUT_MAIN)
	{
		pointe.x -= LARGEUR_TUILE/2 - 10; //pointe.y = ;
		pGauche.x = pointe.x ; pGauche.y += 5;
		pDroit.x -= 10; pDroit.y += HAUTEUR_TUILE/2 +2;
		dessine_triangle_plein(pointe, pDroit, pGauche, rouge);
	}
	else{
		pointe.x += LARGEUR_TUILE/2 - 10; //pointe.y = ;
		pGauche.x += 10 ; pGauche.y += HAUTEUR_TUILE/2 +2;
		pDroit.x = pointe.x ; pDroit.y += 5;
		dessine_triangle_plein(pGauche,  pointe,pDroit, rouge);
	}

	dessine_triangle(pointe, pGauche, pDroit, noir);

}

void affiche_joueurs_triominos(int nbJoueurs, JOUEUR_TRIOMINOS joueurs[])
{
	POINT p1, p2;
	int i;

	p1.x = BORDURE; p1.y = 870;

	for (i = 0; i< nbJoueurs; i++)
	{
		affiche_texte(joueurs[i].pseudo, 20, p1, noir);
		p1.x += 260;
	}

	p1.x = 255; 	p1.y = 885;
	p2.x = p1.x; 	p2.y = p1.y - 50;

	for (i = 0; i< nbJoueurs - 1; i++)
	{
		dessine_ligne(p1, p2, noir);
		p1.x += 260;
		p2.x += 260;
	}
}

void actualise_score_triominos(int nbJoueurs, JOUEUR_TRIOMINOS joueurs[])
{
	POINT p1, p2;
	int i;

	p1.x = 195; 		p1.y = 875;
	p2.x = p1.x + 58; 	p2.y = p1.y - 30;

	for (i = 0; i< nbJoueurs; i++)
	{
		dessine_rectangle_plein(p1,p2, bleuclair);
		p1.x += 260;
		p2.x += 260;
	}

	p1.x = 200; p1.y = 870;

	for (i = 0; i< nbJoueurs; i++)
	{
		affiche_entier(joueurs[i].score, 20, p1, noir);
		p1.x += 260;
	}
}

void affiche_joueur_main_triominos(JOUEUR_TRIOMINOS joueur)
{
	POINT p1;

	p1.x = BORDURE + 80; p1.y = HAUTEUR_MAIN + 5;
	affiche_texte(joueur.pseudo, 20, p1, noir);
}

void affiche_selection_main_triominos(int trioSelect)
{
	POINT pointe, pDroit, pGauche;

	pointe.x = BORDURE + 5 + (LARGEUR_TUILE/2) + (trioSelect * 70);
	pointe.y = BORDURE + HAUTEUR_TUILE + 1;
	pGauche.x = BORDURE + 4 + (trioSelect * 70);
	pGauche.y = BORDURE - 1;
	pDroit.x = pGauche.x + LARGEUR_TUILE + 2 ;
	pDroit.y = pGauche.y;

	dessine_triangle(pointe, pGauche, pDroit, red);

	pointe.y += 1;
	pGauche.x -= 1; pGauche.y -= 1;
	pDroit.x += 1; pDroit.y = pGauche.y ;
	dessine_triangle(pointe, pGauche, pDroit, red);
}

void efface_selection_main_triominos(int trioDeselect)
{
	POINT pointe, pDroit, pGauche;

	pointe.x = BORDURE + 5 + (LARGEUR_TUILE/2) + (trioDeselect * 70);
	pointe.y = BORDURE + HAUTEUR_TUILE + 1;
	pGauche.x = BORDURE + 4 + (trioDeselect * 70);
	pGauche.y = BORDURE - 1;
	pDroit.x = pGauche.x + LARGEUR_TUILE + 2 ;
	pDroit.y = pGauche.y;

	dessine_triangle(pointe, pGauche, pDroit, lightgrey);

	pointe.y += 1;
	pGauche.x -= 1; 	pGauche.y -= 1;
	pDroit.x += 1; 		pDroit.y = pGauche.y ;
	dessine_triangle(pointe, pGauche, pDroit, lightgrey);

	pointe.y -= 2;
	pGauche.x += 2; pGauche.y += 2;
	pDroit.x -= 2; 	pDroit.y = pGauche.y ;
	dessine_triangle(pointe, pGauche, pDroit, noir);
}

void affiche_selection_emplacement_triominos(CASE caseS)
{
	POINT pointe, pGauche, pDroit;

	//triangle avec pointe vers le haut
	if ((caseS.l%2 == 0 && caseS.c%2== 0) || (caseS.l%2 == 1 && caseS.c%2== 1))
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseS.c);	pointe.y = 820 - (HAUTEUR_TUILE * caseS.l);
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y - HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; 	pDroit.y = pointe.y - HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,red);
	}

	//triangle avec pointe vers le bas
	else
	{
		pointe.x = 20 + (LARGEUR_TUILE/2 * caseS.c);pointe.y = 820 - (HAUTEUR_TUILE * (caseS.l+1));
		pGauche.x = pointe.x - LARGEUR_TUILE/2; pGauche.y = pointe.y + HAUTEUR_TUILE;
		pDroit.x = pointe.x + LARGEUR_TUILE/2; 	pDroit.y = pointe.y + HAUTEUR_TUILE;
		dessine_triangle_plein(pointe,pGauche,pDroit,red);
	}
}
