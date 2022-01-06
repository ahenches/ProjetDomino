#include <stdio.h>
#include <stdlib.h>
#include "mainDominos.h"
#include "../lib/lib.h"

#define RESH_FENETRE 600
#define RESV_FENETRE 626
#define TOT_JOUEURS 4

/******************************************************************************/
/* 									MAIN                                      */
/******************************************************************************/
NB_JOUEURS entre_nb_joueurs(NB_JOUEURS joueurs)
{
	do
	{
		printf("Choisissez le nombre de joueurs Humain :\n"); 
    	scanf("%d",&joueurs.nbJoueurHumain);
	}while(joueurs.nbJoueurHumain > 4 || joueurs.nbJoueurHumain < 0);

    do
	{
	    printf("Choisissez le nombre de joueurs Ordinateur :\n");
	    scanf("%d",&joueurs.nbJoueurIA); 
	}while(joueurs.nbJoueurIA > 3 || joueurs.nbJoueurIA < 0);
	
	printf("-------------------------\n");
	return joueurs;
}

void entre_pseudos(char *tabPseudo[], NB_JOUEURS joueurs)
{
	int i;
    int compt;
    int totJoueurs;

    totJoueurs = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
    compt=1;

	for (i = 0; i < joueurs.nbJoueurHumain; i++)
	{
		printf("Choisissez votre pseudo :\n"); 
		tabPseudo[i]=(char*)malloc(25);//mention  the size you need..
		scanf("%s",tabPseudo[i]);
	}
	
	for (i = joueurs.nbJoueurHumain; i < totJoueurs; i++)
	{
		tabPseudo[i]=(char*)malloc(25);//mention  the size you need..
		sprintf(tabPseudo[i],"IA%d",compt);
		compt++;
	}

	printf("-------------------------\n");
}

int main(int argc, char *argv[])
{
    // début de la session graphique
    ouvre_fenetre(RESH_FENETRE,RESV_FENETRE);

    NB_JOUEURS joueurs;
    char *tabPseudo[TOT_JOUEURS];

	joueurs = entre_nb_joueurs(joueurs);
    entre_pseudos(tabPseudo, joueurs);
    main_dominos(joueurs, tabPseudo);


    attend_clic();
    ferme_fenetre();

    return 0;
		
}
		

