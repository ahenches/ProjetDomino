#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/lib.h"
#include "../controleur.h"
#include "modele.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonction controleur                                 //
//////////////////////////////////////////////////////////////////////////////////////////

int main_dominos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs, VARIANTE variante)
{

    int totJoueurs;
    int tour;    // à qui le tour (numéro du joueur)
    int tourJeu; // nombre de tour joués
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

    affiche_fond();
    affiche_interface(variante);
    affiche_tour(infos_joueurs[1].pseudo);
    actualise_affichage();
    initialise_plateau_domino();
    initialise_joueurs(infos_joueurs, totJoueurs);
    affiche_plateau();
    genere_pioche();
    affiche_pioche_domino();
    distribue_premiers_dominos(infos_joueurs, totJoueurs);
    affiche_main(infos_joueurs, tour);
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
            affiche_main(infos_joueurs, tour);
            actualise_affichage();

            if (strcmp(infos_joueurs[tour].pseudo, "IA0") == 0 || strcmp(infos_joueurs[tour].pseudo, "IA1") == 0 || strcmp(infos_joueurs[tour].pseudo, "IA2") == 0)
            {
                SDL_Delay(3000);
                choix_joueur = joue_IA(&infos_joueurs[tour], &indiceExtremite1, &indiceExtremite2, tourJeu, variante);
            }
            else
            {
                choix_joueur = joue_joueur(&infos_joueurs[tour], &indiceExtremite1, &indiceExtremite2, tourJeu, variante, tour);
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

        if (gagnant != -1) // si la partie est terminée
        {
            affiche_victoire(gagnant, infos_joueurs);
            POINT p1;
            p1.x = 1;
            p1.y = 100;
            affiche_image("./dominos/img_dominos/cache_main.bmp", p1);
            actualise_affichage();
            SDL_Delay(3000);
            p1.x = 1;
            p1.y = 20 + HAUTEUR_MAIN + HAUTEUR_PLATEAU;
            affiche_image("./dominos/img_dominos/tapis.bmp", p1);
            p1.x = 430;
            p1.y = HAUTEUR / 2;

            if (gagnant == -2)
            {
                affiche_texte("Personne ne gagne il y egalite", 25, p1, lightgoldenrodyellow);
                actualise_affichage();
            }
            else
            {
                char phrase_gagnant[100];
                sprintf(phrase_gagnant, "%s a pose tous ses dominos", infos_joueurs[gagnant].pseudo);
                affiche_texte(phrase_gagnant, 25, p1, lightgoldenrodyellow);
                actualise_affichage();
            }

            ecrit_scores_fichier(infos_joueurs, totJoueurs);

            SDL_Delay(3000);
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
