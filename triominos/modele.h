#define N_COUPS_MAXIMAL 20
typedef struct coup
{
  int indice_trio_dans_main;
  int indice_ligne;
  int indice_colonne;
} COUP; // utiliser dans la fonction jeu_ordinateur

typedef enum HEXAGONE
{
  AUCUN,
	SIMPLE,
	DOUBLE,
  TRIPLE,
} HEXAGONE;

void initialise_ordis(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs);
EMPLACEMENT ** initialise_plateau();
PIOCHE_TRIOMINOS initialise_pioche();
int joueur_qui_commence(NB_JOUEURS nb_joueurs,
  JOUEUR_TRIOMINOS *joueurs, PIOCHE_TRIOMINOS pioche_initiale);
void distribution(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs,
  PIOCHE_TRIOMINOS *pioche_initiale);
BOOL test_fin(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs,
  PIOCHE_TRIOMINOS pioche, EMPLACEMENT **tabEmplacement);

int trouve_coups_legaux(JOUEUR_TRIOMINOS j, EMPLACEMENT **tabEmplacement,
  COUP *coups_legaux[N_COUPS_MAXIMAL]);
void pioche(MAIN_J_TRIOMINOS *main, PIOCHE_TRIOMINOS *pioche);
int placer_trio(TRIOMINO TrioAPlacer, EMPLACEMENT **tabEmpl, int c, int l);
BOOL verif_coup_valide(int v1, int v2, TRIOMINO trio);
// INT verifie_figure();
int jeu_ordinateur(JOUEUR_TRIOMINOS ordi, EMPLACEMENT **tabEmplacement);
BOOL est_hexagone(TRIOMINO TrioAPlacer , EMPLACEMENT **tabEmpl, int l, int c);
