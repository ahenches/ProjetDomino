#include "main.h"
#include "modele.h"
#include "controleur.h"
#include "vue.h"


//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonction controleur                                 //
//////////////////////////////////////////////////////////////////////////////////////////

void main_dominos(JOUEUR tabJoueurs[], NB_JOUEURS joueurs)
{
    POINT coin;
    int totJoueur;
    int tour;
    DOMINO dominoChoisi;

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
    distribue_premiers_dominos(tabJoueurs, totJoueur);
    affiche_mains(totJoueur, tabJoueurs);
    affiche_pioche();
    affiche_pseudos(tabJoueurs, totJoueur);
    definit_premier_joueur(tabJoueurs, determine_nb_dominos_main(totJoueur));
    printf("**** C'est au tour de %s de jouer ! ****\n", tabJoueurs[0].pseudo);

    while (1)
    {
        dominoChoisi = recupere_choix_domino_main(tabJoueurs[tour].mainJoueur);
        printf("**** Le domino |%d %d| a ete choisi ****\n", dominoChoisi.valeur1, dominoChoisi.valeur2);
        printf("\n-----------------------------\n");
        tour = determine_joueur_suivant(tour, totJoueur, tabJoueurs);
    }
}
