#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "couleur.h"

typedef Uint32 COULEUR;
typedef struct
{
    int x, y;
} POINT;
typedef int BOOL;
typedef struct
{
    int touches[SDLK_LAST];
    int sourisx;
    int sourisy;
    int boutong;
    int boutond;
} Trace_evts;

#define TRUE 1
#define True 1
#define true 1
#define FALSE 0
#define False 0
#define false 0

void ouvre_fenetre(int largeur, int hauteur);
void ferme_fenetre();
void teste_arret();
void actualise_affichage();
void change_pixel(POINT pix, COULEUR couleur);
void dessine_rectangle(POINT p1, POINT p2, COULEUR color);
void dessine_ligne(POINT p1, POINT p2, COULEUR);
void dessine_rectangle_plein(POINT p1, POINT p2, COULEUR couleur);
void dessine_triangle(POINT p1, POINT p2, POINT p3, COULEUR couleur);
void dessine_triangle_plein(POINT p1, POINT p2, POINT p3, COULEUR couleur);
void affiche_image(char *nom, POINT coin);
POINT attend_clic();
void affiche_texte(char *texte, int taille, POINT coin, COULEUR couleur);
void affiche_entier(int n, int taille, POINT coin, COULEUR couleur);
void rempli_ecran(COULEUR couleur);
COULEUR fabrique_couleur(int r, int g, int b);
