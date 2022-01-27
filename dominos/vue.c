#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/lib.h"
#include "../controleur.h"
#include "modele.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonctions de la vue                                 //
//////////////////////////////////////////////////////////////////////////////////////////


// Cette fonction affiche le domino, elle prend en entree le domino a afficher, les coordonnee où l'afficher, et dans quel direction l'afficher
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
        if (domino_a_afficher.valeur1 > domino_a_afficher.valeur2 && direction == HAUT)
        {
            sprintf(nom_image, "./dominos/img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur2, domino_a_afficher.valeur1);
        }
        else if (domino_a_afficher.valeur1 < domino_a_afficher.valeur2 && direction == HAUT)
        {
            sprintf(nom_image, "./dominos/img_dominos/bmp_vertical_inverse/%d%d.bmp", domino_a_afficher.valeur2, domino_a_afficher.valeur1);
        }
        else if (est_double(domino_a_afficher))
        {
            sprintf(nom_image, "./dominos/img_dominos/bmp_horizontal/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
        }
        else
            sprintf(nom_image, "./dominos/img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
    }

    affiche_image(nom_image, coin);
}

// cette fonction affiche le fond
void affiche_fond()
{
    rempli_ecran(blanc); // affiche un fond blanc
    POINT p1;
    p1.x = 1;
    p1.y = 20 + HAUTEUR_MAIN + HAUTEUR_PLATEAU;

    affiche_image("./dominos/img_dominos/tapis.bmp", p1);
}

// cette fonction affiche l'interface en fonction de la variante choisi
void affiche_interface(VARIANTE variante)
{

    POINT p1, p2;
    p1.x = 1;
    p1.y = 100;
    affiche_image("./dominos/img_dominos/bas_tapis.bmp", p1);

    p1.x += LARGEUR_MAIN + 10;

    if (variante == AVEC_PIOCHE)
    {
        // affiche le mot "Pioche"
        p1.y = HAUTEUR_MAIN + 5;
        // affiche_texte("Pioche", 18, p1, lightgoldenrodyellow);

        // affiche le nombre de dominos dans la pioche
        p1.x = 1265;
        p1.y = 75;
        char nombre_dominos_pioche[4];
        sprintf(nombre_dominos_pioche, "%d", compte_dominos_pioche());      //écrit le nombre de dominos restant dans la pioche dans un tableau de char
        affiche_texte(nombre_dominos_pioche, 18, p1, lightgoldenrodyellow); // affiche le nombre contenu dans ce tableau

        // affiche un domino décoratif pour représenter la pioche
        p1.x = 1220;
        p1.y = HAUTEUR - 805;
        affiche_image("./dominos/img_dominos/verso_domino.bmp", p1);
    }
    else // affiche "Passer son tour"
    {
        p1.y = BORDURE;
        p2.x = p1.x + LARGEUR_PIOCHE;
        p2.y = p1.y + HAUTEUR_MAIN;
        dessine_rectangle(p1, p2, lightgoldenrodyellow);
        p1.x += 50;
        p1.y = HAUTEUR_MAIN / 2 + 50;
        affiche_texte("Passer", 18, p1, lightgoldenrodyellow);
        p1.y = p1.y - 30;
        p1.x = p1.x - 8;
        affiche_texte("son tour", 18, p1, lightgoldenrodyellow);
    }

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

// Cette fonction affiche la main du joueur, elle prend en paramettre les infos des joueur, et le tour pour determiné de quel joueur on parle
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
    else // si est une IA
    {
        POINT coordonnees_phrase;
        coordonnees_phrase.x = 500;
        coordonnees_phrase.y = 850;
        affiche_texte("l'IA choisit son meilleur coup...", 18, coordonnees_phrase, noir);
        for (i = 0; i < NB_MAX_DOMINO_MAIN; i++) // alors on affiche tous les dominos de sa main retournés
        {
            coordonnees_domino.x = LARGEUR_PIOCHE - 50 + i * 50;
            if (infos_joueurs[tour].mainJoueur[i].valeur1 != -1)
            {
                for (i = 0; i < NB_MAX_DOMINO_MAIN; i++) // alors on affiche tous les dominos de sa main
                {
                    coordonnees_domino.x = LARGEUR_PIOCHE - 50 + i * 50;
                    if (infos_joueurs[tour].mainJoueur[i].valeur1 != -1)
                    {
                        affiche_image("./dominos/img_dominos/verso_domino.bmp", coordonnees_domino);
                        actualise_affichage();
                    }
                }
                actualise_affichage();
            }
        }
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

void affiche_domino_main(DOMINO domino_a_afficher, POINT coin) // affiche un domino dans la main d'un joueur humain
{
    char nom_image[100];

    sprintf(nom_image, "./dominos/img_dominos/bmp_vertical/%d%d.bmp", domino_a_afficher.valeur1, domino_a_afficher.valeur2);
    affiche_image(nom_image, coin);
}