#ifndef VUE_H
#define VUE_H

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

// Prototypes Vue
void affiche_domino();
void affiche_plateau();
void affiche_mains(int totJoueur, JOUEUR mains_joueurs[]);
void affiche_pioche();
void affiche_pseudos(JOUEUR mains_joueurs[], int totJoueur);

#endif