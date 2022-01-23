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

void entre_pseudos(JOUEUR tabJoueurs[], NB_JOUEURS joueurs)
{
    int i;
    int compt;
    int totJoueurs;

    totJoueurs = joueurs.nbJoueurHumain + joueurs.nbJoueurIA;
    compt = 1;

    for (i = 0; i < joueurs.nbJoueurHumain; i++)
    {
        printf("Choisissez votre pseudo :\n");
        // tabJoueurs[i].pseudo = (char *)malloc(25);
        scanf("%s", tabJoueurs[i].pseudo);
    }

    for (i = joueurs.nbJoueurHumain; i < totJoueurs; i++)
    {
        // tabPseudos[i] = (char *)malloc(25);
        sprintf(tabJoueurs[i].pseudo, "IA%d", compt);
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
void distribue_premiers_dominos(JOUEUR tabJoueurs[], int totJoueur)
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
            tabJoueurs[i].mainJoueur[j] = domChoisi;
        }
    }
}

// choisit aléatoirement un domino dans la pioche[] et le supprime de la pioche
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
        return TRUE;

    return FALSE;
}

/* définit le joueur qui commence, et place les mains des joueurs dans l'ordre dans tabPseudos.
  Celui qui a le plus grand double commence, sinon celui qui a le domino le plus fort : 6 5, 6 4, 6 3 ... commence*/
void definit_premier_joueur(JOUEUR tabJoueurs[], int nbDominosMain)
{
    int i;
    int j;
    int grandDouble;
    int tempDouble;
    int joueurChoisi;
    int nbrDoublePioche;
    DOMINO grandDomino;
    char *pseudoTemp;
    DOMINO *mainTemp;

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
                if (est_double(tabJoueurs[i].mainJoueur[j]))
                {
                    tempDouble = tabJoueurs[i].mainJoueur[j].valeur1;

                    if (tempDouble > grandDouble)
                    {
                        grandDouble = tempDouble;
                        joueurChoisi = i;
                    }
                }
            }
        }
        printf("Le joueur qui a le plus grand double est %s, il a |%d %d|\n", tabJoueurs[joueurChoisi].pseudo, grandDouble, grandDouble);
    }
    else
    {
        for (i = 0; i < TOT_JOUEURS; i++)
        {
            for (j = 0; j < nbDominosMain; j++)
            {
                if (tabJoueurs[i].mainJoueur[j].valeur1 >= grandDomino.valeur1 && tabJoueurs[i].mainJoueur[j].valeur2 >= grandDomino.valeur2)
                {
                    grandDomino.valeur1 = tabJoueurs[i].mainJoueur[j].valeur1;
                    grandDomino.valeur2 = tabJoueurs[i].mainJoueur[j].valeur2;
                    joueurChoisi = i;
                }
            }
        }
        printf("Le joueur qui a le domino le plus fort est %s, il a |%d %d|\n", tabJoueurs[joueurChoisi].pseudo, grandDomino.valeur1, grandDomino.valeur2);
    }

    // change l'ordre des pseudos dans le tableau des pseudos et l'ordre des mains dans le tableau des mains.
    if (joueurChoisi != 0)
    {
        pseudoTemp = tabJoueurs[0].pseudo;
        strcpy(tabJoueurs[0].pseudo, tabJoueurs[joueurChoisi].pseudo);
        strcpy(tabJoueurs[joueurChoisi].pseudo, pseudoTemp);

        mainTemp = tabJoueurs[0].mainJoueur;
        for (int i = 0; i < NB_MAX_DOMINO_MAIN; i++)
        {
            tabJoueurs[0].mainJoueur[i] = tabJoueurs[joueurChoisi].mainJoueur[i];
            tabJoueurs[joueurChoisi].mainJoueur[i] = mainTemp[i];
        }
    }
}

// determine qui doit jouer.
int determine_joueur_suivant(int tour, int totJoueur, JOUEUR tabJoueurs[])
{
    tour++;
    if (tour >= totJoueur)
        tour = 0;

    printf("**** [%d] C'est au tour de %s de jouer ! ****\n", tour, tabJoueurs[tour].pseudo);
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

/*void place_domino(Domino dominoAPlacer)
{
    if ()
    {

    }
}*/