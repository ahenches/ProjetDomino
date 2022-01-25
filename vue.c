#include "lib/lib.h"
#include "controleur.h"
#include "vue.h"

void affiche_menu_accueil()
{
    POINT pGauche, pDroit;

    rempli_ecran(bleuclair);

    pGauche.x = 550; pGauche.y = 600;
    affiche_texte("Bienvenue !", 50, pGauche, noir);

    pGauche.x = 500 ; pGauche.y = 500;
    pDroit.x = pGauche.x + 300 ; pDroit.y = pGauche.y - 200;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x = 600; pGauche.y = 420;
    affiche_texte("Jouer", 35, pGauche, noir);
}

void affiche_menu_nombre_joueurs()
{
    rempli_ecran(bleuclair);

}

void affiche_menu_pseudo()
{
    rempli_ecran(bleuclair);

}

void affiche_menu_choix_jeu()
{
    rempli_ecran(bleuclair);

}
