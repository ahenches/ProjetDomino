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
void affiche_pioche_domino()
{
    int i;

    printf("---------  La pioche : ----------\n");
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        if (pioche_domino[i].valeur1 != -1)
            printf("|%d %d| ", pioche_domino[i].valeur1, pioche_domino[i].valeur2);
    }
    printf("\n---------------------------------\n");
}

void affiche_domino(DOMINO domino_a_afficher, POINT coin, EXTREMITE_COMPATIBLE direction)
{
    char nom_image[100];

    if (domino_a_afficher.orientation == HORIZONTALE)
    {
        if (domino_a_afficher.valeur1 > domino_a_afficher.valeur2)
        {
            sprintf(nom_image, "./dominos/img_dominos/bmp_horizontal/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
        }
        else if (est_double(domino_a_afficher) && direction == DROITE)
        {
            sprintf(nom_image, "./dominos/img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
            coin.y += 20;
        }
        else if (est_double(domino_a_afficher) && direction == GAUCHE)
        {
            sprintf(nom_image, "./dominos/img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
            coin.y += 20;
        }
        else
            sprintf(nom_image, "./dominos/img_dominos/bmp_horizontal_inverse/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
    }
    if (domino_a_afficher.orientation == VERTICALE)
    {
        if (domino_a_afficher.valeur1 > domino_a_afficher.valeur2)
        {
            sprintf(nom_image, "./dominos/img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur2, domino_a_afficher.valeur1);
        }
        else if (est_double(domino_a_afficher))
        {
            sprintf(nom_image, "./dominos/img_dominos/bmp_horizontal/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
        }
        else
            sprintf(nom_image, "./dominos/img_dominos/bmp_vertical_inverse/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
    }

    affiche_image(nom_image, coin);
    printf("///////Le domino a ete affiche avec SUCCES///////\n");
}
void affiche_fond()
{
    rempli_ecran(blanc); // affiche un fond blanc
    POINT p1;
    /*POINT p2;
    p1.x = BORDURE;
    p1.y = 20 + HAUTEUR_MAIN;
    p2.x = p1.x + LARGEUR_PLATEAU;
    p2.y = p1.y + HAUTEUR_PLATEAU;
    dessine_rectangle_plein(p1, p2, 0x50D3D0);
    dessine_rectangle(p1, p2, gris);*/
    p1.x = 1;
    p1.y = 20 + HAUTEUR_MAIN + HAUTEUR_PLATEAU;

    affiche_image("./dominos/img_dominos/tapis.bmp", p1);
}

void affiche_interface(VARIANTE variante)
{

    POINT p1, p2;
    p1.x = 1;
    p1.y = 100;
    affiche_image("./dominos/img_dominos/bas_tapis.bmp", p1);

    // Affiche la case qui contient la main du joueur
    p1.x = BORDURE;
    p1.y = 10;
    p2.x = p1.x + LARGEUR_MAIN;
    p2.y = p1.y + HAUTEUR_MAIN;
    /*dessine_rectangle_plein(p1, p2, lightgrey);
    dessine_rectangle(p1, p2, gris);*/

    // affiche la case qui contient le bouton pour piocher ou passer son tour
    p1.x = p2.x + 10;
    p2.x = p1.x + LARGEUR_PIOCHE;
    // dessine_rectangle_plein(p1, p2, lightgrey);
    dessine_rectangle(p1, p2, gris);

    // affiche le mot "main"
    p1.x = BORDURE + 5;
    p1.y = HAUTEUR_MAIN + 5;
    /*affiche_texte("Main", 18, p1, noir);*/

    if (variante == AVEC_PIOCHE)
    {
        // affiche le mot "Pioche"
        p1.x += LARGEUR_MAIN + 10;
        affiche_texte("Pioche", 18, p1, noir);

        // affiche le nombre de dominos dans la pioche
        p1.x = p1.x + 10;
        p1.y = p1.y - 20;
        char nombre_dominos_pioche[4];
        sprintf(nombre_dominos_pioche, "(%d)", compte_dominos_pioche()); //écrit le nombre de dominos restant dans la pioche dans un tableau de char
        affiche_texte(nombre_dominos_pioche, 18, p1, noir);              // affiche le nombre contenu dans ce tableau

        // affiche un domino décoratif pour représenter la pioche
        POINT coordonnees_image;
        coordonnees_image.x = 1220;
        coordonnees_image.y = HAUTEUR - 805;
        affiche_image("./dominos/img_dominos/pioche.bmp", coordonnees_image);
    }
    else // affiche "Passer son tour"
    {
        p1.x += LARGEUR_MAIN + 50;
        p1.y = p1.y - 18;
        affiche_texte("Passer", 18, p1, noir);
        p1.y = p1.y - 30;
        p1.x = p1.x - 8;
        affiche_texte("son tour", 18, p1, noir);
    }

    /*// Affiche plateau
    p1.x = BORDURE;
    p1.y = 20 + HAUTEUR_MAIN;
    p2.x = p1.x + LARGEUR_PLATEAU;
    p2.y = p1.y + HAUTEUR_PLATEAU;
    dessine_rectangle_plein(p1, p2, blanc);
    dessine_rectangle(p1, p2, gris);*/

    // affiche bouton quitter
    p1.x = ABSCISSE_BOUTON_QUITTER;
    p1.y = ORDONNEE_BOUTON_QUITTER;
    p2.x = ABSCISSE_BOUTON_QUITTER + 80;
    p2.y = ORDONNEE_BOUTON_QUITTER + 40;
    dessine_rectangle_plein(p1, p2, lightgrey);
    dessine_rectangle(p1, p2, gris);
    p1.x = p1.x + 10;
    p1.y = p1.y + 33;
    affiche_texte("Quitter", 17, p1, noir);
}

void affiche_victoire(int gagnant, JOUEUR infos_joueurs[])
{
    if (gagnant == -2)
        printf("*** EGALITE Personne n'a gagne ***\n");
    else
    {
        printf("*** C'est le JOUEUR n %d : %s qui a gagne !!! ***\n", gagnant, infos_joueurs[gagnant].pseudo);
        printf("*** SCORE : %d ***\n", infos_joueurs[gagnant].score);
    }
}

void affiche_main(JOUEUR *infos_joueurs, int tour)
{
    int i;
    POINT coordonnees_domino;
    coordonnees_domino.y = HAUTEUR_MAIN - 5;
    POINT p1_rectangle, p2_rectangle; // on efface le message "l'IA choisit son meilleur coup"
    p1_rectangle.x = 500;
    p1_rectangle.y = 850;
    p2_rectangle.x = p1_rectangle.x + 350;
    p2_rectangle.y = 850 - 26;
    dessine_rectangle_plein(p1_rectangle, p2_rectangle, blanc); // on dessine un rectangle pour effacer le nom du joueur précédent

    if ((strcmp(infos_joueurs[tour].pseudo, "IA0") != 0) && (strcmp(infos_joueurs[tour].pseudo, "IA1") != 0) && (strcmp(infos_joueurs[tour].pseudo, "IA2") != 0))
    { // si le joueur n'est pas une IA

        for (i = 0; i < NB_MAX_DOMINO_MAIN; i++) // alors on affiche tous les dominos de sa main
        {
            coordonnees_domino.x = LARGEUR_PIOCHE - 50 + i * 50;
            if (infos_joueurs[tour].mainJoueur[i].valeur1 != -1)
            {
                affiche_domino_main(infos_joueurs[tour].mainJoueur[i], coordonnees_domino);
                actualise_affichage();
            }
        }
    }
    else
    {
        POINT coordonnees_phrase;
        coordonnees_phrase.x = 500;
        coordonnees_phrase.y = 850;
        affiche_texte("l'IA choisit son meilleur coup...", 18, coordonnees_phrase, noir);
    }
}

void affiche_tour(char pseudo[]) // affiche le pseudo du joueur dont c'est le tour en haut à gauche de l'écran
{

    POINT coordonnees_phrase, p1_rectangle, p2_rectangle;
    coordonnees_phrase.x = 20;
    coordonnees_phrase.y = 850;
    p1_rectangle.x = coordonnees_phrase.x;
    p1_rectangle.y = coordonnees_phrase.y;
    p2_rectangle.x = p1_rectangle.x + 350;
    p2_rectangle.y = coordonnees_phrase.y - 26;
    dessine_rectangle_plein(p1_rectangle, p2_rectangle, blanc); // on dessine un rectangle pour effacer le nom du joueur précédent
    char phrase_a_afficher[50];
    sprintf(phrase_a_afficher, "C'est au tour de: %s", pseudo);
    affiche_texte(phrase_a_afficher, 18, coordonnees_phrase, noir);
}

void affiche_domino_main(DOMINO domino_a_afficher, POINT coin)
{
    char nom_image[100];

    sprintf(nom_image, "./dominos/img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
    affiche_image(nom_image, coin);
}