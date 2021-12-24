#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mainDominos.h"
#include "libGraphique.h"

#define TAILLE_TAB_DOMINOS 28 // 28 dominos en longueur ou largeur

DOMINO plateau [TAILLE_TAB_DOMINOS][TAILLE_TAB_DOMINOS]; // Plateau de jeu
DOMINO pioche [TAILLE_TAB_DOMINOS]; // pioche
DOMINO mainJoueurs[4][7];

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonctions Dominos                                   //
//////////////////////////////////////////////////////////////////////////////////////////

void main_dominos(NB_JOUEURS joueurs)
{ 
    POINT coin;
    int totJoueur;

    coin.x=100;
    coin.y=200;
    totJoueur = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
    printf("%d Joueurs Humains \n%d IA \n", joueurs.nbJoueurHumain, joueurs.nbJoueurIA);

    affiche_image("./domino.bmp", coin);
    initialise_plateau();
    //affiche_plateau();
    genere_pioche();
    affiche_pioche();
    distribue_premiers_dominos(totJoueur);
    affiche_mains(totJoueur);
    affiche_pioche();
}


void initialise_plateau()
{
    int i;
    int j;
    DOMINO emplacementVide;

    emplacementVide.valeur1 = -1; emplacementVide.valeur2 = -1; emplacementVide.orientation = RIEN;
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        for (j = 0; j < TAILLE_TAB_DOMINOS; j++)
        {
            plateau[i][j]=emplacementVide;
        }
    }

}

void affiche_plateau()
{
    int i;
    int j;
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        for (j = 0; j < TAILLE_TAB_DOMINOS; j++)
        {
            if(plateau[i][j].valeur1 == -1 && plateau[i][j].valeur2 == -1)
                printf("|-1|");
            //printf("|%d %d| ", dominoCourant.valeur1, dominoCourant.valeur2);
        }
        printf("\n");
    }

}

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
        for (j = 0+compt; j <= 6; j++)
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

// cette fonction determine le nombre de dominos que doit recevoir chaque joueur en fonction de leurs nombres
int determine_nb_dominos_main(int totJoueur)
{
    int nbDominosMain;

    if (totJoueur == 2)
        nbDominosMain = 7;
    else if (totJoueur >= 3)
        nbDominosMain = 6;

    return nbDominosMain;
}

// Cette fonction distribue les dominos en fonction du nombre de joueurs, et remplit le tab mainsJoueurs[]
void distribue_premiers_dominos(int totJoueur)
{
    int i;
    int j;
    DOMINO domChoisi;

    if (totJoueur == 2)
    {
        for (i = 0; i < totJoueur; i++)
        {
            for (j = 0; j < determine_nb_dominos_main(totJoueur); j++)
            {
                domChoisi = prend_domino_pour_distribue();
                mainJoueurs[i][j] = domChoisi;
            }
        }
        
    }
    else if (totJoueur >= 3)
    {
       for (i = 0; i < totJoueur; i++)
        {
            for (j = 0; j < determine_nb_dominos_main(totJoueur); j++)
            {
                domChoisi = prend_domino_pour_distribue();
                mainJoueurs[i][j] = domChoisi;
            }
        }
    }
}

// Cette fonction choisi aleatoirement un domino dans la pioche[] et le supprime de la pioche
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
        alea = rand() % TAILLE_TAB_DOMINOS ;
        domChoisi = pioche[alea];
    }while(domChoisi.valeur1 == -1 && domChoisi.valeur2 == -1);

    if (domChoisi.valeur1 != -1 && domChoisi.valeur2 != -1)
        pioche[alea] = pasDom;

    return domChoisi;
}

void affiche_mains(int totJoueur)
{
    int i;
    int j;
   
    for (i = 0; i < totJoueur; i++)
    {
        printf("Joueur %d = ", i);
        for (j = 0; j < determine_nb_dominos_main(totJoueur); j++)
        {
            printf("|%d %d| ", mainJoueurs[i][j].valeur1, mainJoueurs[i][j].valeur2);
        }
        printf("\n");
    }


}

void affiche_pioche()
{
    int i;
   
    printf("---------  La pioche : ----------\n");
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        printf("|%d %d| ", pioche[i].valeur1, pioche[i].valeur2);
       
    }
     printf("\n---------------------------------\n");

}

