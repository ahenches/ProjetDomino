#ifndef MODELE_H
#define MODELE_H

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

// Prototypes Modèle
void initialise_plateau();
void initialise_mains_joueurs(JOUEUR infos_joueurs[], int totJoueurs);
NB_JOUEURS entre_nb_joueurs(NB_JOUEURS joueurs);
void entre_pseudos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs);
void genere_pioche();
int determine_nb_dominos_main(int totJoueur);
void distribue_premiers_dominos(JOUEUR infos_joueurs[], int totJoueur);
void pioche_un_domino(JOUEUR infos_joueurs[], int numero_joueur_actif);
int compte_double_pioche();
int est_double(DOMINO domino);
void definit_premier_joueur(JOUEUR infos_joueurs[], int nbDominosMain);
int determine_joueur_suivant(int tour, int totJoueur, JOUEUR infos_joueurs[]);
DOMINO recupere_choix_domino_main(DOMINO mainActive[]);
BOOL place_domino(DOMINO dominoAPlacer, COORDONNEES *indiceExtremite1, COORDONNEES *indiceExtremite2, int tourJeu, JOUEUR tabJoueurs[]);
AIDE_PLACEMENT verifie_compatibilite_domino(DOMINO domino, COORDONNEES indices_extremite1, COORDONNEES indices_extremite2);

#endif