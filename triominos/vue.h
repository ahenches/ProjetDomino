#ifndef VUE_H_TRIOMINOS
#define VUE_H_TRIOMINOS

#define LARGEUR 1300
#define HAUTEUR 900
#define LARGEUR_PLATEAU_T 1260
#define HAUTEUR_PLATEAU_T 700
#define LARGEUR_MAIN_T 1050
#define HAUTEUR_MAIN_T 100
#define LARGEUR_PIOCHE_T 200
#define LARGEUR_TUILE_T 60
#define HAUTEUR_TUILE_T 50
#define BORDURE_T 20

void affiche_plateau_triminos();
void affiche_triomino(CASE caseP, EMPLACEMENT emp);
void affiche_emplacement_possible_triominos(CASE caseP);
void actualise_plateau_triominos(EMPLACEMENT **plateau);
void actualise_pioche_triominos(int nbPioche);
void efface_main_triominos();
void affiche_main_triominos(JOUEUR_TRIOMINOS joueur, int partieMain);
void affiche_joueurs_triominos(int nbJoueurs, JOUEUR_TRIOMINOS joueurs[]);
void actualise_score_triominos(int nbJoueurs, JOUEUR_TRIOMINOS joueurs[]);
void affiche_joueur_main_triominos(JOUEUR_TRIOMINOS joueur);
void affiche_selection_main_triominos(int trioSelect, int partieMain, int tailleMain);
void efface_selection_main_triominos(int tailleMain, int partieMain);
void affiche_selection_emplacement_triominos(CASE caseS);

#endif
