#include "dominos.h"
#include "modele.h"
#include "controleur.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonctions de la vue                                 //
//////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui parcourt le tableau des pseudos et qui affiche les pseudos des joueurs
void affiche_pseudos(JOUEUR infos_joueurs[], int totJoueur)
{
    int i;

    for (i = 0; i < totJoueur; i++)
    {
        printf("%s\n", infos_joueurs[i].pseudo);
    }
}

// Fonction qui affiche le plateau de jeu en parcourant le tableau de jeu
void affiche_plateau()
{
    int i;
    int j;
    printf("\n\n         ");
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        for (j = 0; j < TAILLE_TAB_DOMINOS; j++)
        {
            /*if (plateau[i][j].valeur1 == -1 && plateau[i][j].valeur2 == -1)
                printf("|-1|");*/
            if (plateau[i][j].valeur1 != -1 && plateau[i][j].valeur2 != -1)
                printf("|%d %d| ", plateau[i][j].valeur1, plateau[i][j].valeur2);
        }
        if (plateau[i][j].valeur1 != -1 && plateau[i][j].valeur2 != -1)
            printf("\n\n");
    }
}

// affiche la main des joueurs en parcourant le tableau des mainsJoueurs
void affiche_mains(int totJoueur, JOUEUR infos_joueurs[])
{
    int i;
    int j;

    for (i = 0; i < totJoueur; i++)
    {
        printf("%s = ", infos_joueurs[i].pseudo);
        for (j = 0; j < NB_MAX_DOMINO_MAIN; j++)
        {
            if (infos_joueurs[i].mainJoueur[j].valeur1 != -1)
            {
                printf("(%d)|%d %d| ", j, infos_joueurs[i].mainJoueur[j].valeur1, infos_joueurs[i].mainJoueur[j].valeur2);
            }
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

void affiche_domino(DOMINO domino_a_afficher, POINT coin)
{
    char nom_image[100];
    sprintf(nom_image, "./img_dominos/bmp/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
    affiche_image(nom_image, coin);
}

void affiche_fond()
{

    POINT p1, p2;

    rempli_ecran(bleuclair);

    // Affiche main
    p1.x = BORDURE;
    p1.y = 10;
    p2.x = p1.x + LARGEUR_MAIN;
    p2.y = p1.y + HAUTEUR_MAIN;
    dessine_rectangle_plein(p1, p2, lightgrey);
    dessine_rectangle(p1, p2, gris);

    // Affiche pioche
    p1.x = p2.x + 10;
    p2.x = p1.x + LARGEUR_PIOCHE;
    dessine_rectangle_plein(p1, p2, lightgrey);
    dessine_rectangle(p1, p2, gris); // affiche le conteneur de la pioche

    POINT coordonnees_image;
    coordonnees_image.x = 1190;
    coordonnees_image.y = 805;
    affiche_image("./img_dominos/bmp/pioche.bmp", coordonnees_image); // affiche un domino décoratif

    // textes à afficher
    p1.x = BORDURE + 5;
    p1.y = HAUTEUR_MAIN + 5;
    affiche_texte("Main", 18, p1, noir);
    p1.x += LARGEUR_MAIN + 10;
    affiche_texte("Pioche", 18, p1, noir);
    p1.x = p1.x + 10;
    p1.y = p1.y - 20;
    char nombre_dominos_pioche[4];
    sprintf(nombre_dominos_pioche, "(%d)", compte_dominos_pioche()); //écrit le nombre de dominos restant dans la pioche dans un tableau de char
    affiche_texte(nombre_dominos_pioche, 18, p1, noir);              // affiche le nombre contenu dans le tableau

    // Affiche plateau
    p1.x = BORDURE;
    p1.y = 20 + HAUTEUR_MAIN;
    p2.x = p1.x + LARGEUR_PLATEAU;
    p2.y = p1.y + HAUTEUR_PLATEAU;
    dessine_rectangle_plein(p1, p2, blanc);
    dessine_rectangle(p1, p2, gris);
}

void affiche_victoire(int gagnant, JOUEUR infos_joueurs[])
{
    if (gagnant == -2)
        printf("*** EGALITE Personne n'a gagné ***\n");
    else
    {
        printf("*** C'est le JOUEUR n %d : %s qui a gagné !!! ***\n", gagnant, infos_joueurs[gagnant].pseudo);
        printf("*** SCORE : %d ***\n", infos_joueurs[gagnant].score);
    }
}