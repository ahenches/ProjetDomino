// Bochra et Arnaud
typedef struct nb_joueur
{
    int nbJouHum;
    int nbJouOrdi;
} NB_JOUEUR;

EMPLACEMENT ** initialise_plateau();
PIOCHE_TRIOMINOS initialise_pioche();
void initialise_ordis(NB_JOUEUR nb_joueur, JOUEUR_TRIOMINOS *joueurs);
void distribution(NB_JOUEUR nb_joueur, JOUEUR_TRIOMINOS *joueurs,
  PIOCHE_TRIOMINOS *pioche_initiale);
JOUEUR_TRIOMINOS joueur_qui_commence(NB_JOUEUR nb_joueur,
  JOUEUR_TRIOMINOS *joueurs, PIOCHE_TRIOMINOS *pioche_initiale);

void pioche(MAIN_J_TRIOMINOS *main, PIOCHE_TRIOMINOS *pioche);
// VOID placer();
BOOL verif_coup_valide(int v1, int v2, TRIOMINO trio);
// INT verifie_figure();
// BOOL test_fin();
// INT calcule_score(JOUEUR j);
void jeu_ordinateur(JOUEUR_TRIOMINOS ordi, EMPLACEMENT **tabEmplacement);
