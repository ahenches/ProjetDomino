#include <stdio.h>
#include <stdlib.h>
#include "mainDominos.h"
#define RESH_FENETRE 600
#define RESV_FENETRE 626

/******************************************************************************/
/* 									MAIN                                      */
/******************************************************************************/

int main(int argc, char *argv[])
{

    // début de la session graphique
    init_fenetre(RESH_FENETRE,RESV_FENETRE);

	affiche_domino();
	initialise_plateau();
	affiche_plateau();

    attendre_clic();
    ferme_fenetre();
    return 0;
		
}
		

