#include <stdio.h>
#include "lib/lib.h"
#include "controleur.h"
#include "vue.h"
#include "triominos/controleur.h"
#include "./dominos/modele.h"
#include "./dominos/vue.h"

// variables globales
DOMINO plateau[TAILLE_TAB_DOMINOS][TAILLE_TAB_DOMINOS]; // Plateau de jeu, [ligne][colonne]
DOMINO pioche_domino[TAILLE_TAB_DOMINOS];

int main()
{
	POINT clic;
	int i, compt;
	NB_JOUEURS nbJoueurs;
	PSEUDO_JOUEUR pseudoJoueurs[4];
	CHOIX_JEU choixJeu;
	BOOL rejouer;

	ouvre_fenetre(1300, 900);

	// On attend que l'utilisateur clique sur Jouer
	affiche_menu_accueil();
	actualise_affichage();
	do
	{
		clic = attend_clic();
	} while (!est_clic_sur_jouer_menu_accueil(clic));

	// On affiche le menu du choix du nombre de joueurs
	affiche_menu_nombre_joueurs();
	actualise_affichage();

	// On attend que le choix du nombre de joueurs soit fait et correcte
	nbJoueurs = transforme_clic_en_nb_joueurs();

	// On demande a chaque joueur d entrer son pseudo
	for (i = 0; i < nbJoueurs.nbJoueurHumain; i++)
	{
		affiche_menu_pseudo(i + 1);
		actualise_affichage();
		printf("Joueur %d, Choisissez votre pseudo :\n", i + 1);
		scanf("%s", pseudoJoueurs[i].pseudo);

		if (strlen(pseudoJoueurs[i].pseudo) > 25)
		{
			do
			{
				printf("\nVeillez respecter la limite maximale de 25 charactères.\n");
				scanf("%s", pseudoJoueurs[i].pseudo);
			} while (strlen(pseudoJoueurs[i].pseudo) > 25);
		}
	}
	printf("\nLes pseudos sont enregistrés !\n");

	// On complete le nom des Ordinateurs s il en a
	compt = 0;
	for (i = nbJoueurs.nbJoueurHumain; i < nbJoueurs.nbJoueurIA + nbJoueurs.nbJoueurHumain; i++)
	{
		sprintf(pseudoJoueurs[i].pseudo, "IA%d", compt);
		compt++;
	}

	rejouer = TRUE;
	do
	{
		// On affiche le menu pour le choix et du jeu et de sa variante
		affiche_menu_choix_jeu();
		actualise_affichage();

		choixJeu = transforme_clic_en_choix_jeu();

		// On lance le jeu selectionné
		if (choixJeu.jeu == DOMINOS)
		{
			JOUEUR infos_joueurs[TOT_JOUEURS];
			for (i = 0; i < TOT_JOUEURS; i++)
			{
				strcpy(infos_joueurs[i].pseudo, pseudoJoueurs[i].pseudo); // on récupere les pseudos du tableau destiné au jeu triomino dans le tableau destiné au domino
			}

			main_dominos(infos_joueurs, nbJoueurs, choixJeu.variante);
		}
		else
		{
			main_triominos(pseudoJoueurs, nbJoueurs, choixJeu.variante);
		}

		// On affiche le classement
		affiche_menu_classement();
		actualise_affichage();

		// On atend de savoir si l'utilsateur veut rejouer ou non
		rejouer = veut_rejouer();
	} while (rejouer);

	return 0;
}

BOOL est_clic_sur_jouer_menu_accueil(POINT clic)
{
	if (clic.x > 450 && clic.x < 450 + 400 && clic.y < 500 && clic.y > 500 - 200)
		return TRUE;
	else
		return FALSE;
}

NB_JOUEURS transforme_clic_en_nb_joueurs()
{
	NB_JOUEURS nbJoueurs;
	int nbHumains, nbOrdi, nbTotal;
	POINT clic;
	BOOL estChoixCorrect, estClicSurConfirme;

	nbHumains = -5;
	nbOrdi = -5;
	estChoixCorrect = FALSE;
	estClicSurConfirme = FALSE;

	do
	{
		clic = attend_clic();

		// Clic dans choix nombre joueurs humains
		if (clic.y < 630 && clic.y > 630 - COTE_NB_JOUEUR)
		{
			if (clic.x > 520 && clic.x < 520 + COTE_NB_JOUEUR)
				nbHumains = 1;
			if (clic.x > 600 && clic.x < 600 + COTE_NB_JOUEUR)
				nbHumains = 2;
			if (clic.x > 680 && clic.x < 680 + COTE_NB_JOUEUR)
				nbHumains = 3;
			if (clic.x > 760 && clic.x < 760 + COTE_NB_JOUEUR)
				nbHumains = 4;
			if (nbHumains <= 4 && nbHumains >= 1)
				affiche_selection_nb_joueurs_humains(nbHumains);
		}

		// Clic dans choix nombre joueurs ordinateurs
		if (clic.y < 380 && clic.y > 380 - COTE_NB_JOUEUR)
		{
			if (clic.x > 520 && clic.x < 520 + COTE_NB_JOUEUR)
				nbOrdi = 0;
			if (clic.x > 600 && clic.x < 600 + COTE_NB_JOUEUR)
				nbOrdi = 1;
			if (clic.x > 680 && clic.x < 680 + COTE_NB_JOUEUR)
				nbOrdi = 2;
			if (clic.x > 760 && clic.x < 760 + COTE_NB_JOUEUR)
				nbOrdi = 3;
			if (nbOrdi <= 3 && nbOrdi >= 0)
				affiche_selection_nb_joueurs_ordi(nbOrdi);
		}
		nbTotal = nbHumains + nbOrdi;
		if (nbTotal >= 2 && nbTotal <= 4)
			estChoixCorrect = TRUE;
		else
			estChoixCorrect = FALSE;

		// Clic sur Confirmer
		// Clic dans choix nombre joueurs humains
		if ((clic.x > 480) && (clic.x < 480 + 400) && (clic.y < 230) && (clic.y > 230 - 100))
		{
			if (estChoixCorrect)
			{

				estClicSurConfirme = TRUE;
			}
			else
			{
				estClicSurConfirme = FALSE;
			}
		}
		actualise_affichage();
	} while (!estChoixCorrect || !estClicSurConfirme);

	nbJoueurs.nbJoueurHumain = nbHumains;
	nbJoueurs.nbJoueurIA = nbOrdi;

	return nbJoueurs;
}

CHOIX_JEU transforme_clic_en_choix_jeu()
{
	CHOIX_JEU choix;
	JEU jeuSelect;
	VARIANTE varSelect;
	POINT clic;
	BOOL estChoisiVariante, estClicSurJouer;

	estChoisiVariante = FALSE;
	estClicSurJouer = FALSE;
	do
	{
		clic = attend_clic();

		// Clic sur un jeu
		if (clic.y < 580 && clic.y > 580 - 100)
		{
			if (clic.x > 125 && clic.x < 125 + 400)
			{
				jeuSelect = DOMINOS;
				estChoisiVariante = FALSE;
				affiche_selection_jeu(DOMINOS);
			}
			if (clic.x > 775 && clic.x < 775 + 400)
			{
				jeuSelect = TRIOMINOS;
				estChoisiVariante = FALSE;
				affiche_selection_jeu(TRIOMINOS);
			}
		}

		// Clic sur une variante
		if (clic.y < 350 && clic.y > 350 - 50)
		{
			if (clic.x > 155 && clic.x < 155 + 150)
			{
				jeuSelect = DOMINOS;
				varSelect = AVEC_PIOCHE;
				affiche_selection_variante(AVEC_PIOCHE);
				estChoisiVariante = TRUE;
			}
			if (clic.x > 345 && clic.x < 345 + 150)
			{
				jeuSelect = DOMINOS;
				varSelect = SANS_PIOCHE;
				affiche_selection_variante(SANS_PIOCHE);
				estChoisiVariante = TRUE;
			}
			if (clic.x > 805 && clic.x < 805 + 150)
			{
				jeuSelect = TRIOMINOS;
				varSelect = AVEC_SCORE;
				affiche_selection_variante(AVEC_SCORE);
				estChoisiVariante = TRUE;
			}
			if (clic.x > 995 && clic.x < 995 + 150)
			{
				jeuSelect = TRIOMINOS;
				varSelect = SANS_SCORE;
				affiche_selection_variante(SANS_SCORE);
				estChoisiVariante = TRUE;
			}
		}

		if (clic.x > 500 && clic.x < 500 + 300 && clic.y < 200 && clic.y > 200 - 100)
		{
			if (estChoisiVariante)
				estClicSurJouer = TRUE;
			else
				estClicSurJouer = FALSE;
		}
		actualise_affichage();
	} while (!estChoisiVariante || !estClicSurJouer);

	choix.jeu = jeuSelect;
	choix.variante = varSelect;
	return choix;
}

BOOL veut_rejouer()
{
	POINT clic;
	BOOL estCLicBon, choixRejouer;

	estCLicBon = FALSE;
	do
	{
		clic = attend_clic();
		if (clic.y < 200 && clic.y > 200 - 100)
		{
			if (clic.x > 425 && clic.x < 425 + 200)
			{
				estCLicBon = TRUE;
				choixRejouer = TRUE;
			}
			if (clic.x > 675 && clic.x < 675 + 200)
			{
				estCLicBon = TRUE;
				choixRejouer = FALSE;
			}
		}
	} while (!estCLicBon);
	return choixRejouer;
}
