/*******************************************************************************
 * libraphique.c                                                               *
 * Quelques fonctions C basées sur la SDl pour réaliser des opérations         *
 * graphiques simples                                                          *
 *                                                                             *
 * Pour compiler en ligne de commande :                                        *
 * gcc ../lib/libgraphique.c prog.c -o resultat                                *
 *           `sdl-config --libs --cflags` -lm -lSDL                            *
 *                                                                             *
 * où                                                                          *
 *             prog.c : votre code source                                      *
 *             resultat    : nom de l'exécutable                               *
 *******************************************************************************
*/

///////////////////////////////////////////////////////////////////////////////
//0. Directive préprocesseur
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "couleur.h"

///////////////////////////////////////////////////////////////////////////////
//1. Déclaration des types "maison"
typedef Uint32 COULEUR;
typedef struct {int x,y;} POINT;
typedef struct {
    int touches[SDLK_LAST] ;
    int sourisx ;
    int sourisy ;
    int boutong ;
    int boutond ;
} Trace_evts ;

////////////////////////////////////////////////////////////////////////////////
// Déclaration des fonctions
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// 1. Ouvrir et fermer une fenêtre

// ouvrir une fenêtre de taille largeur (x), hauteur (y)
void ouvre_fenetre(int largeur, int hauteur);

// terminer le programme
void ferme_fenetre();

// teste si la fin du programme a été demandée et le termine si nécessaire
// ne pas utiliser directement
void teste_arret() ;

////////////////////////////////////////////////////////////////////////////////
// 2. Fonctions de dessin

// actualise l'affichage des modifications graphiques
// sans appel à cet fonction les modifications sont non apparentes
void actualise_affichage();

// fonction de dessin principale
// changer la couleur du POINT pix
void change_pixel(POINT pix, COULEUR couleur) ;

// dessine un rectangle de couleur de largeur et hauteur données
// coin est le coin haut, gauche
void dessine_rectangle(POINT coin, int largeur, int hauteur, COULEUR couleur) ;

// trace une ligne du POINT p1 au point p2 dela couleur donnée
// utilise l'algorithme de Bresenham
void dessine_ligne(POINT p1, POINT p2, COULEUR);

void dessine_rectangle_plein(POINT p1, POINT p2, COULEUR couleur)

//dessine un disque (cercle plein) de couleur voulue en donnant rayon et centre
//void dessiner_disque(POINT centre, int rayon, COULEUR couleur);

// affiche l'image sous forme .bmp (bitmap), contenue dans le même dossier
// nom est une chaine de caracteres qui est le nom (complet) du fichier image
// coin est le coin haut, gauche voulu pour l'image à afficher dans l'ecran
void affiche_image(char *nom, POINT coin);

////////////////////////////////////////////////////////////////////////////////
// 3. Gestion des événements

// renvoie le code SDLK de la prochaine touche pressée
// fonction bloquante
//int attendre_touche(void);

// renvoie les coordonnees du prochain clic (gauche ou droite) de souris
// fonction bloquante
POINT attend_clic() ;

//comme la fonction attendre clic, mais on ajoute un signe
//négatif devant les coordonnées du point si c'est un clic droit
//POINT attendre_clic_gauche_droite() ;


////////////////////////////////////////////////////////////////////////////////
// 3 bis : fonctions optionnelles pour les événements, non bloquantes

//reinitialise la mémoire des événements à 0
//void reinitialiser_evenements(void);

// memorise les evenements ayant eu lieu depuis la derniere
// reinitialisation
//void traiter_evenements(void);

// indique si la touche de code SDL en question a été pressée 
// entre la derniere reinitialisation et le dernier traitement
//int touche_a_ete_pressee(int);

//renvoie les coordonnees du dernier clic obtenu
// entre la derniere reinitialisation et le dernier traitement
// POINT (-1,-1) si pas de clic
//POINT clic_a_eu_lieu();

// renvoie un point de coordonnées relatives souris obtenu
// entre la derniere reinitialisation et le dernier traitement
// (0,0) au lancement, dernière position reçue si sortie de fenêtre
//POINT deplacement_souris_a_eu_lieu();

////////////////////////////////////////////////////////////////////////////////
// 4. Affichage de texte
// pour fonctionner, la police doit se trouver dans le dossier lib
// (la police peut être changée en changeant la variable globale NOM_POLICE )

//affiche du texte de taille de police donnée ; coin est le coin haut gauche du texte
void affiche_texte(char *texte, int taille, POINT coin, COULEUR couleur);

//renvoie un point qui contient la taille en pixels que prendrait ce texte si on l'affichait
//(largeur,hauteur) à la taille de police donnée
//POINT taille_texte(char *texte, int taille);

void rempli_ecran(COULEUR couleur);

////////////////////////////////////////////////////////////////////////////////
// 5. Autres

// renvoie une COULEUR (UInt32) RGB avec les valeurs entre 0 et 255 données
// en rouge r, vert g et bleu b
COULEUR fabrique_couleur(int r, int g, int b);

// pause le programme pour une duree en millisecondes
//void attente(int duree_ms);
    
//renvoie la couleur du point donné ; renvoie noir si le point est hors de l'écran
//COULEUR couleur_point(POINT p);

//renvoie un entier au hasard entre 0 et n-1
//int entier_aleatoire(int n) ;

