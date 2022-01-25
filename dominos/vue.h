#ifndef VUE_H
#define VUE_H

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

#define LARGEUR 1300
#define HAUTEUR 900
#define LARGEUR_PLATEAU 1260
#define HAUTEUR_PLATEAU 700
#define LARGEUR_MAIN 1100
#define HAUTEUR_MAIN 100
#define LARGEUR_PIOCHE 150
#define BORDURE 20
#define ORDONNEE_BOUTON_QUITTER 840
#define ABSCISSE_BOUTON_QUITTER 1175

// Prototypes Vue
void affiche_domino(DOMINO domino_a_afficher, POINT coin);
void affiche_plateau();
void affiche_domino_main(DOMINO domino_a_afficher, POINT coin);
void affiche_mains(int totJoueur, JOUEUR infos_joueurs[]);
void affiche_pioche();
void affiche_pseudos(JOUEUR infos_joueurs[], int totJoueur);
void affiche_interface();
void affiche_victoire(int gagnant, JOUEUR infos_joueurs[]);
void affiche_main(DOMINO main_a_afficher[]);
void affiche_tour(char pseudo[]);
#endif