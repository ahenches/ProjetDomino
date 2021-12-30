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

typedef struct main_joueur
{
    TRIOMINO tab[25];
    int taille;
} MAIN_JOUEUR;

typedef struct {
    int l ;
    int c ;
} CASE ;

int main_triominos();
BOOL clic_dans_main_triominos(POINT clic);
BOOL clic_dans_pioche_triominos(POINT clic);
BOOL clic_dans_plateau_triominos(POINT clic);
CASE transforme_point_en_case_triominos(POINT clic);
TRIOMINO transforme_selection_en_triominos(POINT clic, MAIN_JOUEUR mainJoueurCourant);
