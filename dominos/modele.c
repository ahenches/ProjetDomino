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

void initialise_mains_joueurs(JOUEUR infos_joueurs[], int totJoueurs)
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
            pioche_un_domino(infos_joueurs, i);
        }
    }
}


void pioche_un_domino(JOUEUR infos_joueurs[], int numero_joueur_actif)
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

        if (infos_joueurs[numero_joueur_actif].mainJoueur[i].valeur1 == -1) // si on parcourt une case dans laquelle il n'y a pas de domino
        {
            infos_joueurs[numero_joueur_actif].mainJoueur[i] = domChoisi; // on stocke le domino dans la case
            i = NB_MAX_DOMINO_MAIN + 1;                                   // on arrête la boucle
        }
    }

 }
// choisit aléatoirement un domino dans la pioche[] et le supprime de la pioche
/*
void distribue_premiers_dominos(JOUEUR infos_joueurs[], int totJoueur)
{
    int i;
    int j;
    DOMINO domChoisi;
    int nbDominosMain;

    nbDominosMain = determine_nb_dominos_main(totJoueur);

    for (i = 0; i < totJoueur; i++)
    {
        for (j = 0; j < nbDominosMain; j++)
        {
            domChoisi = pioche_un_domino();
            infos_joueurs[i].mainJoueur[j] = domChoisi;
        }
    }
}

DOMINO pioche_un_domino()
{
    int alea;
    DOMINO domChoisi;
    DOMINO pasDom;

    pasDom.valeur1 = -1;
    pasDom.valeur2 = -1;
    pasDom.orientation = HORIZONTALE;

    do
    {
        alea = rand() % TAILLE_TAB_DOMINOS;
        domChoisi = pioche[alea];
    } while (domChoisi.valeur1 == -1 && domChoisi.valeur2 == -1);

    if (domChoisi.valeur1 != -1 && domChoisi.valeur2 != -1)
        pioche[alea] = pasDom;

    return domChoisi;
}*/


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
DOMINO recupere_choix_domino_main(DOMINO mainActive[])
{
    int choix;

    printf("Choisissez le domino (0, 1, 2, 3, 4, 5, 6) :\n");
    scanf("%d", &choix);
    return mainActive[choix];
}

// renvoie vrai si le domino choisi peut être joué
// indicesExtremite1: domino le plus en bas ou à gauche du plateau
AIDE_PLACEMENT verifie_compatibilite_domino(DOMINO* domino, COORDONNEES indicesExtremite1, COORDONNEES indicesExtremite2) 
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
        
        copie = domino->valeur1;
        domino->valeur1 = domino->valeur2;
        domino->valeur2 = copie;
        a_retourner.compatible = VRAI;
        a_retourner.extremite = GAUCHE;
    }

    else if (plateau[indicesExtremite2.ligne][indicesExtremite2.colonne].valeur2 == domino->valeur2)
    {
        copie = domino->valeur1;
        domino->valeur1 = domino->valeur2;
        domino->valeur2 = copie;
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
    DOMINO pasDom;
    int dominoMain;

    pasDom.valeur1 = -1;
    pasDom.valeur2 = -1;
    alea = rand() % 2;

    dominoMain = trouve_indice_domino_main(mainActive, *dominoAPlacer);  

    if (tourJeu == 1)
    {
        plateau[TAILLE_TAB_DOMINOS/2][TAILLE_TAB_DOMINOS/2] = *dominoAPlacer;
        mainActive[dominoMain] = pasDom;
        printf("** C'est le premier tour, place n'importe quel domino **\n");
    }
    else
    {
        extremiteCompatible = verifie_compatibilite_domino(dominoAPlacer, *indiceExtremite1, *indiceExtremite2).extremite;
        
        if(extremiteCompatible == GAUCHE)
        {
            if (indiceExtremite1->colonne != 0)
            {
                plateau[indiceExtremite1->ligne][indiceExtremite1->colonne-1] = *dominoAPlacer;
                indiceExtremite1->colonne--;
                mainActive[dominoMain] = pasDom;
                printf("** DOMINO choisi COMPATIBLE a GAUCHE **\n");
            }
        }
        else if(extremiteCompatible == DROITE)
        {
            if (indiceExtremite2->colonne != TAILLE_TAB_DOMINOS-1)
            {
                plateau[indiceExtremite2->ligne][indiceExtremite2->colonne+1] = *dominoAPlacer;
                indiceExtremite2->colonne++;
                mainActive[dominoMain] = pasDom;
                printf("** DOMINO choisi COMPATIBLE a DROITE **\n");
            }
            
        }
        else if (extremiteCompatible == LES_DEUX)
        {
            printf("** DOMINO choisi COMPATIBLE a DROITE et a GAUCHE **\n");
            if (alea == 0)
            {
                plateau[indiceExtremite1->ligne][indiceExtremite1->colonne-1] = *dominoAPlacer;
                indiceExtremite1->colonne--;
            }
            else
            {
                plateau[indiceExtremite2->ligne][indiceExtremite2->colonne+1] = *dominoAPlacer;
                indiceExtremite2->colonne++;
            }
            mainActive[dominoMain] = pasDom;
        }
        else
        {
            printf("** DOMINO choisi PAS COMPATIBLE **\n");
            return FALSE;
        }
        
    }

    return TRUE;
}

BOOL passe_tour()
{
    int choix;
    printf("** Tu veux passer ton tour ? 1 = OUI,0 = NON **\n");
    scanf("%d", &choix);

    if (choix == 0)
        return FALSE;
    else if (choix == 1)
        return TRUE;

    return FALSE;
}


/////////////////////////////////////////////////////////////////////
///                           FONCTION IA                          ///
/////////////////////////////////////////////////////////////////////
/*DOMINO recupere_choix_IA(DOMINO mainActive[], COORDONNEES indicesExtremite1, COORDONNEES indicesExtremite2)
{
    for (int i = 0; i < NB_MAX_DOMINO_MAIN; i++)
    {
        if (verifie_compatibilite_domino(mainActive[i], indicesExtremite1, indicesExtremite2).compatible)
        {
            
        } 
    }
    
}

*/