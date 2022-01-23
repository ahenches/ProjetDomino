#include "dominos.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonction controleur                                 //
//////////////////////////////////////////////////////////////////////////////////////////

void main_dominos(NB_JOUEURS joueurs, char *tabPseudos[])
{
    POINT coin;
    int totJoueur;
    int tour;
    DOMINO choixJoueur;

    coin.x = 100;
    coin.y = 200;
    totJoueur = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
    tour = 0;
    printf("%d Joueurs Humains \n%d IA \n", joueurs.nbJoueurHumain, joueurs.nbJoueurIA);

    affiche_image("./img_dominos/bmp/00.bmp", coin);
    initialise_plateau();
    // affiche_plateau();
    genere_pioche();
    affiche_pioche();
    distribue_premiers_dominos(totJoueur);
    affiche_mains(totJoueur, tabPseudos);
    affiche_pioche();
    affiche_pseudos(tabPseudos, totJoueur);
    definit_premier_joueur(tabPseudos, determine_nb_dominos_main(totJoueur));
    printf("**** C'est au tour de %s de jouer ! ****\n", tabPseudos[0]);

    while (1)
    {
        choixJoueur = recupere_choix_domino_main(mainJoueurs[tour]);
        printf("**** Le domino |%d %d| a ete choisi ****\n", choixJoueur.valeur1, choixJoueur.valeur2);
        printf("\n-----------------------------\n");
        tour = determine_joueur_suivant(tour, totJoueur, tabPseudos);
    }
}
