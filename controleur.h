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
	char pseudo[25];	//Pseudo du joueur
} PSEUDO_JOUEUR;

typedef struct CHOIX_JEU
{
	JEU jeu; 			//Jeu choisi
    VARIANTE variante;	//Variante choisie
} CHOIX_JEU;

BOOL est_clic_sur_jouer_menu_accueil(POINT clic);
NB_JOUEURS transforme_clic_en_nb_joueurs();
CHOIX_JEU transforme_clic_en_choix_jeu();
BOOL veut_rejouer();
