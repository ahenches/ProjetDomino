#ifndef MODELE_H
#define MODELE_H

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

// Prototypes Modèle
void initialise_plateau();
NB_JOUEURS entre_nb_joueurs(NB_JOUEURS joueurs);
void entre_pseudos(JOUEUR mains_joueurs[], NB_JOUEURS joueurs);
void genere_pioche();
int determine_nb_dominos_main(int totJoueur);
void distribue_premiers_dominos(JOUEUR mains_joueurs[], int totJoueur);
DOMINO pioche_un_domino();
int compte_double_pioche();
int est_double(DOMINO domino);
void definit_premier_joueur(JOUEUR mains_joueurs[], int nbDominosMain);
int determine_joueur_suivant(int tour, int totJoueur, JOUEUR mains_joueurs[]);
DOMINO recupere_choix_domino_main(DOMINO mainActive[]);
BOOL verifie_compatibilite_domino(DOMINO domino, COORDONNEES indices_extremite1, COORDONNEES indices_extremite2);

#endif