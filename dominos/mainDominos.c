#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mainDominos.h"
#include "../lib/lib.h"

#define TAILLE_TAB_DOMINOS 28 // 28 dominos en longueur ou largeur
#define TOT_JOUEURS 4

DOMINO plateau[TAILLE_TAB_DOMINOS][TAILLE_TAB_DOMINOS]; // Plateau de jeu
DOMINO pioche[TAILLE_TAB_DOMINOS];                      // pioche
DOMINO mainJoueurs[4][7];

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonctions Dominos                                   //
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

// Fonction qui parcourt le tableau des pseudos et qui affiche les pseudos des joueurs
void affiche_pseudos(char *tabPseudos[], int totJoueur)
{
    int i;

    for (i = 0; i < totJoueur; i++)
    {
        printf("%s\n", tabPseudos[i]);
    }
}

// Fonction qui initialise le plateau
void initialise_plateau()
{
    int i;
    int j;
    DOMINO emplacementVide;

    emplacementVide.valeur1 = -1;
    emplacementVide.valeur2 = -1;
    emplacementVide.orientation = RIEN;
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        for (j = 0; j < TAILLE_TAB_DOMINOS; j++)
        {
            plateau[i][j] = emplacementVide;
        }
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

// Fonction qui genère les 28 dominos qui constituent la pioche
void genere_pioche()
{
    int i;
    int j;
    int compt;
    int comptDominos;
    DOMINO dominoCourant;

    dominoCourant.orientation = HORIZONTALE;
    compt = 0;
    comptDominos = 0;
    for (i = 0; i <= 6; i++)
    {
        for (j = 0 + compt; j <= 6; j++)
        {
            dominoCourant.valeur1 = i;
            dominoCourant.valeur2 = j;

            pioche[comptDominos] = dominoCourant;

            printf("|%d %d| ", dominoCourant.valeur1, dominoCourant.valeur2);
            comptDominos++;
        }
        compt++;
        printf("\n");
    }
}

// détermine le nombre de dominos que doit recevoir chaque joueur en fonction de leur nombre
int determine_nb_dominos_main(int totJoueur)
{
    int nbDominosMain;

    if (totJoueur == 2)
        nbDominosMain = 7;
    else if (totJoueur >= 3)
        nbDominosMain = 6;

    return nbDominosMain;
}

// distribue les dominos en fonction du nombre de joueurs, et remplit le tableau mainsJoueurs[]
void distribue_premiers_dominos(int totJoueur)
{
    int i;
    int j;
    DOMINO domChoisi;
    int nbDominosMain;

    nbDominosMain = determine_nb_dominos_main(totJoueur);

    for (i = 0; i < totJoueur; i++)
    {
        for (j = 0; j < nbDominosMain; j++)
        {
            domChoisi = prend_domino_pour_distribue();
            mainJoueurs[i][j] = domChoisi;
        }
    }
}

// choisit aléatoirement un domino dans la pioche[] et le supprime de la pioche
DOMINO prend_domino_pour_distribue()
{
    int alea;
    DOMINO domChoisi;
    DOMINO pasDom;

    pasDom.valeur1 = -1;
    pasDom.valeur2 = -1;
    pasDom.orientation = HORIZONTALE;

    do
    {
        alea = rand() % TAILLE_TAB_DOMINOS;
        domChoisi = pioche[alea];
    } while (domChoisi.valeur1 == -1 && domChoisi.valeur2 == -1);

    if (domChoisi.valeur1 != -1 && domChoisi.valeur2 != -1)
        pioche[alea] = pasDom;

    return domChoisi;
}

// affiche la main des joueurs en parcourant le tableau des mainsJoueurs
void affiche_mains(int totJoueur, char *s[])
{
    int i;
    int j;

    for (i = 0; i < totJoueur; i++)
    {
        printf("%s = ", tabPseudos[i]);
        for (j = 0; j < determine_nb_dominos_main(totJoueur); j++)
        {
            printf("|%d %d| ", mainJoueurs[i][j].valeur1, mainJoueurs[i][j].valeur2);
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

/* FIXME: compte le nombre de double dans la pioche pour déterminer si un joueur a au moins
un double. Cette information est nécessaire pour determine le joueur qui commence.
est appele par la fonction definit_premier_joueurT */
int compte_double_pioche()
{
    int compt;
    int i;

    compt = 0;
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        if (est_double(pioche[i]) && pioche[i].valeur1 != -1)
            compt++;
    }
    return compt;
}

// indique si le domino pris en paramètre est un double ou non
BOOL est_double(DOMINO domino)
{
    if (domino.valeur1 == domino.valeur2)
        return TRUE;

    return FALSE;
}

/* définit le joueur qui commence, et place les mains des joueurs dans l'ordre dans tabPseudos.
  Celui qui a le plus grand double commence, sinon celui qui a le domino le plus fort : 6 5, 6 4, 6 3 ... commence*/
void definit_premier_joueur(char *tabPseudos[], int nbDominosMain)
{
    int i;
    int j;
    int grandDouble;
    int tempDouble;
    int joueurChoisi;
    int nbrDoublePioche;
    DOMINO grandDomino;
    char *pseudoTemp;
    DOMINO *mainTemp;

    grandDouble = 0;
    tempDouble = 0;
    grandDomino.valeur1 = 0;
    grandDomino.valeur2 = 0;
    nbrDoublePioche = compte_double_pioche();
    if (nbrDoublePioche <= 7 && nbrDoublePioche != 0)
    {
        for (i = 0; i < TOT_JOUEURS; i++)
        {
            for (j = 0; j < nbDominosMain; j++)
            {
                if (est_double(mainJoueurs[i][j]))
                {
                    tempDouble = mainJoueurs[i][j].valeur1;

                    if (tempDouble > grandDouble)
                    {
                        grandDouble = tempDouble;
                        joueurChoisi = i;
                    }
                }
            }
        }
        printf("Le joueur qui a le plus grand double est %s, il a |%d %d|\n", tabPseudos[joueurChoisi], grandDouble, grandDouble);
    }
    else
    {
        for (i = 0; i < TOT_JOUEURS; i++)
        {
            for (j = 0; j < nbDominosMain; j++)
            {
                if (mainJoueurs[i][j].valeur1 >= grandDomino.valeur1 && mainJoueurs[i][j].valeur2 >= grandDomino.valeur2)
                {
                    grandDomino.valeur1 = mainJoueurs[i][j].valeur1;
                    grandDomino.valeur2 = mainJoueurs[i][j].valeur2;
                    joueurChoisi = i;
                }
            }
        }
        printf("Le joueur qui a le domino le plus fort est %s, il a |%d %d|\n", tabPseudos[joueurChoisi], grandDomino.valeur1, grandDomino.valeur2);
    }

    // change l'ordre des pseudos dans le tableau des pseudos et l'ordre des mains dans le tableau des mains.
    if (joueurChoisi != 0)
    {
        pseudoTemp = tabPseudos[0];
        tabPseudos[0] = tabPseudos[joueurChoisi];
        tabPseudos[joueurChoisi] = pseudoTemp;

        mainTemp = mainJoueurs[0];
        for (int i = 0; i < 7; ++i)
        {
            mainJoueurs[0][i] = mainJoueurs[joueurChoisi][i];
            mainJoueurs[joueurChoisi][i] = mainTemp[i];
        }
    }
}

// determine qui doit jouer.
int determine_joueur_suivant(int tour, int totJoueur, char *tabPseudos[])
{
    tour++;
    if (tour >= totJoueur)
        tour = 0;

    printf("**** [%d] C'est au tour de %s de jouer ! ****\n", tour, tabPseudos[tour]);
    return tour;
}

// recupere le domino que l'utilisateur a choisi (qu'il veut placer)
DOMINO recupere_choix_domino_main(DOMINO mainActive[])
{
    int choix;

    printf("Choisissez le domino (0, 1, 2, 3, 4, 5, 6) :\n");
    scanf("%d", &choix);
    return mainActive[choix];
}

/*void place_domino(Domino dominoAPlacer)
{
    if ()
    {

    }
}*/