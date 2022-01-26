#define TAILLE_PIOCHE_INITIALE 56
#define HAUTEUR_PLATEAU_MAX 14
#define LARGEUR_PLATEAU_MAX 48
#define MAX_TAILLE_PSEUDO 48
#define DEBUT_MAIN 0
#define FIN_MAIN 1

typedef struct triomino
{
    int min ;
    int sec ;
    int der ;

} TRIOMINO;

typedef struct emplacement
{
    TRIOMINO trio;
    char pointe ; // valeur possible : m, s, d
    char direction ; // direction de la pointe
    // valeur possible : n, s (nord, sud)
} EMPLACEMENT;

typedef struct main_j_triominos
{
    TRIOMINO tab[25];
    int taille;
} MAIN_J_TRIOMINOS;

typedef struct pioche_triominos
{
    TRIOMINO tab[TAILLE_PIOCHE_INITIALE];
    int taille;
} PIOCHE_TRIOMINOS;

typedef struct {
    int l ;
    int c ;
} CASE ;

typedef struct joueur_triominos
{
    char pseudo[MAX_TAILLE_PSEUDO];
    MAIN_J_TRIOMINOS mainJoueur;
    int score;
    BOOL estHumain;
} JOUEUR_TRIOMINOS;

typedef struct coup
{
  int indice_trio_dans_main;
  int indice_ligne;
  int indice_colonne;
} COUP; // utiliser dans la fonction jeu_ordinateur

int main_triominos();
BOOL clic_dans_main_triominos(POINT clic);
BOOL clic_sur_fleche_triominos(POINT clic);
BOOL clic_dans_pioche_triominos(POINT clic);
BOOL clic_dans_plateau_triominos(POINT clic);
CASE transforme_point_en_case_triominos(POINT clic);
TRIOMINO transforme_selection_en_triominos(POINT clic, MAIN_J_TRIOMINOS mainJoueurCourant, int partieMain);
int change_partie_main_triominos(JOUEUR_TRIOMINOS joueur, int partieMain);
