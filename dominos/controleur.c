#include "dominos.h"
#include "modele.h"
#include "controleur.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonction controleur                                 //
//////////////////////////////////////////////////////////////////////////////////////////

void main_dominos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs)
{
    int totJoueurs;
    int tour;    // a qui le tour
    int tourJeu; // nombre de tour jouer
    int gagnant;

    COORDONNEES indiceExtremite1;
    COORDONNEES indiceExtremite2;
    BOOL dominoPlace;
    BOOL continuePartie;

    indiceExtremite1.ligne = TAILLE_TAB_DOMINOS / 2;
    indiceExtremite1.colonne = TAILLE_TAB_DOMINOS / 2;
    indiceExtremite2.ligne = TAILLE_TAB_DOMINOS / 2;
    indiceExtremite2.colonne = TAILLE_TAB_DOMINOS / 2;

    totJoueurs = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
    tour = 0;
    tourJeu = 1;
    gagnant = -1;
    dominoPlace = FALSE;
    continuePartie = TRUE;
    printf("%d Joueurs Humains \n%d IA \n", joueurs.nbJoueurHumain, joueurs.nbJoueurIA);

    affiche_fond();
    actualise_affichage();
    initialise_plateau();
    initialise_joueurs(infos_joueurs, totJoueurs);
    affiche_plateau();
    genere_pioche();
    affiche_pioche();
    distribue_premiers_dominos(infos_joueurs, totJoueurs);
    affiche_mains(totJoueurs, infos_joueurs);
    affiche_pioche();
    affiche_pseudos(infos_joueurs, totJoueurs);
    definit_premier_joueur(infos_joueurs, determine_nb_dominos_main(totJoueurs));
    printf("**** C'est au tour de %s de jouer ! ****\n\n", infos_joueurs[0].pseudo);

    while (continuePartie)
    {
        do
        {
            affiche_mains(totJoueurs, infos_joueurs);
            if (strcmp(infos_joueurs[tour].pseudo, "IA1") == 0 || strcmp(infos_joueurs[tour].pseudo, "IA2") == 0 || strcmp(infos_joueurs[tour].pseudo, "IA3") == 0)
            {
                dominoPlace = joue_IA(&infos_joueurs[tour], &indiceExtremite1, &indiceExtremite2, tourJeu);
            }
            else
            {
                dominoPlace = joue_joueur(&infos_joueurs[tour], &indiceExtremite1, &indiceExtremite2, tourJeu);
            }

        } while (dominoPlace == FALSE);

        

        affiche_plateau();

        if (tourJeu > 0)
        {
            gagnant = verifie_gagnant(infos_joueurs, indiceExtremite1, indiceExtremite2, totJoueurs);
        }
        
        if (gagnant != -1)
        {
            affiche_victoire(gagnant, infos_joueurs);
            continuePartie = FALSE;
        }
        else
        {
            tour = determine_joueur_suivant(tour, totJoueurs, infos_joueurs);
            tourJeu++;
        }

    }
}
