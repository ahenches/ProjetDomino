#include "dominos.h"
#include "modele.h"
#include "vue.h"

//////////////////////////////////////////////////////////////////////////////////////////
//                                  Fonctions du modele                                 //
//////////////////////////////////////////////////////////////////////////////////////////

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

DOMINO pioche_un_domino(JOUEUR *infos_joueur)
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
        domChoisi = pioche[alea];
    } while (domChoisi.valeur1 == -1 && domChoisi.valeur2 == -1);

    if (domChoisi.valeur1 != -1 && domChoisi.valeur2 != -1)
        pioche[alea] = pasDom;

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
        if (est_double(pioche[i]) && pioche[i].valeur1 != -1)
            compt++;
    }
    return compt;
}

// indique si le domino pris en paramètre est un double ou non
BOOL est_double(DOMINO domino)
{
    if (domino.valeur1 == domino.valeur2)
        return VRAI;

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
    int choix;

    do
    {

        choix = gere_clics();

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
            {
                choix = -1;
            }
        }
        else if (choix == -3)
        {
            DOMINO quitter;
            quitter.valeur1 = -3;
            quitter.valeur2 = -3;
            return quitter;
        }
        else
        {
            return mainActive[choix];
        }
    } while (choix == gere_clics());

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
    }while(choix == -1);

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
        a_retourner.extremite = AUCUN;
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

    coin.x = 0;
    coin.y = 0;
    pasDom.valeur1 = -1;
    pasDom.valeur2 = -1;
    alea = rand() % 2;

    dominoMain = trouve_indice_domino_main(mainActive, *dominoAPlacer);

    if (tourJeu == 1)
    {
        plateau[TAILLE_TAB_DOMINOS / 2][TAILLE_TAB_DOMINOS / 2] = *dominoAPlacer;
        mainActive[dominoMain] = pasDom;
        coin = transforme_coord_point(*indiceExtremite2, DROITE);
        printf("coord du domino[%d,%d]\n", coin.x, coin.y);
        affiche_domino(*dominoAPlacer, coin, DROITE);
        actualise_affichage();
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
                if (indiceExtremite1->colonne != 0)
                {
                    plateau[indiceExtremite1->ligne][indiceExtremite1->colonne - 1] = *dominoAPlacer;
                    indiceExtremite1->colonne--;
                    mainActive[dominoMain] = pasDom;
                    coin = transforme_coord_point(*indiceExtremite1, GAUCHE);
                    printf("coord du domino[%d,%d]\n", coin.x, coin.y);
                    printf("** DOMINO choisi COMPATIBLE a GAUCHE **\n");
                    affiche_domino(*dominoAPlacer, coin, GAUCHE);
                }
            }
            else if (extremiteCompatible == DROITE)
            {
                if (indiceExtremite2->colonne != TAILLE_TAB_DOMINOS - 1)
                {
                    plateau[indiceExtremite2->ligne][indiceExtremite2->colonne + 1] = *dominoAPlacer;
                    indiceExtremite2->colonne++;
                    mainActive[dominoMain] = pasDom;
                    coin = transforme_coord_point(*indiceExtremite2, DROITE);
                    printf("coord du domino[%d,%d]\n", coin.x, coin.y);
                    printf("** DOMINO choisi COMPATIBLE a DROITE **\n");
                    affiche_domino(*dominoAPlacer, coin, DROITE);
                }
            }
            else if (extremiteCompatible == LES_DEUX)
            {
                printf("** DOMINO choisi COMPATIBLE a DROITE et a GAUCHE **\n");
                if (alea == 0)
                {
                    plateau[indiceExtremite1->ligne][indiceExtremite1->colonne - 1] = *dominoAPlacer;
                    indiceExtremite1->colonne--;
                    coin = transforme_coord_point(*indiceExtremite1, GAUCHE);
                    printf("coord du domino[%d,%d]\n", coin.x, coin.y);
                    affiche_domino(*dominoAPlacer, coin, GAUCHE);
                }
                else
                {
                    plateau[indiceExtremite2->ligne][indiceExtremite2->colonne + 1] = *dominoAPlacer;
                    indiceExtremite2->colonne++;
                    coin = transforme_coord_point(*indiceExtremite2, DROITE);
                    printf("coord du domino[%d,%d]\n", coin.x, coin.y);
                    affiche_domino(*dominoAPlacer, coin, DROITE);
                }
                mainActive[dominoMain] = pasDom;
            }

           
            actualise_affichage();
        }
        else
        {
            printf("** DOMINO choisi PAS COMPATIBLE **\n");
            return FALSE;
        }
    }

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
        if (pioche[i].valeur1 != -1)
            return FALSE;
    }
    return TRUE;
}

POINT transforme_coord_point(COORDONNEES indiceExtremite, EXTREMITE_COMPATIBLE direction)
{
    POINT coin;
    int i;
    int x;
    int y;

    x = 0;
    y = 0;
    if (direction == DROITE)
    {
        for (i = TAILLE_TAB_DOMINOS / 2; i < indiceExtremite.colonne; i++)
        {
            x += 71;
        }
        
    }
    if (direction == GAUCHE)
    {
        for (i = indiceExtremite.colonne; i < TAILLE_TAB_DOMINOS / 2; i++)
        {
            x -= 71;
        }
        
    }

    coin.x = (LARGEUR_PLATEAU / 2) + x;
    coin.y = 700 / 2 + y;

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

int joue_joueur(JOUEUR *infos_joueur, COORDONNEES *indiceExtremite1, COORDONNEES *indiceExtremite2, int tourJeu, VARIANTE variante)
{
    BOOL dominoPlace;
    DOMINO *mainActive = infos_joueur->mainJoueur;
    DOMINO temp = recupere_choix_domino_main(mainActive, *indiceExtremite1, *indiceExtremite2);
    DOMINO *dominoChoisi = &temp;

    if (dominoChoisi->valeur1 == -3)
    {
        return QUITTER;
    }
    else if (dominoChoisi->valeur1 == -2)
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
    else
    {
        printf("**** Le domino |%d %d| a ete choisi ****\n", dominoChoisi->valeur1, dominoChoisi->valeur2);
        dominoPlace = place_domino(dominoChoisi, indiceExtremite1, indiceExtremite2, tourJeu, mainActive);
        if (dominoPlace)
            calcule_score(&infos_joueur->score, *dominoChoisi);
        printf("\n-----------------------------\n");
    }

    return dominoPlace;
}

int compte_dominos_pioche() // compte le nombre de dominos dans la pioche
{
    int nb_dominos;
    int i;

    nb_dominos = 0;

    for (i = 0; i < TAILLE_TAB_DOMINOS; i++)
    {
        if (pioche[i].valeur1 != -1)
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
int verifie_gagnant(JOUEUR infos_joueurs[], COORDONNEES indiceExtremite1, COORDONNEES indiceExtremite2, int totJoueurs)
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
        else if (minMain == nbDominosMain) // sinon on regarde s'il y a une egalité
        {
            gagnant = -2;
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

int gere_clics()
{

    BOOL clic_sur_bouton = 0;
    int position_domino = 0;
    int i, j = 0;
    do
    {
        POINT coordonees_clic = attend_clic();
        for (i = 0; i <= 21 * 50; i += 50)
        {

            if ((100 + i <= coordonees_clic.x) && (coordonees_clic.x <= 135 + i) && (25 <= coordonees_clic.y) && (coordonees_clic.y <= 95))
            {
                position_domino = j;
                clic_sur_bouton = 1;
            }
            j++;
        }
        if ((1130 <= coordonees_clic.x) && (coordonees_clic.x <= 1280) && (10 <= coordonees_clic.y) && (coordonees_clic.y <= 115)) // si on clique sur le bouton piocher ou passer son tour
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
