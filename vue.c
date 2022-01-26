#include "lib/lib.h"
#include "controleur.h"
#include "vue.h"

void affiche_menu_accueil()
{
    POINT pGauche, pDroit;

    pGauche.x = 0;
    pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    pGauche.x = 500;
    pGauche.y = 700;
    affiche_texte("Bienvenue !", 50, pGauche, noir);

    // Bouton Jouer
    pGauche.x = 450;
    pGauche.y = 500;
    pDroit.x = pGauche.x + 400;
    pDroit.y = pGauche.y - 200;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x = 590;
    pGauche.y = 430;
    affiche_texte("Jouer", 40, pGauche, noir);
}

void affiche_menu_nombre_joueurs()
{
    POINT pGauche, pDroit, pNombre;
    int i;

    pGauche.x = 0;
    pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    // Choix nombre joueurs humains
    pGauche.x = 410;
    pGauche.y = 750;
    affiche_texte("Nombre joueurs humains : ", 40, pGauche, noir);

    // Boutons de choix
    pGauche.x = 520;
    pGauche.y = 630;
    pDroit.x = pGauche.x + COTE_NB_JOUEUR;
    pDroit.y = pGauche.y - COTE_NB_JOUEUR;
    pNombre.x = pGauche.x + 15;
    pNombre.y = pGauche.y - 8;
    for (i = 1; i <= 4; i++)
    {
        dessine_rectangle_plein(pGauche, pDroit, lightgrey);
        dessine_rectangle(pGauche, pDroit, noir);
        affiche_entier(i, 30, pNombre, noir);

        pGauche.x += COTE_NB_JOUEUR + 30;
        pDroit.x += COTE_NB_JOUEUR + 30;
        pNombre.x += COTE_NB_JOUEUR + 30;
    }

    // Choix nombre de joueurs ordinateurs
    pGauche.x = 400;
    pGauche.y = 500;
    affiche_texte("Nombre joueurs ordinateurs : ", 40, pGauche, noir);

    // Boutons choix
    pGauche.x = 520;
    pGauche.y = 380;
    pDroit.x = pGauche.x + COTE_NB_JOUEUR;
    pDroit.y = pGauche.y - COTE_NB_JOUEUR;
    pNombre.x = pGauche.x + 15;
    pNombre.y = pGauche.y - 8;
    for (i = 0; i <= 3; i++)
    {
        dessine_rectangle_plein(pGauche, pDroit, lightgrey);
        dessine_rectangle(pGauche, pDroit, noir);
        affiche_entier(i, 30, pNombre, noir);

        pGauche.x += COTE_NB_JOUEUR + 30;
        pDroit.x += COTE_NB_JOUEUR + 30;
        pNombre.x += COTE_NB_JOUEUR + 30;
    }

    // Bouton Confirmer
    pGauche.x = 480;
    pGauche.y = 230;
    pDroit.x = pGauche.x + 400;
    pDroit.y = pGauche.y - 100;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x += 100;
    pGauche.y -= 25;
    affiche_texte("Confirmer", 35, pGauche, noir);
}

void affiche_menu_pseudo(int numeroJoueur)
{
    POINT pGauche;

    pGauche.x = 0;
    pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    // Affichage du joueur qui doit entrer son pseudo
    pGauche.x = 530;
    pGauche.y = 600;
    affiche_texte("Joueur ", 50, pGauche, noir);
    pGauche.x += 200;
    affiche_entier(numeroJoueur, 50, pGauche, noir);

    pGauche.x = 450;
    pGauche.y = 480;
    affiche_texte("Entrez votre pseudo", 40, pGauche, noir);

    pGauche.x = 500;
    pGauche.y = 400;
    affiche_texte("Dans la console", 35, pGauche, noir);
}

void affiche_menu_choix_jeu()
{
    POINT pGauche, pDroit, pTexte;

    pGauche.x = 0;
    pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    pGauche.x = 440;
    pGauche.y = 750;
    affiche_texte("A quoi voulez vous jouer ?", 35, pGauche, noir);

    pGauche.x = 650;
    pGauche.y = 650;
    pDroit.x = 650;
    pDroit.y = 250;
    dessine_ligne(pGauche, pDroit, noir);

    // Bouton Dominos
    pGauche.x = 125;
    pGauche.y = 580;
    pDroit.x = pGauche.x + 400;
    pDroit.y = pGauche.y - 100;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 110;
    pTexte.y = pGauche.y - 25;
    affiche_texte("Dominos", 35, pTexte, noir);

    // Bouton Triominos
    pGauche.x += 650;
    pDroit.x = pGauche.x + 400;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 110;
    affiche_texte("Triominos", 35, pTexte, noir);

    // Boutons choix Dominos
    // Avec Pioche
    pGauche.x = 155;
    pGauche.y = 350;
    pDroit.x = pGauche.x + 150;
    pDroit.y = pGauche.y - 50;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 20;
    pTexte.y = pGauche.y - 10;
    affiche_texte("Avec Pioche", 20, pTexte, noir);

    // Sans Pioche
    pGauche.x += 190;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 20;
    affiche_texte("Sans Pioche", 20, pTexte, noir);

    // Boutons choix Triominos
    // Avec Score
    pGauche.x += 460;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 20;
    affiche_texte("Avec Score", 20, pTexte, noir);

    // Sans Score
    pGauche.x += 190;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 20;
    affiche_texte("Sans Score", 20, pTexte, noir);

    // Bouton jouer
    pGauche.x = 500;
    pGauche.y = 200;
    pDroit.x = pGauche.x + 300;
    pDroit.y = pGauche.y - 100;
    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);

    pTexte.x = pGauche.x + 110;
    pTexte.y = pGauche.y - 30;
    affiche_texte("Jouer", 30, pTexte, noir);
}

void affiche_menu_classement()
{
    POINT pGauche, pDroit, pTexte;
    FILE *fichier = NULL;
    char texte[500] = "";

    pGauche.x = 0;
    pGauche.y = 900;
    affiche_image("./fond.bmp", pGauche);

    pTexte.x = 510;
    pTexte.y = 750;
    affiche_texte("Classement", 40, pTexte, noir);

    fichier = fopen("./classement.txt", "r");

    // Tableau du classement
    pGauche.x = 450;
    pGauche.y = 650;
    pDroit.x = pGauche.x + 400;
    pDroit.y = pGauche.y - 100;
    pTexte.x = pGauche.x + 30;
    pTexte.y = pGauche.y - 40;
    if (fichier != NULL)
    {
        while (fgets(texte, 500, fichier) != NULL)
        {
            dessine_rectangle_plein(pGauche, pDroit, bleuclair);
            dessine_rectangle(pGauche, pDroit, noir);
            affiche_texte(texte, 20, pTexte, noir);
            pGauche.y -= 100;
            pDroit.y -= 100;
            pTexte.y -= 100;
        }
        fclose(fichier);
    }

    // Boutons Rejouer et Quitter
    pGauche.x = 425;
    pGauche.y = 200;
    pDroit.x = pGauche.x + 200;
    pDroit.y = pGauche.y - 100;
    pTexte.x = pGauche.x + 40;
    pTexte.y = pGauche.y - 30;

    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);
    affiche_texte("Rejouer", 30, pTexte, noir);

    pGauche.x += 250;
    pDroit.x += 250;
    pTexte.x += 250;

    dessine_rectangle_plein(pGauche, pDroit, lightgrey);
    dessine_rectangle(pGauche, pDroit, noir);
    affiche_texte("Quitter", 30, pTexte, noir);
}

void affiche_selection_nb_joueurs_humains(int nbHumains)
{
    POINT pGauche, pDroit;

    // Met en evidence le nombre selectionné, efface la selection precedente
    pGauche.x = 520;
    pGauche.y = 630;
    pDroit.x = pGauche.x + COTE_NB_JOUEUR;
    pDroit.y = pGauche.y - COTE_NB_JOUEUR;
    for (int i = 1; i <= 4; i++)
    {
        if (i == nbHumains)
            dessine_rectangle(pGauche, pDroit, rouge);
        else
            dessine_rectangle(pGauche, pDroit, noir);
        pGauche.x += COTE_NB_JOUEUR + 30;
        pDroit.x += COTE_NB_JOUEUR + 30;
    }
}

void affiche_selection_nb_joueurs_ordi(int nbOrdi)
{
    POINT pGauche, pDroit;

    // Met en evidence le nombre selectionné, efface la selection precedente
    pGauche.x = 520;
    pGauche.y = 380;
    pDroit.x = pGauche.x + COTE_NB_JOUEUR;
    pDroit.y = pGauche.y - COTE_NB_JOUEUR;
    for (int i = 0; i <= 3; i++)
    {
        if (i == nbOrdi)
            dessine_rectangle(pGauche, pDroit, rouge);
        else
            dessine_rectangle(pGauche, pDroit, noir);

        pGauche.x += COTE_NB_JOUEUR + 30;
        pDroit.x += COTE_NB_JOUEUR + 30;
    }
}

void affiche_selection_jeu(JEU jeuSelect)
{
    POINT pGauche, pDroit;

    // Efface la selection precedente des variantes
    pGauche.x = 155;
    pGauche.y = 350;
    pDroit.x = pGauche.x + 150;
    pDroit.y = pGauche.y - 50;
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x += 190;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x += 460;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x += 190;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle(pGauche, pDroit, noir);

    // affiche la selection du jeu
    pGauche.x = 125;
    pGauche.y = 580;
    pDroit.x = pGauche.x + 400;
    pDroit.y = pGauche.y - 100;
    if (jeuSelect == DOMINOS)
    {
        dessine_rectangle(pGauche, pDroit, rouge);
        pGauche.x += 650;
        pDroit.x = pGauche.x + 400;
        dessine_rectangle(pGauche, pDroit, noir);
    }
    else
    {
        dessine_rectangle(pGauche, pDroit, noir);
        pGauche.x += 650;
        pDroit.x = pGauche.x + 400;
        dessine_rectangle(pGauche, pDroit, rouge);
    }
}

void affiche_selection_variante(VARIANTE varSelect)
{
    POINT pGauche, pDroit;

    // Efface la selection precedente
    pGauche.x = 155;
    pGauche.y = 350;
    pDroit.x = pGauche.x + 150;
    pDroit.y = pGauche.y - 50;
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x += 190;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x += 460;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle(pGauche, pDroit, noir);

    pGauche.x += 190;
    pDroit.x = pGauche.x + 150;
    dessine_rectangle(pGauche, pDroit, noir);

    // Affiche la nouvelle selection
    switch (varSelect)
    {
    case SANS_PIOCHE:
        affiche_selection_jeu(DOMINOS);
        pGauche.x = 345;
        pGauche.y = 350;
        pDroit.x = pGauche.x + 150;
        pDroit.y = pGauche.y - 50;
        dessine_rectangle(pGauche, pDroit, rouge);
        break;
    case AVEC_PIOCHE:
        affiche_selection_jeu(DOMINOS);
        pGauche.x = 155;
        pGauche.y = 350;
        pDroit.x = pGauche.x + 150;
        pDroit.y = pGauche.y - 50;
        dessine_rectangle(pGauche, pDroit, rouge);
        break;
    case AVEC_SCORE:
        affiche_selection_jeu(TRIOMINOS);
        pGauche.x = 805;
        pGauche.y = 350;
        pDroit.x = pGauche.x + 150;
        pDroit.y = pGauche.y - 50;
        dessine_rectangle(pGauche, pDroit, rouge);
        break;
    default:
        affiche_selection_jeu(TRIOMINOS);
        pGauche.x = 995;
        pGauche.y = 350;
        pDroit.x = pGauche.x + 150;
        pDroit.y = pGauche.y - 50;
        dessine_rectangle(pGauche, pDroit, rouge);
    }
}
