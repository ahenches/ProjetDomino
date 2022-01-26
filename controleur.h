#define MAX_TAILLE_PSEUDO 48

typedef enum VARIANTE
{
	SANS_PIOCHE,
	AVEC_PIOCHE,
	SANS_SCORE,
	AVEC_SCORE,
} VARIANTE;

typedef enum JEU
{
	DOMINOS,
	TRIOMINOS,
} JEU;

typedef struct NB_JOUEURS
{
	int nbJoueurHumain; // Nombre de joueurs humains
	int nbJoueurIA;		// Nombre d'IA
} NB_JOUEURS;

typedef struct PSEUDO_JOUEUR
{
	char pseudo[25]; // Pseudo du joueur
} PSEUDO_JOUEUR;

typedef struct CHOIX_JEU
{
	JEU jeu;		   // Jeu choisi
	VARIANTE variante; // Variante choisie
} CHOIX_JEU;

BOOL est_clic_sur_jouer_menu_accueil(POINT clic);
NB_JOUEURS transforme_clic_en_nb_joueurs();
CHOIX_JEU transforme_clic_en_choix_jeu();
BOOL veut_rejouer();

/*#ifndef CONTROLEUR_H_DOMINOS
#define CONTROLEUR_H_DOMINOS*/

//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

// defines
#define TAILLE_TAB_DOMINOS 28 // 28 dominos en longueur ou largeur
#define RESH_FENETRE 600
#define RESV_FENETRE 626
#define TOT_JOUEURS 4
#define NB_MAX_DOMINO_MAIN 21
#define SDL_TTF_OK // police
#define VRAI 1
#define FAUX 0

// Structures et enums
typedef enum CHOIX_JOUEUR
{
	TOUR_NON_FINI,
	TOUR_FINI,
	QUITTER
} CHOIX_JOUEUR;
typedef enum ORIENTATION
{
	HORIZONTALE,
	VERTICALE,
	RIEN
} ORIENTATION;

typedef enum EXTREMITE_COMPATIBLE
{
	GAUCHE,
	DROITE,
	LES_DEUX,
	HAUT,
	BAS,
	AUCUN_DOMINO,
} EXTREMITE_COMPATIBLE;

typedef struct DOMINO
{
	int valeur1; // Valeur Bas ou Gauche du domino
	int valeur2; // Valeur Haut ou Droite du domino
	ORIENTATION orientation;
} DOMINO;

typedef struct COORDONNEES
{
	int ligne;
	int colonne;
	POINT coin;
} COORDONNEES;

typedef struct AIDE_PLACEMENT // aide la fonction place_domino à placer ou non un domino et à quelle extrémité
{
	BOOL compatible;
	EXTREMITE_COMPATIBLE extremite;

} AIDE_PLACEMENT;

typedef struct JOUEUR
{
	char pseudo[20];					   // pseudo du joueur
	DOMINO mainJoueur[NB_MAX_DOMINO_MAIN]; // main du joueur
	int score;							   // score du joueur
} JOUEUR;

// variables globales
extern DOMINO plateau[TAILLE_TAB_DOMINOS][TAILLE_TAB_DOMINOS]; // Plateau de jeu [ligne][colonne]
extern DOMINO pioche_domino[TAILLE_TAB_DOMINOS];

// Prototype Contôleur
void main_dominos(JOUEUR infos_joueurs[], NB_JOUEURS joueurs, VARIANTE pioche);

//#endif
