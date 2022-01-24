#ifndef VUE_H
#define VUE_H

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

#define LARGEUR 1300
#define HAUTEUR 900
#define LARGEUR_PLATEAU 1260
#define HAUTEUR_PLATEAU 700
#define LARGEUR_MAIN 1050
#define HAUTEUR_MAIN 100
#define LARGEUR_PIOCHE 200
#define LARGEUR_TUILE 60
#define HAUTEUR_TUILE 50
#define BORDURE 20

// Prototypes Vue
void affiche_domino();
void affiche_plateau();
void affiche_mains(int totJoueur, JOUEUR infos_joueurs[]);
void affiche_pioche();
void affiche_pseudos(JOUEUR infos_joueurs[], int totJoueur);

#endif