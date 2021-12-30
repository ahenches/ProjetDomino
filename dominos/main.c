#include <stdio.h>
#include <stdlib.h>
#include "mainDominos.h"
#include "../lib/lib.h"

#define RESH_FENETRE 600
#define RESV_FENETRE 626


/******************************************************************************/
/* 									MAIN                                      */
/******************************************************************************/
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
    char *tabPseudo[4];
    joueurs.nbJoueurHumain = 2;
    joueurs.nbJoueurIA = 1;
   
	
    entre_pseudos(tabPseudo, joueurs);
    main_dominos(joueurs, tabPseudo);


    attend_clic();
    ferme_fenetre();

    return 0;
		
}
		

