#include "dominos.h"
#include "modele.h"
#include "controleur.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonction controleur                                 //
//////////////////////////////////////////////////////////////////////////////////////////

void main_dominos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs)
{
    POINT coin;
    int totJoueur;
    int tour; // a qui le tour
    int tourJeu; // nombre de tour jouer
    
    COORDONNEES indiceExtremite1;
    COORDONNEES indiceExtremite2;
    BOOL dominoPlace;

    indiceExtremite1.ligne = TAILLE_TAB_DOMINOS/2;
    indiceExtremite1.colonne = TAILLE_TAB_DOMINOS/2;
    indiceExtremite2.ligne = TAILLE_TAB_DOMINOS/2;
    indiceExtremite2.colonne = TAILLE_TAB_DOMINOS/2;

    coin.x = 100;
    coin.y = 200;
    totJoueur = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
    tour = 0;
    tourJeu = 1;
    dominoPlace = FALSE;
    printf("%d Joueurs Humains \n%d IA \n", joueurs.nbJoueurHumain, joueurs.nbJoueurIA);

    affiche_image("./img_dominos/bmp/00.bmp", coin);
    actualise_affichage();
    initialise_plateau();
    initialise_mains_joueurs(infos_joueurs, totJoueur);
    affiche_plateau();
    genere_pioche();
    affiche_pioche();
    distribue_premiers_dominos(infos_joueurs, totJoueur);
    affiche_mains(totJoueur, infos_joueurs);
    affiche_pioche();
    affiche_pseudos(infos_joueurs, totJoueur);
    definit_premier_joueur(infos_joueurs, determine_nb_dominos_main(totJoueur));
    printf("**** C'est au tour de %s de jouer ! ****\n\n", infos_joueurs[0].pseudo);

    while (1)
    {
        do
        {
            affiche_mains(totJoueur, infos_joueurs);
            DOMINO temp = recupere_choix_domino_main(infos_joueurs[tour].mainJoueur);
            DOMINO *dominoChoisi = &temp;
            printf("**** Le domino |%d %d| a ete choisi ****\n", dominoChoisi->valeur1, dominoChoisi->valeur2);
            printf("\n-----------------------------\n");
        
            dominoPlace = place_domino(dominoChoisi, &indiceExtremite1, &indiceExtremite2, tourJeu, infos_joueurs[tour].mainJoueur);
        }while(dominoPlace == FALSE);
        
        affiche_plateau();
        tour = determine_joueur_suivant(tour, totJoueur, infos_joueurs);
        tourJeu++;
    }
}
