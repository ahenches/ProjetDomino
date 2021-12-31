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
// JOUEUR joueur_qui_commence();
void pioche(MAIN_TRIOMINOS *main, PIOCHE_TRIOMINOS *pioche);
// VOID placer();
// BOOL verifie_coup_valide(INT valeur1, INT valeur2, TRIOMINO a_placer);
// INT verifie_figure();
// BOOL test_fin();
// INT calcule_score(JOUEUR j);
// void jeu_ordinateur(JOUEUR ordi);
