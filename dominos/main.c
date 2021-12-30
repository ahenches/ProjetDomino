#include <stdio.h>
#include <stdlib.h>
#include "mainDominos.h"
#include "../lib/lib.h"

#define RESH_FENETRE 600
#define RESV_FENETRE 626
const unsigned int  lignes =  4;
const unsigned int  colonnes = 10;

/******************************************************************************/
/* 									MAIN                                      */
/******************************************************************************/

int main(int argc, char *argv[])
{
    // début de la session graphique
    ouvre_fenetre(RESH_FENETRE,RESV_FENETRE);

    NB_JOUEURS joueurs;
    char pseudoIA[3][5]={"IA1","IA2","IA3"};
    int totJoueurs;
    int i;

    joueurs.nbJoueurHumain = 2;
    joueurs.nbJoueurIA = 1;
    totJoueurs = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
	


	char *tabPseudo[4];
	for (i = 0; i < joueurs.nbJoueurHumain; i++)
	{
		printf("Choisissez votre pseudo :\n"); 
		tabPseudo[i]=(char*)malloc(25);//mention  the size you need..
		scanf("%s",tabPseudo[i]);
	}
	for (i = joueurs.nbJoueurHumain; i < totJoueurs; i++)
	{
		printf("%d IA \n", joueurs.nbJoueurIA); 
		tabPseudo[i]=(char*)malloc(25);//mention  the size you need..
		sprintf(tabPseudo[i],"IA%d",i);
	}

	printf("-------------------------\n");
	for (i = 0; i < 4; i++)
	{
		printf("%s\n",tabPseudo[i]);
	}
	printf("-------------\n %s\n",tabPseudo[2]);
  

    main_dominos(joueurs, tabPseudo);


    attend_clic();
    ferme_fenetre();

    return 0;

	/*
	CA MARCHE

	char *tabPseudo[4];
	for (int i = 0; i < 4; i++)
	{
		printf("Choisissez votre pseudo :\n"); 
		tabPseudo[i]=(char*)malloc(25);//mention  the size you need..
		scanf("%s",tabPseudo[i]);
	}
	
	printf("-------------------------\n");
	for (int i = 0; i < 4; i++)
	{
		printf("%s\n",tabPseudo[i]);
	}
	printf("-------------\n %s\n",tabPseudo[2]);
    */
		
}
		

