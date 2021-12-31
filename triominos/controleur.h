#define TAILLE_PIOCHE_INITIALE 56
#define HAUTEUR_PLATEAU_MAX 14
#define LARGEUR_PLATEAU_MAX 48
#define MAX_TAILLE_PSEUDO 48

typedef struct triomino
{
    int min ;
    int sec ;
    int der ;

} TRIOMINO;

typedef struct emplacement
{
    TRIOMINO trio ;
    char pointe ;
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
    BOOL estHumain ;
} JOUEUR_TRIOMINOS;

int main_triominos();
BOOL clic_dans_main_triominos(POINT clic);
BOOL clic_dans_pioche_triominos(POINT clic);
BOOL clic_dans_plateau_triominos(POINT clic);
CASE transforme_point_en_case_triominos(POINT clic);
TRIOMINO transforme_selection_en_triominos(POINT clic, MAIN_J_TRIOMINOS mainJoueurCourant);
