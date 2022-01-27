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
//                                  Fonctions du modele                                 //
//////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui initialise le plateau
void initialise_plateau_domino()
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

void initialise_joueurs(JOUEUR infos_joueurs[], int totJoueurs)
{
    int i;
    int j;
    DOMINO emplacementVide;

    emplacementVide.valeur1 = -1;
    emplacementVide.valeur2 = -1;
    emplacementVide.orientation = RIEN;
    for (i = 0; i < totJoueurs; i++)
    {
        for (j = 0; j < NB_MAX_DOMINO_MAIN; j++)
        {
            infos_joueurs[i].mainJoueur[j] = emplacementVide;
        }
        infos_joueurs[i].score = 0;
    }
}

NB_JOUEURS entre_nb_joueurs(NB_JOUEURS joueurs)
{
    do
    {
        printf("Choisissez le nombre de joueurs Humain :\n");
        scanf("%d", &joueurs.nbJoueurHumain);
    } while (joueurs.nbJoueurHumain > 4 || joueurs.nbJoueurHumain < 0);

    do
    {
        printf("Choisissez le nombre de joueurs Ordinateur :\n");
        scanf("%d", &joueurs.nbJoueurIA);
    } while (joueurs.nbJoueurIA > 3 || joueurs.nbJoueurIA < 0);

    printf("-------------------------\n");
    return joueurs;
}

void entre_pseudos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs)
{
    int i;
    int compt;
    int totJoueurs;

    totJoueurs = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
    compt = 1;

    for (i = 0; i < joueurs.nbJoueurHumain; i++)
    {
        printf("Choisissez votre pseudo :\n");
        // infos_joueurs[i].pseudo = (char *)malloc(25);
        scanf("%s", infos_joueurs[i].pseudo);

        if (strlen(infos_joueurs[i].pseudo) > 25)
        {
            do
            {
                printf("\nVeillez respecter la limite maximale de 25 charactères.\n");
                scanf("%s", infos_joueurs[i].pseudo);
            } while (strlen(infos_joueurs[i].pseudo) > 25);
        }
    }

    for (i = joueurs.nbJoueurHumain; i < totJoueurs; i++)
    {
        // tabPseudos[i] = (char *)malloc(25);
        sprintf(infos_joueurs[i].pseudo, "IA%d", compt);
        compt++;
    }

    printf("-------------------------\n");
}

VARIANTE choix_variante()
{
    int choix;
    printf("Choisissez la variante : 0 SANS Pioche, 1 AVEC Pioche : \n");
    scanf("%d", &choix);

    return choix;
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

            pioche_domino[comptDominos] = dominoCourant;

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
void distribue_premiers_dominos(JOUEUR infos_joueurs[], int totJoueur)
{
    int i;
    int j;
    int nbDominosMain;

    nbDominosMain = determine_nb_dominos_main(totJoueur);

    for (i = 0; i < totJoueur; i++)
    {
        for (j = 0; j < nbDominosMain; j++)
        {
            pioche_un_domino(&infos_joueurs[i]);
        }
    }
}

DOMINO pioche_un_domino(JOUEUR *infos_joueur) // ajoute le domino pioché à la main du joueur, renvoie le domino choisi pour que l'IA le joue directement
{
    int alea;
    int i;
    DOMINO domChoisi;
    DOMINO pasDom;

    pasDom.valeur1 = -1;
    pasDom.valeur2 = -1;
    pasDom.orientation = HORIZONTALE;
    i = 0;
    do
    {
        alea = rand() % TAILLE_TAB_DOMINOS;
        domChoisi = pioche_domino[alea];
    } while (domChoisi.valeur1 == -1 && domChoisi.valeur2 == -1);

    if (domChoisi.valeur1 != -1 && domChoisi.valeur2 != -1)
        pioche_domino[alea] = pasDom;

    for (i = 0; i < NB_MAX_DOMINO_MAIN; i++)
    {

        if (infos_joueur->mainJoueur[i].valeur1 == -1) // si on parcourt une case dans laquelle il n'y a pas de domino
        {
            infos_joueur->mainJoueur[i] = domChoisi; // on stocke le domino dans la case
            i = NB_MAX_DOMINO_MAIN + 1;              // on arrête la boucle
        }
    }

    return domChoisi;
}

/*compte le nombre de double dans la pioche pour déterminer si un joueur a au moins
un double. Cette information est nécessaire pour determine le joueur qui commence.
est appele par la fonction definit_premier_joueurT */
int compte_double_pioche()
{
    int compt;
    int i;

    compt = 0;
    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        if (est_double(pioche_domino[i]) && pioche_domino[i].valeur1 != -1)
            compt++;
    }
    return compt;
}

// indique si le domino pris en paramètre est un double ou non
BOOL est_double(DOMINO domino)
{
    if ((domino.valeur1 == domino.valeur2) && (domino.valeur1 >= 0))
    {
        return VRAI;
    }

    return FALSE;
}

/* définit le joueur qui commence, et place les mains des joueurs dans l'ordre dans tabPseudos.
  Celui qui a le plus grand double commence, sinon celui qui a le domino le plus fort : 6 5, 6 4, 6 3 ... commence*/
void definit_premier_joueur(JOUEUR infos_joueurs[], int nbDominosMain)
{
    int i;
    int j;
    int grandDouble;
    int tempDouble;
    int joueurChoisi;
    int nbrDoublePioche;
    DOMINO grandDomino;
    JOUEUR joueurTemp;

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
                if (est_double(infos_joueurs[i].mainJoueur[j]))
                {
                    tempDouble = infos_joueurs[i].mainJoueur[j].valeur1;

                    if (tempDouble > grandDouble)
                    {
                        grandDouble = tempDouble;
                        joueurChoisi = i;
                    }
                }
            }
        }
        printf("Le joueur qui a le plus grand double est %s, il a |%d %d|\n\n\n", infos_joueurs[joueurChoisi].pseudo, grandDouble, grandDouble);
    }
    else
    {
        for (i = 0; i < TOT_JOUEURS; i++)
        {
            for (j = 0; j < nbDominosMain; j++)
            {
                if (infos_joueurs[i].mainJoueur[j].valeur1 >= grandDomino.valeur1 && infos_joueurs[i].mainJoueur[j].valeur2 >= grandDomino.valeur2)
                {
                    grandDomino.valeur1 = infos_joueurs[i].mainJoueur[j].valeur1;
                    grandDomino.valeur2 = infos_joueurs[i].mainJoueur[j].valeur2;
                    joueurChoisi = i;
                }
            }
        }
        printf("Le joueur qui a le domino le plus fort est %s, il a |%d %d|\n\n\n", infos_joueurs[joueurChoisi].pseudo, grandDomino.valeur1, grandDomino.valeur2);
    }

    // change l'ordre des pseudos dans le tableau des pseudos et l'ordre des mains dans le tableau des mains.
    if (joueurChoisi != 0)
    {
        joueurTemp = infos_joueurs[0];
        infos_joueurs[0] = infos_joueurs[joueurChoisi];
        infos_joueurs[joueurChoisi] = joueurTemp;
    }
}

// determine qui doit jouer.
int determine_joueur_suivant(int tour, int totJoueur, JOUEUR infos_joueurs[])
{
    tour++;
    if (tour >= totJoueur)
        tour = 0;

    printf("**** [%d] C'est au tour de %s de jouer ! ****\n", tour, infos_joueurs[tour].pseudo);
    return tour;
}

// recupere le domino que l'utilisateur a choisi (qu'il veut placer)
DOMINO recupere_choix_domino_main(DOMINO mainActive[], COORDONNEES indicesExtremite1, COORDONNEES indicesExtremite2)
{
    printf(" on entre dans recupere_choix_domino");
    int choix;
    BOOL choix_est_valable = FAUX;

    do
    {
        printf(" recupere_choix_domino_main appelle gere_clic");
        choix = gere_clics(mainActive);

        if (choix == -2)
        {
            printf("choix == -2 dans recupere_choix_domino_main");
            if (!verifie_compatibilite_main(mainActive, indicesExtremite1, indicesExtremite2))
            {
                DOMINO passeTour;
                passeTour.valeur1 = -2;
                passeTour.valeur2 = -2;
                return passeTour;
            }
            else
            {
                printf("choix non valable donc on boucle (normalement)");
                // choix_est_valable = FAUX;
            }
        }
        else if (choix == -3)
        {
            printf("choix == -3 dans recupere_choic_domino_main");
            DOMINO quitter;
            quitter.valeur1 = -3;
            quitter.valeur2 = -3;
            return quitter;
        }
        else if (choix == -1)
        {
            // choix_est_valable = FAUX;
            printf("choix non valable donc on boucle (normalement)");
        }
        else
        {
            printf("return mainActive[choix]");
            return mainActive[choix];
        }
    } while (choix_est_valable == FAUX);

    return mainActive[0];
}

/*DOMINO recupere_choix_domino_main(DOMINO mainActive[], COORDONNEES indicesExtremite1, COORDONNEES indicesExtremite2)
{
    int choix;

    choix = -1;
    do
    {
        printf("Choisissez le domino (0, 1, 2, 3, 4, 5, 6) :\n");
        scanf("%d", &choix);

        if (choix == -2)
        {
            if (!verifie_compatibilite_main(mainActive, indicesExtremite1, indicesExtremite2))
            {
                DOMINO passeTour;
                passeTour.valeur1 = -2;
                passeTour.valeur2 = -2;
                return passeTour;
            }
            else
                choix = -1;
        }
        else
            return mainActive[choix];
    } while (choix == -1);

    return mainActive[0];
}*/

// Cette fonction verifie si le joueur a encore la possibilité de jouer.
BOOL verifie_compatibilite_main(DOMINO mainActive[], COORDONNEES indiceExtremite1, COORDONNEES indiceExtremite2)
{
    int i;

    for (i = 0; i < NB_MAX_DOMINO_MAIN; i++)
    {
        if (verifie_compatibilite_domino(&mainActive[i], indiceExtremite1, indiceExtremite2, 0).compatible)
            return TRUE;
    }

    return FALSE;
}

// renvoie vrai si le domino choisi peut être joué
// indicesExtremite1: domino le plus en bas ou à gauche du plateau
AIDE_PLACEMENT verifie_compatibilite_domino(DOMINO *domino, COORDONNEES indicesExtremite1, COORDONNEES indicesExtremite2, int inverse)
{
    AIDE_PLACEMENT a_retourner;
    int copie;

    if (plateau[indicesExtremite1.ligne][indicesExtremite1.colonne].valeur1 == domino->valeur2)
    {
        a_retourner.compatible = VRAI;
        a_retourner.extremite = GAUCHE;
    }
    else if (plateau[indicesExtremite2.ligne][indicesExtremite2.colonne].valeur2 == domino->valeur1)
    {
        a_retourner.compatible = VRAI;
        a_retourner.extremite = DROITE;
    }
    else if (plateau[indicesExtremite1.ligne][indicesExtremite1.colonne].valeur1 == domino->valeur1)
    {
        if (inverse == 1)
        {
            printf("YOUHOU on inverse\n");
            copie = domino->valeur1;
            domino->valeur1 = domino->valeur2;
            domino->valeur2 = copie;
        }
        a_retourner.compatible = VRAI;
        a_retourner.extremite = GAUCHE;
    }

    else if (plateau[indicesExtremite2.ligne][indicesExtremite2.colonne].valeur2 == domino->valeur2)
    {
        if (inverse == 1)
        {
            printf("YOUHOU on inverse\n");
            copie = domino->valeur1;
            domino->valeur1 = domino->valeur2;
            domino->valeur2 = copie;
        }
        a_retourner.compatible = VRAI;
        a_retourner.extremite = DROITE;
    }

    else
    {
        a_retourner.compatible = FAUX;
        a_retourner.extremite = AUCUN_DOMINO;
    }
    return a_retourner;
}

int trouve_indice_domino_main(DOMINO mainActive[], DOMINO domino)
{
    int i;

    for (i = 0; i < NB_MAX_DOMINO_MAIN; i++)
    {
        if ((mainActive[i].valeur1 == domino.valeur1) && (mainActive[i].valeur2 == domino.valeur2))
            return i;
    }

    return -1;
}

BOOL place_domino(DOMINO *dominoAPlacer, COORDONNEES *indiceExtremite1, COORDONNEES *indiceExtremite2, int tourJeu, DOMINO mainActive[])
{
    int alea;
    EXTREMITE_COMPATIBLE extremiteCompatible;
    AIDE_PLACEMENT dominoCompatible;
    DOMINO pasDom;
    int dominoMain;
    POINT coin;
    EXTREMITE_COMPATIBLE direction;

    direction = AUCUN_DOMINO;
    coin.x = 0;
    coin.y = 0;
    pasDom.valeur1 = -1;
    pasDom.valeur2 = -1;
    alea = rand() % 2;

    dominoMain = trouve_indice_domino_main(mainActive, *dominoAPlacer);

    if (tourJeu == 1)
    {
        plateau[TAILLE_TAB_DOMINOS / 2][TAILLE_TAB_DOMINOS / 2] = *dominoAPlacer;
        direction = DROITE;
        *indiceExtremite1 = *indiceExtremite2;
        printf("indiceExtremite1 = %d et indiceExtremite2 = %d\n", indiceExtremite1->coin.x, indiceExtremite2->coin.x);
        coin = transforme_coord_point(&indiceExtremite2, direction, tourJeu);

        mainActive[dominoMain] = pasDom;

        printf("** C'est le premier tour, place n'importe quel domino **\n");
    }
    else
    {
        dominoCompatible = verifie_compatibilite_domino(dominoAPlacer, *indiceExtremite1, *indiceExtremite2, 1);
        extremiteCompatible = dominoCompatible.extremite;

        if (dominoCompatible.compatible == TRUE)
        {
            if (extremiteCompatible == GAUCHE)
            {

                if (indiceExtremite1->colonne >= 0) ///!\j'ai changé le != en >=
                {
                    if ((indiceExtremite1->coin.x >= 1125) || (indiceExtremite1->coin.x <= 65)) // si les coordonnées du domino choisi se trouvent à l'extérieur du plateau (trop à gauche ou à droite)
                    {
                        printf("\n\n\n ATTENTION ON SORT DU CADRE DONC CHANGEMENT ORIENTATION!!!!\n\n\n");
                        dominoAPlacer->orientation = VERTICALE;
                        indiceExtremite1->coin.x += 36;
                        if (plateau[indiceExtremite1->ligne][indiceExtremite1->colonne].valeur1 = dominoAPlacer->valeur2)
                        {
                            indiceExtremite1->ligne = indiceExtremite1->ligne - 1;
                            indiceExtremite1->coin.y -= 36;
                            direction = BAS;
                        }
                        else
                        {
                            indiceExtremite1->ligne = indiceExtremite1->ligne + 1;
                            indiceExtremite1->coin.y += 36;
                            direction = HAUT;
                        }
                    }
                    else
                    {
                        direction = GAUCHE;
                    }

                    plateau[indiceExtremite1->ligne][indiceExtremite1->colonne - 1] = *dominoAPlacer;
                    indiceExtremite1->colonne--;

                    coin = transforme_coord_point(&indiceExtremite1, direction, tourJeu);

                    mainActive[dominoMain] = pasDom;
                }
            }
            else if (extremiteCompatible == DROITE)
            {
                if (indiceExtremite2->colonne <= TAILLE_TAB_DOMINOS - 1) // j'ai modifié le =! en <
                {
                    if ((indiceExtremite2->coin.x >= 1125) || (indiceExtremite2->coin.x <= 65)) // pour haut /bas : if ((coin.y >= 750) || (coin.y <= 180))
                    {                                                                           // si les coordonnées du domino choisi se trouvent à l'extérieur du plateau (trop à gauche ou à droite)
                        printf("\n\n\n ATTENTION ON SORT DU CADRE DONC CHANGEMENT ORIENTATION!!!!\n\n\n");
                        dominoAPlacer->orientation = VERTICALE;

                        indiceExtremite2->coin.x -= 36;
                        if (alea == 0)
                        {
                            indiceExtremite1->ligne = indiceExtremite1->ligne + 1;
                            indiceExtremite2->coin.y += 36;
                        }
                        else
                        {
                            indiceExtremite1->ligne = indiceExtremite1->ligne - 1;
                            indiceExtremite2->coin.y -= 36;
                        }
                    }
                    plateau[indiceExtremite2->ligne][indiceExtremite2->colonne + 1] = *dominoAPlacer;
                    indiceExtremite2->colonne++;
                    direction = DROITE;
                    coin = transforme_coord_point(&indiceExtremite2, direction, tourJeu);

                    mainActive[dominoMain] = pasDom;
                }
            }
            else if (extremiteCompatible == LES_DEUX)
            {
                printf("** DOMINO choisi COMPATIBLE a DROITE et a GAUCHE **\n");
                if (alea == 0)
                {
                    plateau[indiceExtremite1->ligne][indiceExtremite1->colonne - 1] = *dominoAPlacer;
                    indiceExtremite1->colonne--;
                    direction = GAUCHE;
                    coin = transforme_coord_point(&indiceExtremite1, direction, tourJeu);
                }
                else
                {
                    plateau[indiceExtremite2->ligne][indiceExtremite2->colonne + 1] = *dominoAPlacer;
                    indiceExtremite2->colonne++;
                    direction = DROITE;
                    coin = transforme_coord_point(&indiceExtremite2, direction, tourJeu);
                }
                mainActive[dominoMain] = pasDom;
            }
        }
        else
        {
            printf("** DOMINO choisi PAS COMPATIBLE **\n");
            return FALSE;
        }
    }

    printf("coord du domino[%d,%d]\n", coin.x, coin.y);
    // si les coordonnées du domino choisi se trouvent à l'extérieur du plateau (trop bas ou trop haut)
    affiche_domino(*dominoAPlacer, coin, direction);
    actualise_affichage();

    return TRUE;
}

void calcule_score(int *score, DOMINO dominoPose)
{
    *score += dominoPose.valeur1 + dominoPose.valeur2;
}

BOOL est_vide_pioche()
{
    for (int i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        if (pioche_domino[i].valeur1 != -1)
            return FALSE;
    }
    return TRUE;
}

POINT transforme_coord_point(COORDONNEES **indiceExtremite, EXTREMITE_COMPATIBLE direction, int tourJeu)
{
    POINT coin;
    if (direction == DROITE)
    {
        if (tourJeu != 1)
        {
            if (est_double(plateau[(*indiceExtremite)->ligne][(*indiceExtremite)->colonne - 1]))
                (*indiceExtremite)->coin.x += 36;
            else
                (*indiceExtremite)->coin.x += 71;
        }

        coin.x = (*indiceExtremite)->coin.x;
        coin.y = (*indiceExtremite)->coin.y;
        printf("APRES INDICE EXTREMITE COIN  = [%d,%d]\n", (*indiceExtremite)->coin.x, (*indiceExtremite)->coin.y);
    }
    else if (direction == GAUCHE)
    {
        if (est_double(plateau[(*indiceExtremite)->ligne][(*indiceExtremite)->colonne + 1]))
        {
            (*indiceExtremite)->coin.x -= 71;
        }
        else if (est_double(plateau[(*indiceExtremite)->ligne][(*indiceExtremite)->colonne]))
        {
            (*indiceExtremite)->coin.x -= 36;
        }
        else if (!est_double(plateau[(*indiceExtremite)->ligne][(*indiceExtremite)->colonne + 1]))
        {
            (*indiceExtremite)->coin.x -= 71;
        }
        else
            (*indiceExtremite)->coin.x -= 71;

        coin.x = (*indiceExtremite)->coin.x;
        coin.y = (*indiceExtremite)->coin.y;
        printf("APRES INDICE EXTREMITE COIN  = [%d,%d]\n", (*indiceExtremite)->coin.x, (*indiceExtremite)->coin.y);
    }
    else if (direction == HAUT)
    {
        (*indiceExtremite)->coin.y += 71;
        coin.x = (*indiceExtremite)->coin.x;
        coin.y = (*indiceExtremite)->coin.y;
        printf("APRES INDICE EXTREMITE COIN  = [%d,%d]\n", (*indiceExtremite)->coin.x, (*indiceExtremite)->coin.y);
    }
    else
    {
        (*indiceExtremite)->coin.y -= 71;
        coin.x = (*indiceExtremite)->coin.x;
        coin.y = (*indiceExtremite)->coin.y;
        printf("APRES INDICE EXTREMITE COIN  = [%d,%d]\n", (*indiceExtremite)->coin.x, (*indiceExtremite)->coin.y);
    }

    return coin;
}

BOOL joue_IA(JOUEUR *infos_joueur, COORDONNEES *indiceExtremite1, COORDONNEES *indiceExtremite2, int tourJeu, VARIANTE variante)
{
    BOOL dominoPlace;
    DOMINO temp;
    int i;
    DOMINO *mainActive = infos_joueur->mainJoueur;

    do
    {
        for (i = 0; i < NB_MAX_DOMINO_MAIN; i++) // on parcours la main de l'ia et des lors que l'on trouve un domino compatible on le place
        {
            temp = mainActive[i];
            if (temp.valeur1 != -1)
            {
                DOMINO *dominoChoisi = &temp;
                printf("**** Le domino |%d %d| a ete choisi ****\n", dominoChoisi->valeur1, dominoChoisi->valeur2);
                dominoPlace = place_domino(dominoChoisi, indiceExtremite1, indiceExtremite2, tourJeu, mainActive);
                printf("\n-----------------------------\n");
                if (dominoPlace == TRUE)
                {
                    calcule_score(&infos_joueur->score, *dominoChoisi);
                    return TRUE;
                }
            }
        }
        if (i >= NB_MAX_DOMINO_MAIN) // Si pas de domino compatible on passe le tour
        {
            if (variante == SANS_PIOCHE)
            {
                printf("**** %s passe son tour ****\n", infos_joueur->pseudo);
                printf("\n-----------------------------\n");
                return TRUE;
            }
            else if (variante == AVEC_PIOCHE)
            {
                do
                {
                    if (!est_vide_pioche())
                    {
                        DOMINO temp = pioche_un_domino(infos_joueur);
                        DOMINO *dominoChoisi = &temp;
                        dominoPlace = place_domino(dominoChoisi, indiceExtremite1, indiceExtremite2, tourJeu, mainActive);
                        printf("**** Le joueur %s pioche le domino |%d %d| ****\n", infos_joueur->pseudo, dominoChoisi->valeur1, dominoChoisi->valeur2);
                        printf("\n-----------------------------\n");
                        if (dominoPlace == TRUE)
                        {
                            calcule_score(&infos_joueur->score, *dominoChoisi);
                            return TRUE;
                        }
                    }
                    else
                    {
                        printf("**** PIOCHE EST VIDE ****\n");
                        printf("\n-----------------------------\n");
                        return TRUE;
                    }

                } while (dominoPlace == FALSE);
            }
        }

    } while (dominoPlace == FALSE);

    return FALSE;
}

CHOIX_JOUEUR joue_joueur(JOUEUR *infos_joueur, COORDONNEES *indiceExtremite1, COORDONNEES *indiceExtremite2, int tourJeu, VARIANTE variante, int tour)
{
    DOMINO *mainActive = infos_joueur->mainJoueur;
    DOMINO temp = recupere_choix_domino_main(mainActive, *indiceExtremite1, *indiceExtremite2);
    DOMINO *dominoChoisi = &temp;
    BOOL domino_est_compatible;

    if (dominoChoisi->valeur1 == -1)
    {
        do
        {
            temp = recupere_choix_domino_main(mainActive, *indiceExtremite1, *indiceExtremite2);
            dominoChoisi = &temp;
            printf("\nclic dans le vide\n");
        } while (dominoChoisi->valeur1 == -1);
    }

    if (dominoChoisi->valeur1 == -2) // si le joueur a appuyé sur le bouton piocher/passer son tour
    {
        if (variante == SANS_PIOCHE)
        {
            printf("**** %s passe son tour ****\n", infos_joueur->pseudo);
            printf("\n-----------------------------\n");
            return TOUR_FINI;
        }
        else if (variante == AVEC_PIOCHE)
        {
            if (!est_vide_pioche())
            {
                pioche_un_domino(infos_joueur);
                affiche_interface(variante);
                affiche_main(infos_joueur, tour);
                actualise_affichage();
                *dominoChoisi = recupere_choix_domino_main(mainActive, *indiceExtremite1, *indiceExtremite2);
                printf("**** Le joueur %s pioche le domino |%d %d| ****\n", infos_joueur->pseudo, dominoChoisi->valeur1, dominoChoisi->valeur2);
                printf("\n-----------------------------\n");
                calcule_score(&infos_joueur->score, *dominoChoisi);
                return TOUR_FINI;
            }

            else
            {
                printf("**** PIOCHE EST VIDE ****\n");
                printf("\n-----------------------------\n");
                return TOUR_FINI;
            }
        }
    }
    if (dominoChoisi->valeur1 == -3) // si le joueur a appuyé sur le bouton QUITTER
    {
        printf("le joueur veut quitter");
        return QUITTER;
    }

    printf("**** Le domino |%d %d| a ete choisi ****\n", dominoChoisi->valeur1, dominoChoisi->valeur2);
    domino_est_compatible = place_domino(dominoChoisi, indiceExtremite1, indiceExtremite2, tourJeu, mainActive);
    if (domino_est_compatible)
    {
        calcule_score(&infos_joueur->score, *dominoChoisi);
        printf("\n-----------------------------\n");
        return TOUR_FINI;
    }

    printf("\nOn a choisi un domino non compatible donc tour non fini\n");
    return TOUR_NON_FINI;
}

int compte_dominos_pioche() // compte le nombre de dominos dans la pioche
{
    int nb_dominos;
    int i;

    nb_dominos = 0;

    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        if (pioche_domino[i].valeur1 != -1)
        {
            nb_dominos++;
        }
    }
    return nb_dominos;
}

/*
 Cette fonction verifie s'il y a un gagnant:
 Renvoie le numero du joueur gagnant s'il y en a un,
 Renvoie -2 s'il y a une egalité,
 Renvoie -1 si personne n'a gagné,
*/
int verifie_gagnant(JOUEUR infos_joueurs[], COORDONNEES indiceExtremite1, COORDONNEES indiceExtremite2, int totJoueurs, VARIANTE variante)
{
    BOOL compatible;
    BOOL peutEncoreJouer;
    int i;
    int j;
    int nbDominosMain;
    int minMain;
    int gagnant;

    gagnant = 9;
    minMain = 999;
    compatible = FALSE;
    peutEncoreJouer = FALSE;

    // on parcourt une fois toute les mains des joueurs
    for (i = 0; i < totJoueurs; i++)
    {
        nbDominosMain = 0;
        for (j = 0; j < NB_MAX_DOMINO_MAIN; j++)
        {
            if (infos_joueurs[i].mainJoueur[j].valeur1 != -1)
            {
                compatible = verifie_compatibilite_domino(&infos_joueurs[i].mainJoueur[j], indiceExtremite1, indiceExtremite2, 0).compatible;
                if (compatible) // si au moin un domino est compatible, on peut toujours jouer
                    peutEncoreJouer = TRUE;

                nbDominosMain++; // on compte le nombre de domino dans la main
            }
        }

        if (nbDominosMain == 0) // s'il le joueur n'a plus de domino alors il a gagné
            return i;
        else if ((minMain == nbDominosMain) && (variante == SANS_PIOCHE)) // sinon on regarde s'il y a une egalité
        {
            gagnant = -2;
        }
        else if ((minMain == nbDominosMain) && (variante == AVEC_PIOCHE))
        {
            if (!est_vide_pioche())
            {
                peutEncoreJouer = TRUE;
            }
            else
            {
                peutEncoreJouer = FALSE;
            }
        }

        else // ou qui en a le moins
        {
            if (nbDominosMain < minMain)
            {
                gagnant = i;
                minMain = nbDominosMain;
            }
        }
    }

    if (!peutEncoreJouer)
        return gagnant;
    else
        return -1;
}

int gere_clics(DOMINO main[])
{

    BOOL clic_sur_bouton = 0;
    int position_domino = 0;
    int i, j = 0;
    do
    {
        POINT coordonees_clic = attend_clic();
        printf(" gere_clic attend un clic ");
        for (i = 0; i <= 21 * 50; i += 50)
        {

            if ((100 + i <= coordonees_clic.x) && (coordonees_clic.x <= 135 + i) && (25 <= coordonees_clic.y) && (coordonees_clic.y <= 95))
            {

                if (main[j].valeur1 != -1)
                {
                    position_domino = j;
                    clic_sur_bouton = 1;
                }
            }
            if (j < NB_MAX_DOMINO_MAIN)
            {
                j++;
            }
            else
            {
                j = 0;
            }
        }
        if ((1130 <= coordonees_clic.x) && (coordonees_clic.x <= 1285) && (10 <= coordonees_clic.y) && (coordonees_clic.y <= 115)) // si on clique sur le bouton piocher ou passer son tour
        {
            position_domino = -2;
            clic_sur_bouton = 1;
        }
        else if ((1175 <= coordonees_clic.x) && (coordonees_clic.x <= 1255) && (840 <= coordonees_clic.y) && (coordonees_clic.y <= 885)) // si on clique sur quitter
        {
            position_domino = -3;
            clic_sur_bouton = 1;
        }

    } while (clic_sur_bouton == 0);

    return position_domino;
}
