#include <stdio.h>
#include <stdlib.h>
#include "mainDominos.h"
#include "libGraphique.h"

#define RESH_FENETRE 600
#define RESV_FENETRE 626

/******************************************************************************/
/* 									MAIN                                      */
/******************************************************************************/

int main(int argc, char *argv[])
{
    // début de la session graphique
    init_fenetre(RESH_FENETRE,RESV_FENETRE);

    NB_JOUEURS joueurs;

    joueurs.nbJoueurHumain = 2;
    joueurs.nbJoueurIA = 0;

	main_dominos(joueurs);

    attendre_clic();
    ferme_fenetre();
    return 0;
		
}
		

