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

    pGauche.x = 410 ; pGauche.y = 750;
    affiche_texte("Nombre joueurs humains : ", 40, pGauche, noir);

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

    pGauche.x = 400 ; pGauche.y = 500;
    affiche_texte("Nombre joueurs ordinateurs : ", 40, pGauche, noir);

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
    POINT pGauche;
    pGauche.x = 0; pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);


}
