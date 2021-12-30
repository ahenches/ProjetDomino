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
void efface_main_triominos();
void actualise_pioche_triominos(int nbPioche);
void affiche_main_triominos(TRIOMINO mainJoueur []);

