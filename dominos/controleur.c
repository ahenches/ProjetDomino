#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/lib.h"
#include "../controleur.h"
//#include "controleur.h"
#include "modele.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonction controleur                                 //
//////////////////////////////////////////////////////////////////////////////////////////

int main_dominos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs, VARIANTE variante)
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

    indiceExtremite1.coin.x = (LARGEUR_PLATEAU / 2) - 85;
    indiceExtremite1.coin.y = 470;
    indiceExtremite2.coin.x = (LARGEUR_PLATEAU / 2) - 85;
    indiceExtremite2.coin.y = 470;

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
    initialise_plateau_domino();
    initialise_joueurs(infos_joueurs, totJoueurs);
    affiche_plateau();
    genere_pioche();
    affiche_pioche_domino();
    distribue_premiers_dominos(infos_joueurs, totJoueurs);
    affiche_main(infos_joueurs[tour].mainJoueur);
    actualise_affichage();
    affiche_mains(totJoueurs, infos_joueurs);
    affiche_pioche_domino();
    affiche_pseudos(infos_joueurs, totJoueurs);
    definit_premier_joueur(infos_joueurs, determine_nb_dominos_main(totJoueurs));
    printf("**** C'est au tour de %s de jouer ! ****\n\n", infos_joueurs[0].pseudo);
    affiche_victoire(gagnant, infos_joueurs);

    while (continuePartie)
    {
        do
        {
            affiche_mains(totJoueurs, infos_joueurs);
            affiche_interface(variante);
            affiche_tour(infos_joueurs[tour].pseudo);
            affiche_main(infos_joueurs[tour].mainJoueur);
            actualise_affichage();

            if (strcmp(infos_joueurs[tour].pseudo, "IA0") == 0 || strcmp(infos_joueurs[tour].pseudo, "IA1") == 0 || strcmp(infos_joueurs[tour].pseudo, "IA2") == 0)
            {
                choix_joueur = joue_IA(&infos_joueurs[tour], &indiceExtremite1, &indiceExtremite2, tourJeu, variante);
            }
            else
            {
                choix_joueur = joue_joueur(&infos_joueurs[tour], &indiceExtremite1, &indiceExtremite2, tourJeu, variante);
                if (choix_joueur == QUITTER)
                {
                    FILE *fichier = NULL;

                    fichier = fopen("./classement.txt", "w");

                    if (fichier != NULL)
                    {

                        int i;
                        for (i = 0; i < totJoueurs; i++)
                        {
                            fprintf(fichier, "score de %s: %d\n", infos_joueurs[i].pseudo, infos_joueurs[i].score);
                        }
                        fclose(fichier);
                    }
                    return 0;
                }
                actualise_affichage();
            }

        } while (choix_joueur == TOUR_NON_FINI);

        affiche_pioche_domino();
        affiche_plateau();

        if (tourJeu > 0)
        {
            gagnant = verifie_gagnant(infos_joueurs, indiceExtremite1, indiceExtremite2, totJoueurs, variante);
        }

        if (gagnant != -1)
        {
            affiche_victoire(gagnant, infos_joueurs);

            FILE *fichier = NULL;

            fichier = fopen("./classement.txt", "w");

            if (fichier != NULL)
            {

                int i;
                for (i = 0; i < totJoueurs; i++)
                {
                    fprintf(fichier, "score de %s: %d\n", infos_joueurs[i].pseudo, infos_joueurs[i].score);
                }
                fclose(fichier);
            }
            continuePartie = FALSE;
        }
        else
        {
            tour = determine_joueur_suivant(tour, totJoueurs, infos_joueurs);
            tourJeu++;
        }
        actualise_affichage();
    }

    return 0;
}
