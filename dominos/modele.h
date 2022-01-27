//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

// Prototypes Modèle
void initialise_plateau_domino();
void initialise_joueurs(JOUEUR infos_joueurs[], int totJoueurs);
NB_JOUEURS entre_nb_joueurs(NB_JOUEURS joueurs);
void entre_pseudos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs);
VARIANTE choix_variante();
void genere_pioche();
int determine_nb_dominos_main(int totJoueur);
void distribue_premiers_dominos(JOUEUR infos_joueurs[], int totJoueur);
DOMINO pioche_un_domino(JOUEUR *infos_joueur);
int compte_double_pioche();
int est_double(DOMINO domino);
void definit_premier_joueur(JOUEUR infos_joueurs[], int nbDominosMain);
int determine_joueur_suivant(int tour, int totJoueur, JOUEUR infos_joueurs[]);
DOMINO recupere_choix_domino_main(DOMINO mainActive[], COORDONNEES indicesExtremite1, COORDONNEES indicesExtremite2);
int trouve_indice_domino_main(DOMINO mainActive[], DOMINO domino);
POINT transforme_coord_point(COORDONNEES **indiceExtremite, EXTREMITE_COMPATIBLE direction, int tourJeu);
BOOL place_domino(DOMINO *dominoAPlacer, COORDONNEES *indiceExtremite1, COORDONNEES *indiceExtremite2, int tourJeu, DOMINO mainActive[]);
BOOL verifie_compatibilite_main(DOMINO mainActive[], COORDONNEES indicesExtremite1, COORDONNEES indicesExtremite2);
AIDE_PLACEMENT verifie_compatibilite_domino(DOMINO *domino, COORDONNEES indicesExtremite1, COORDONNEES indicesExtremite2, int inverse);
BOOL joue_IA(JOUEUR *infos_joueur, COORDONNEES *indiceExtremite1, COORDONNEES *indiceExtremite2, int tourJeu, VARIANTE variante);
CHOIX_JOUEUR joue_joueur(JOUEUR *infos_joueur, COORDONNEES *indiceExtremite1, COORDONNEES *indiceExtremite2, int tourJeu, VARIANTE variante, int tour);
int compte_dominos_pioche();
int verifie_gagnant(JOUEUR infos_joueurs[], COORDONNEES indiceExtremite1, COORDONNEES indiceExtremite2, int totJoueurs, VARIANTE variante);
void calcule_score(int *score, DOMINO dominoPose);
int gere_clics(DOMINO main[]);
void ecrit_scores_fichier(JOUEUR infos_joueurs[], int totJoueurs);

//#endif