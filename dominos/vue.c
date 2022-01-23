#include "main.h"
#include "modele.h"
#include "controleur.h"
#include "vue.h"


//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonctions de la vue                                 //
//////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui parcourt le tableau des pseudos et qui affiche les pseudos des joueurs
void affiche_pseudos(JOUEUR tabJoueurs[], int totJoueur)
{
    int i;

    for (i = 0; i < totJoueur; i++)
    {
        printf("%s\n", tabJoueurs[i].pseudo);
    }
}

// Fonction qui affiche le plateau de jeu en parcourant le tableau de jeu
void affiche_plateau()
{
    int i;
    int j;
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        for (j = 0; j < TAILLE_TAB_DOMINOS; j++)
        {
            if (plateau[i][j].valeur1 == -1 && plateau[i][j].valeur2 == -1)
                printf("|-1|");
            // printf("|%d %d| ", dominoCourant.valeur1, dominoCourant.valeur2);
        }
        printf("\n");
    }
}

// affiche la main des joueurs en parcourant le tableau des mainsJoueurs
void affiche_mains(int totJoueur, JOUEUR tabJoueurs[])
{
    int i;
    int j;

    for (i = 0; i < totJoueur; i++)
    {
        printf("%s = ", tabJoueurs[i].pseudo);
        for (j = 0; j < determine_nb_dominos_main(totJoueur); j++)
        {
            printf("|%d %d| ", tabJoueurs[i].mainJoueur[j].valeur1, tabJoueurs[i].mainJoueur[j].valeur2);
        }
        printf("\n");
    }
}

// affiche la pioche en parcourant le tableau pioche
void affiche_pioche()
{
    int i;

    printf("---------  La pioche : ----------\n");
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        if (pioche[i].valeur1 != -1)
            printf("|%d %d| ", pioche[i].valeur1, pioche[i].valeur2);
    }
    printf("\n---------------------------------\n");
}