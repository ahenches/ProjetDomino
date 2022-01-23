#ifndef MODELE_H
#define MODELE_H

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

// Prototypes Modèle
void initialise_plateau();
NB_JOUEURS entre_nb_joueurs(NB_JOUEURS joueurs);
void entre_pseudos(JOUEUR tabJoueurs[], NB_JOUEURS joueurs);
void genere_pioche();
int determine_nb_dominos_main(int totJoueur);
void distribue_premiers_dominos(JOUEUR tabJoueurs[], int totJoueur);
DOMINO prend_domino_pour_distribue();
int compte_double_pioche();
int est_double(DOMINO domino);
void definit_premier_joueur(JOUEUR tabJoueurs[], int nbDominosMain);
int determine_joueur_suivant(int tour, int totJoueur, JOUEUR tabJoueurs[]);
DOMINO recupere_choix_domino_main(DOMINO mainActive[]);


#endif