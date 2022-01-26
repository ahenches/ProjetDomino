#include <stdio.h>

#include "../lib/lib.h"
#include "../controleur.h"
#include "controleur.h"
#include "vue.h"
#include "modele.h"

int main_second();

int main_triominos(PSEUDO_JOUEUR *pseudoJoueurs, NB_JOUEURS nbJoueurs,
	VARIANTE variante)
{
	// Pour tester facilement le déroulement d'une partie ajouter ça dans ../controleur.c
	// PSEUDO_JOUEUR pseudoJoueurs[4];
	// strcpy(pseudoJoueurs[0].pseudo, "Jacques");
	// strcpy(pseudoJoueurs[1].pseudo, "Christine");
	// strcpy(pseudoJoueurs[2].pseudo, "Omar");
	// strcpy(pseudoJoueurs[3].pseudo, "Lyu");
	// NB_JOUEURS nj = {4, 2};
	// VARIANTE v = AVEC_SCORE;
	//
	// main_triominos(pseudoJoueurs, nj, v);

	ouvre_fenetre(LARGEUR, HAUTEUR);
	//declarations
	EMPLACEMENT **plateau;
	PIOCHE_TRIOMINOS laPioche;
	JOUEUR_TRIOMINOS joueurs[nbJoueurs.nbJoueurHumain+nbJoueurs.nbJoueurIA];
	int quiJoue, nJoueurs;
	int gainEnScore, partieMainEnCours, indiceDansMain;
	int nFoisPioche;
	POINT clic;
	BOOL aPioche;
	BOOL actionSignificative;
	CASE caseDuClic;
	TRIOMINO trioSelectionne;


	// initialisation de la partie.
	// modele
	for (int i = 0; i < nbJoueurs.nbJoueurHumain; i++)
	{
		strcpy(joueurs[i].pseudo, pseudoJoueurs[i].pseudo);
		joueurs[i].mainJoueur.taille = 0;
		joueurs[i].score = 0;
		joueurs[i].estHumain = true;
	}
	initialise_ordis(nbJoueurs, joueurs);

	plateau = initialise_plateau();
	laPioche = initialise_pioche();
	laPioche.taille = TAILLE_PIOCHE_INITIALE;
	quiJoue = joueur_qui_commence(nbJoueurs, joueurs, laPioche);
	distribution(nbJoueurs, joueurs, &laPioche);

	// vue
	nJoueurs = (nbJoueurs.nbJoueurHumain + nbJoueurs.nbJoueurIA);
	affiche_plateau_triminos();
	affiche_joueurs_triominos(nJoueurs, joueurs);
	actualise_pioche_triominos(laPioche.taille);
	if(variante == AVEC_SCORE)
		actualise_score_triominos(nJoueurs, joueurs);

	actualise_affichage();

	// Jeu
	while(!test_fin(nbJoueurs, joueurs, laPioche, plateau))
	{
		printf("\nquiJoue : joueur n°%d\n", quiJoue);
		if (joueurs[quiJoue].estHumain == false)
		{
			gainEnScore = jeu_ordinateur(joueurs[quiJoue], plateau);
			if (gainEnScore != 0)
			{
				joueurs[quiJoue].score += gainEnScore;
			}
			else
			// coup impossible l'ordinateur pioche
			{
				int i = 0;
				while(i<3 && gainEnScore == 0)
				{
					aPioche = pioche(&joueurs[quiJoue].mainJoueur, &laPioche);
					if (aPioche)
					{
						joueurs[quiJoue].score -= 5;
						gainEnScore = jeu_ordinateur(joueurs[quiJoue], plateau);
						i ++;
					}
					else
					{
						break;
					}

				}
				if (gainEnScore == 0){
					joueurs[quiJoue].score -= 10;
				}
				else  // gainEnScore != 0
				{
					joueurs[quiJoue].score += gainEnScore;
				}
			}
		}
		else // if (joueurs[quiJoue].estHumain == true)
		{
			actionSignificative = false;
			nFoisPioche = 0;
			indiceDansMain = -1;
			partieMainEnCours = DEBUT_MAIN;
			affiche_main_triominos(joueurs[quiJoue], partieMainEnCours);
			actualise_affichage();

			do {
				clic = attend_clic();
				if (est_clic_sur_quitter(clic))
					return 0;
				else if (clic_sur_fleche_triominos(clic))
				{
					partieMainEnCours = change_partie_main_triominos(joueurs[quiJoue],
						partieMainEnCours);
				}
				else if (clic_dans_main_triominos(clic))
				{
					indiceDansMain = transforme_selection_en_indice_main(clic,
						partieMainEnCours);
					if (indiceDansMain < joueurs[quiJoue].mainJoueur.taille)
					{
						trioSelectionne = joueurs[quiJoue].mainJoueur.tab[indiceDansMain];
						affiche_selection_main_triominos(indiceDansMain);
					}
					else
						indiceDansMain = -1;
				}
				else if (clic_dans_pioche_triominos(clic))
				{
					if (nFoisPioche == 3)
					{
						actionSignificative = true;
						joueurs[quiJoue].score -= 10;
					}
					else
					{
						aPioche = pioche(&joueurs[quiJoue].mainJoueur, &laPioche);
						if (aPioche)
						{
							joueurs[quiJoue].score -= 5;
							nFoisPioche ++; // mammamamama
							actualise_pioche_triominos(laPioche.taille);
							actualise_score_triominos(nJoueurs, joueurs);
							affiche_main_triominos(joueurs[quiJoue], partieMainEnCours);
						}
					}

				}
				else if (indiceDansMain != -1 && clic_dans_plateau_triominos(clic))
				{
					caseDuClic = transforme_point_en_case_triominos(clic);
					gainEnScore = placer_trio(trioSelectionne, plateau,
							caseDuClic.l, caseDuClic.c);
					if (gainEnScore != 0)
					{
						rearrange_main_joueur(joueurs[quiJoue].mainJoueur, indiceDansMain);
						joueurs[quiJoue].score += gainEnScore;
						// actualise_plateau_triominos(plateau);
						actualise_score_triominos(nJoueurs, joueurs);
						affiche_main_triominos(joueurs[quiJoue], partieMainEnCours);
						actionSignificative = true;
					}
					else
					{
						// do nothing
					}
				}
				actualise_affichage();
			}
			while (!actionSignificative);
		}
		if(variante == AVEC_SCORE)
			actualise_score_triominos(nJoueurs, joueurs);
		// actualise_plateau_triominos(plateau);
		actualise_pioche_triominos(laPioche.taille);
		actualise_affichage();
		quiJoue = (quiJoue+1) % nJoueurs;
	}
	// JOUEUR_TRIOMINOS joueurs [4];
	// char texte[25] = "test";
	// TRIOMINO trio1;
	// POINT clic;
	// trio1.min = 1; trio1.sec = 2; trio1.der = 3;
	// EMPLACEMENT emp;
	// emp.trio = trio1;
	// emp.pointe = 's';
	//
	// CASE case1;
	// case1.l = 1; case1.c = 19;
	//
	// MAIN_J_TRIOMINOS mainJ1 ;
	// mainJ1.taille = 15;
	// for(int i=0; i<15;i++)
	// {
	// 	mainJ1.tab[i] = trio1;
	// }
	//
	// for (int i=0 ; i<4; i++)
	// {
	// 	joueurs[i].pseudo[0]='J';
	// 	joueurs[i].pseudo[1]='\0';
	// 	joueurs[i].mainJoueur = mainJ1;
	// 	joueurs[i].score = 0;
	// 	joueurs[i].estHumain = FALSE;
	//
	// }
	// affiche_plateau_triminos();
	// actualise_affichage();
	// clic = attend_clic();
	//
	//
	// actualise_pioche_triominos(36);
	// actualise_affichage();
	// //attend_clic();
	//
	// affiche_main_triominos(joueurs[1], FIN_MAIN);
	// actualise_affichage();
	//attend_clic();

	// efface_main_triominos();
	// actualise_affichage();
	// attend_clic();
	//
	// affiche_joueurs_triominos(nbJ,  joueurs);
	// actualise_affichage();
	// attend_clic();
	//
	// actualise_score_triominos( nbJ, joueurs);
	// actualise_affichage();
	// attend_clic();
	//
	// actualise_affichage();
	// attend_clic();

//test affichage plateau
	//affiche_triomino(case1,emp);
	//case1.l = 7;
	//affiche_triomino(case1,emp);

	//case1.l = 6; case1.c = 19;
	//affiche_triomino(case1,emp);

	//case1.l = 6; case1.c = 18;
	//affiche_emplacement_possible_triominos(case1);

	//case1.l = 6; case1.c = 18;
	//affiche_triomino(case1,emp);

	//affiche_main_triominos(mainJ1);
	//actualise_affichage();


	//actualise_affichage();
	//attend_clic();

	//efface_main_triominos();

	//actualise_pioche_triominos(0);

	//actualise_affichage();

//test les fonction verifie clic
	// int pm =DEBUT_MAIN;
	// for (int i=0; i<5;i++)
	// {
	// 	if (clic_dans_main_triominos(clic))
	// 		printf("main ok\n");
	//
	// 	if (clic_sur_fleche_triominos(clic))
	// 	{
	// 		pm = change_partie_main_triominos(joueurs[1], pm);
	// 		actualise_affichage();
	// 	}
	//
	// 	if(clic_dans_pioche_triominos(clic))
	// 		printf("pioche ok\n");
	//
	// 	if(clic_dans_plateau_triominos(clic))
	// 		printf("plateau ok\n");
	//
	// 	clic=attend_clic();
	// }

//test transforme point en case
	//for(int j=0; j<5;j++)
	//{
		//case1 = transforme_point_en_case_triominos(attend_clic());
		//printf("l : %d  c : %d  \n",case1.l, case1.c);
	//}

// test de affiche emplacement selectionne
	//CASE temp;
	//for (int k=0; k < 5 ; k++)
	//{
		//clic= attend_clic();
		//temp = transforme_point_en_case_triominos(clic);
		//affiche_selection_emplacement_triominos(temp);
		//actualise_affichage();
	//}
	//efface_selection_main_triominos(3);
	//attend_clic();
	//actualise_affichage();

	// affiche_selection_main_triominos(0);
	// attend_clic();
	// actualise_affichage();
	//
	// affiche_selection_main_triominos(1);
	//attend_clic();
	//actualise_affichage();

	//efface_selection_main_triominos(0);
	//attend_clic();
	//actualise_affichage();

	//efface_selection_main_triominos(1);
	//attend_clic();

	//main_second();

	return 0;
}


BOOL clic_dans_main_triominos(POINT clic)
{
	if(clic.x > BORDURE_T && clic.x < BORDURE_T + LARGEUR_MAIN_T - ( LARGEUR_TUILE_T + 10 ) )
		if (clic.y > 10 && clic.y < 10 + HAUTEUR_MAIN_T )
			return TRUE;
	return FALSE;
}

BOOL clic_sur_fleche_triominos(POINT clic)
{
	if(clic.x > BORDURE_T +LARGEUR_MAIN_T - ( LARGEUR_TUILE_T + 10 ) && clic.x < BORDURE_T + LARGEUR_MAIN_T  )
		if (clic.y > 10 && clic.y < 10 + HAUTEUR_MAIN_T )
			return TRUE;
	return FALSE;
}

BOOL clic_dans_pioche_triominos(POINT clic)
{
	if(clic.x > BORDURE_T+LARGEUR_MAIN_T+10 && clic.x < BORDURE_T+LARGEUR_MAIN_T+LARGEUR_PIOCHE_T+10)
		if (clic.y > 10 && clic.y < 10 + HAUTEUR_MAIN_T )
			return TRUE;
	return FALSE;
}

BOOL clic_dans_plateau_triominos(POINT clic)
{
	if(clic.x > BORDURE_T && clic.x < BORDURE_T+LARGEUR_PLATEAU_T)
		if (clic.y > BORDURE_T + HAUTEUR_MAIN_T && clic.y < BORDURE_T + HAUTEUR_MAIN_T + HAUTEUR_PLATEAU_T)
			return TRUE;
	return FALSE;
}

// précondition le clic doit etre dans le plateau
CASE transforme_point_en_case_triominos(POINT clic)
{
	CASE caseClic;

	caseClic.l = (HAUTEUR_PLATEAU_T - (clic.y - (BORDURE_T + HAUTEUR_MAIN_T))) / HAUTEUR_TUILE_T;
	caseClic.c = (clic.x -BORDURE_T) / (LARGEUR_TUILE_T / 2);

	return caseClic;
}

// precondition le clic doit etre dans la main
// A voir si elle retourne pas un entier (indice) pour ne pas avoir de probleme si le trionmino est "vide" (rien a l emplacement du clic)
int transforme_selection_en_indice_main(POINT clic, int partieMain)
{
	int indice;

	indice = (clic.x - BORDURE_T) / (LARGEUR_TUILE_T + 10);

	if (partieMain == FIN_MAIN)
		indice += 14;

	return indice;
}

int change_partie_main_triominos(JOUEUR_TRIOMINOS joueur, int partieMain)
{
	efface_main_triominos();
	if (partieMain == DEBUT_MAIN)
	{
		affiche_main_triominos(joueur, FIN_MAIN);
		return FIN_MAIN;
	}
	else
	{
		affiche_main_triominos(joueur, DEBUT_MAIN);
		return DEBUT_MAIN;
	}
}
BOOL est_clic_sur_quitter(POINT clic)
{
	if(clic.x > 1150  && clic.x < 1150 + 100 && clic.y < 885 && clic.y > 885 - 50)
		return TRUE;
	return FALSE;
}
