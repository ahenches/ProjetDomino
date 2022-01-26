#include "dominos.h"
#include "modele.h"
#include "controleur.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonction controleur                                 //
//////////////////////////////////////////////////////////////////////////////////////////

void main_dominos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs, VARIANTE variante)
{
    int totJoueurs;
    int tour;    // a qui le tour
    int tourJeu; // nombre de tour jouer
    int gagnant;

    COORDONNEES indiceExtremite1;
    COORDONNEES indiceExtremite2;
    BOOL choix_joueur;
    BOOL continuePartie;

    indiceExtremite1.ligne = TAILLE_TAB_DOMINOS / 2;
    indiceExtremite1.colonne = TAILLE_TAB_DOMINOS / 2;
    indiceExtremite2.ligne = TAILLE_TAB_DOMINOS / 2;
    indiceExtremite2.colonne = TAILLE_TAB_DOMINOS / 2;

    totJoueurs = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
    tour = 0;
    tourJeu = 1;
    gagnant = -1;
    choix_joueur = FALSE;
    continuePartie = TRUE;

    printf("%d Joueurs Humains \n%d IA \n", joueurs.nbJoueurHumain, joueurs.nbJoueurIA);

    affiche_fonds();
    affiche_interface(variante);
    affiche_tour(infos_joueurs[1].pseudo);
    actualise_affichage();
    initialise_plateau();
    initialise_joueurs(infos_joueurs, totJoueurs);
    affiche_plateau();
    genere_pioche();
    affiche_pioche();
    distribue_premiers_dominos(infos_joueurs, totJoueurs);
    affiche_main(infos_joueurs[tour].mainJoueur);
    actualise_affichage();
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
            affiche_interface(variante);
            affiche_tour(infos_joueurs[tour].pseudo);
            affiche_main(infos_joueurs[tour].mainJoueur);
            actualise_affichage();

            if (strcmp(infos_joueurs[tour].pseudo, "IA1") == 0 || strcmp(infos_joueurs[tour].pseudo, "IA2") == 0 || strcmp(infos_joueurs[tour].pseudo, "IA3") == 0)
            {
                choix_joueur = joue_IA(&infos_joueurs[tour], &indiceExtremite1, &indiceExtremite2, tourJeu, variante);
            }
            else
            {
                choix_joueur = joue_joueur(&infos_joueurs[tour], &indiceExtremite1, &indiceExtremite2, tourJeu, variante);
                if (choix_joueur == QUITTER)
                {
                    printf("le jour a voulu quitter");
                    exit(0);
                }
                actualise_affichage();
            }

        } while (choix_joueur == TOUR_NON_FINI);

        affiche_pioche();
        affiche_plateau();

        if (tourJeu > 0)
        {
            gagnant = verifie_gagnant(infos_joueurs, indiceExtremite1, indiceExtremite2, totJoueurs, variante);
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
        actualise_affichage();
    }
}
