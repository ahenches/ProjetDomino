//////////////////////////////////////////////////////////////////////////////////////////
//                             	   Header du jeu Domino               	                //
//////////////////////////////////////////////////////////////////////////////////////////

#define LARGEUR 1300
#define HAUTEUR 900
#define LARGEUR_PLATEAU 1260
#define HAUTEUR_PLATEAU 700
#define LARGEUR_MAIN 1100
#define HAUTEUR_MAIN 100
#define LARGEUR_PIOCHE 150
#define BORDURE 20
#define ORDONNEE_BOUTON_QUITTER 840
#define ABSCISSE_BOUTON_QUITTER 1175

// Prototypes Vue
void affiche_domino(DOMINO domino_a_afficher, POINT coin, EXTREMITE_COMPATIBLE direction);
void affiche_domino_main(DOMINO domino_a_afficher, POINT coin);
void affiche_interface(VARIANTE variante);
void affiche_main(JOUEUR infos_joueurs[], int tour);
void affiche_tour(char pseudo[]);
void affiche_fond();
