#include "lib/lib.h"
#include "controleur.h"
#include "vue.h"

void affiche_menu_accueil()
{
    POINT pGauche, pDroit;

    pGauche.x = 0; pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    pGauche.x = 500; pGauche.y = 700;
    affiche_texte("Bienvenue !", 50, pGauche, noir);

    //Bouton Jouer
    pGauche.x = 450 ; pGauche.y = 500;
    pDroit.x = pGauche.x + 400 ; pDroit.y = pGauche.y - 200;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x = 590; pGauche.y = 430;
    affiche_texte("Jouer", 40, pGauche, noir);
}

void affiche_menu_nombre_joueurs()
{
    POINT pGauche, pDroit, pNombre;
    int i;

    pGauche.x = 0; pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    //Choix nombre joueurs humains
    pGauche.x = 410 ; pGauche.y = 750;
    affiche_texte("Nombre joueurs humains : ", 40, pGauche, noir);

        //Boutons de choix
    pGauche.x = 520 ; pGauche.y = 630;
    pDroit.x = pGauche.x + COTE_NB_JOUEUR ; pDroit.y = pGauche.y - COTE_NB_JOUEUR;
    pNombre.x = pGauche.x + 15; pNombre.y = pGauche.y - 8;
    for (i = 1 ; i <= 4 ; i++)
    {
        dessine_rectangle_plein(pGauche, pDroit, lightgrey);
        dessine_rectangle(pGauche, pDroit, noir);
        affiche_entier(i, 30, pNombre, noir);

        pGauche.x += COTE_NB_JOUEUR + 30;
        pDroit.x += COTE_NB_JOUEUR + 30;
        pNombre.x += COTE_NB_JOUEUR + 30;
    }

    //Choix nombre de joueurs ordinateurs
    pGauche.x = 400 ; pGauche.y = 500;
    affiche_texte("Nombre joueurs ordinateurs : ", 40, pGauche, noir);

        //Boutons choix
    pGauche.x = 520 ; pGauche.y = 380;
    pDroit.x = pGauche.x + COTE_NB_JOUEUR ; pDroit.y = pGauche.y - COTE_NB_JOUEUR;
    pNombre.x = pGauche.x + 15; pNombre.y = pGauche.y - 8;
    for (i = 0 ; i <= 3 ; i++)
    {
        dessine_rectangle_plein(pGauche, pDroit, lightgrey);
        dessine_rectangle(pGauche, pDroit, noir);
        affiche_entier(i, 30, pNombre, noir);

        pGauche.x += COTE_NB_JOUEUR + 30;
        pDroit.x += COTE_NB_JOUEUR + 30;
        pNombre.x += COTE_NB_JOUEUR + 30;
    }

    //Bouton Confirmer
    pGauche.x = 480 ; pGauche.y = 230;
    pDroit.x = pGauche.x + 400 ; pDroit.y = pGauche.y - 100 ;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x += 100; pGauche.y -= 25;
    affiche_texte("Confirmer", 35, pGauche, noir);
}

void affiche_menu_pseudo(int numeroJoueur)
{
    POINT pGauche;

    pGauche.x = 0; pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    //Affichage du joueur qui doit entrer son pseudo
    pGauche.x = 530; pGauche.y = 600 ;
    affiche_texte("Joueur ", 50, pGauche, noir);
    pGauche.x += 200;
    affiche_entier(numeroJoueur, 50, pGauche, noir);

    pGauche.x = 450; pGauche.y = 480;
    affiche_texte("Entrez votre pseudo", 40, pGauche, noir);

    pGauche.x = 500; pGauche.y = 400;
    affiche_texte("Dans la console", 35, pGauche, noir);
}

void affiche_menu_choix_jeu()
{
    POINT pGauche, pDroit, pTexte;
    pGauche.x = 0; pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    pGauche.x = 440; pGauche.y = 750;
    affiche_texte("A quoi voulez vous jouer ?", 35, pGauche, noir);

    pGauche.x = 650; pGauche.y = 650;
    pDroit.x = 650; pDroit.y = 250;
    dessine_ligne(pGauche,pDroit, noir);

    //Rectangle Dominos
    pGauche.x = 125; pGauche.y = 580;
    pDroit.x = pGauche.x + 400; pDroit.y = pGauche.y - 100;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 110; pTexte.y = pGauche.y - 25;
    affiche_texte("Dominos", 35, pTexte, noir);

    //Rectangle Triominos
    pGauche.x += 650;
    pDroit.x = pGauche.x + 400;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 110;
    affiche_texte("Triominos", 35, pTexte, noir);

    //Rectangles choix Dominos
        //Avec Pioche
    pGauche.x = 155; pGauche.y = 350;
    pDroit.x = pGauche.x + 150; pDroit.y = pGauche.y - 50;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 20; pTexte.y = pGauche.y - 10;
    affiche_texte("Avec Pioche", 20, pTexte, noir);

        //Sans Pioche
    pGauche.x += 190;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 20;
    affiche_texte("Sans Pioche", 20, pTexte, noir);

    //Rectangles choix Triominos
        //Avec Score
    pGauche.x += 460;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 20;
    affiche_texte("Avec Score", 20, pTexte, noir);

        //Sans Score
    pGauche.x += 190;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 20;
    affiche_texte("Sans Score", 20, pTexte, noir);

    //Rectangle jouer
    pGauche.x = 500; pGauche.y = 200;
    pDroit.x = pGauche.x + 300; pDroit.y = pGauche.y - 100;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 110; pTexte.y = pGauche.y - 30;
    affiche_texte("Jouer", 30, pTexte, noir);
}
