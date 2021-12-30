// Maud et Michel
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


void affiche_plateau_triminos();
void affiche_triomino(CASE caseP, EMPLACEMENT emp);
void affiche_emplacement_possible_triominos(CASE caseP);
void actualise_pioche_triominos(int nbPioche);
void efface_main_triominos();
void affiche_main_triominos(MAIN_TRIOMINOS mainJoueur);
//void affiche_joueurs_triominos(char TabPseudo[][]);
//void actualise_score_triominos(int tabScore[]);
//void affiche_joueur_main_triominos(int nbJoueurs, char pseudoJoueur[]);
void affiche_selection_main_triominos(int trioSelect);
void efface_selection_main_triominos(int trioDeselect);
void affiche_selection_emplacement_triominos(CASE caseS);
