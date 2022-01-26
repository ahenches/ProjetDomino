/*#ifndef MODELE_H_TRIOMINOS
#define MODELE_H_TRIOMINOS*/

#define N_COUPS_MAXIMAL 20
#define POINTE_MIN 0
#define POINTE_SEC 1
#define POINTE_DER 2
void affiche_triomino_modele(TRIOMINO t);
void affiche_main_joueur(MAIN_J_TRIOMINOS mj);
void affiche_plateau_modele(EMPLACEMENT **tabEmplacement);
typedef struct coup
{
  int indice_trio_dans_main;
  int indice_ligne;
  int indice_colonne;
  // char pointe;
} COUP; // utiliser dans la fonction jeu_ordinateur

typedef enum HEXAGONE
{
  AUCUN,
  SIMPLE,
  DOUBLE,
  TRIPLE
} HEXAGONE;



void initialise_ordis(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs);
EMPLACEMENT **initialise_plateau();
PIOCHE_TRIOMINOS initialise_pioche();
int joueur_qui_commence(NB_JOUEURS nb_joueurs,
                        JOUEUR_TRIOMINOS *joueurs, PIOCHE_TRIOMINOS pioche_initiale);
void distribution(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs,
                  PIOCHE_TRIOMINOS *pioche_initiale);
BOOL test_fin(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs,
              PIOCHE_TRIOMINOS pioche, EMPLACEMENT **tabEmplacement);

BOOL pioche(MAIN_J_TRIOMINOS *main, PIOCHE_TRIOMINOS *pioche);
BOOL est_plateau_vide(EMPLACEMENT **tabEmplacement);
int trouve_coups_legaux(JOUEUR_TRIOMINOS j, EMPLACEMENT **tabEmplacement,
                        COUP *coups_legaux[N_COUPS_MAXIMAL]);
void rearrange_main_joueur(MAIN_J_TRIOMINOS *main, int indice_main);

int placer_trio(TRIOMINO TrioAPlacer, EMPLACEMENT **tabEmpl, int l, int c);
int placer_trio_bis(TRIOMINO TrioAPlacer, EMPLACEMENT **tabEmpl, int l, int c);
BOOL verif_coup_valide(int v1, int v2, TRIOMINO trio);
int jeu_ordinateur(JOUEUR_TRIOMINOS ordi, EMPLACEMENT **tabEmplacement);
int est_hexagone(TRIOMINO TrioAPlacer, EMPLACEMENT **tabEmpl, int l, int c);
BOOL est_pont(TRIOMINO TrioAPlacer, EMPLACEMENT **tabEmpl, int l, int c);

//#endif
