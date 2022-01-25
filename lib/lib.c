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

////////////////////////////////////////////////////////////////////////////////
// 0. directives préprocesseur

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lib.h"

////////////////////////////////////////////////////////////////////////////////
// 0. variables globales et macros

SDL_Surface *ecran = NULL; // totalité de l'écran
SDL_Event lastevent;       // utilisé pour gestion événements
Trace_evts trace_evts;     // idem
POINT dernier_clic = {-1, -1};
int LARGEUR = -1; // largeur de l'écran en pixels
int HAUTEUR = -1; // hauteur de l'écran en pixels
char *NOM_POLICE = "../lib/verdana.ttf";
// char *NOM_POLICE = "../lib/verdana.ttf" ;

#define octets_par_pixel ecran->format->BytesPerPixel
#define largeur_ecran (ecran->pitch / 4)
int dans_ecran(int x, int y)
{
    if (x < 0)
        return 0;
    if (x >= LARGEUR)
        return 0;
    if (y < 0)
        return 0;
    if (y >= HAUTEUR)
        return 0;
    return 1;
}
#define ajout_pix(x, y, couleur) \
    if (dans_ecran((x), (y)))    \
    *((COULEUR *)ecran->pixels + (HAUTEUR - (y)-1) * LARGEUR + (x)) = (couleur)

////////////////////////////////////////////////////////////////////////////////
// 1. Ouvrir et fermer une fenêtre

// ouvrir une fenêtre de taille largeur (x), hauteur (y)
void ouvre_fenetre(int largeur, int hauteur)
{

    //~ FILE *f=fopen(NOM_POLICE,"r");
    //~ if(!f)
    //~ {
    //~ fprintf(stderr,"Erreur: le chemin '%s' ne permet pas de trouver le dossier 'lib' et la police 'verdana.ttf'\n",NOM_POLICE);
    //~ exit(1);
    //~ }
    //~ fclose(f);

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    // initialisation des variables globales
    LARGEUR = largeur;
    HAUTEUR = hauteur;
    // printf("LARGEUR %d HAUTEUR %d\n",LARGEUR,HAUTEUR);

    // pour permettre les répétitions de touche si elles restent enfoncées
    SDL_EnableKeyRepeat(5, 5);

    // initialisation du hasard
    srand(time(NULL));


}

// terminer le programme
void ferme_fenetre()
{
    SDL_Quit();
    exit(0);
}

// teste si la fin du programme a été demandée et le termine si nécessaire
void teste_arret()
{
    if ((lastevent.type == SDL_QUIT) ||
        ((lastevent.type == SDL_KEYDOWN) && (lastevent.key.keysym.sym == SDLK_ESCAPE)))
        ferme_fenetre();
}

///////////////////////////////////////////////////////////////////////////////
// 2. Fonctions de dessin

// actualise l'affichage des modifications graphiques
// sans appel à cet fonction les modifications sont non apparentes
void actualise_affichage()
{
    SDL_PollEvent(&lastevent);
    teste_arret();
    SDL_Flip(ecran);
}

// fonction de dessin principale
// changer la couleur du POINT pix
void change_pixel(POINT pix, COULEUR couleur)
{
    if ((0 <= pix.x) && (pix.x < LARGEUR) && (0 <= pix.y) && (pix.y < HAUTEUR))
    {
        *((Uint32 *)ecran->pixels + pix.y * largeur_ecran + pix.x) = couleur;
    }
}

/*
// dessine un rectangle de couleur de largeur et hauteur données
// coin est le coin haut, gauche
void dessine_rectangle(POINT coin, int largeur, int hauteur, COULEUR couleur) {
    POINT p ;
    int bord_droit = coin.x + largeur ;
    int bord_bas = coin.y + hauteur ;
    for (p.x = coin.x; p.x < bord_droit ; ++(p.x)) {
        for (p.y = coin.y ; p.y  < bord_bas ; ++(p.y) ) {
            change_pixel(p, couleur);
        }
    }
}
*/

void dessine_rectangle(POINT p1, POINT p2, COULEUR color)
{
    int xmin, xmax;
    int ymin, ymax;
    int i, j;

    if (p1.x < p2.x)
    {
        xmin = p1.x;
        xmax = p2.x;
    }
    else
    {
        xmin = p2.x;
        xmax = p1.x;
    }
    if (p1.y < p2.y)
    {
        ymin = p1.y;
        ymax = p2.y;
    }
    else
    {
        ymin = p2.y;
        ymax = p1.y;
    }

    for (i = xmin; i <= xmax; i++)
        ajout_pix(i, ymin, color);
    for (i = xmin; i <= xmax; i++)
        ajout_pix(i, ymax, color);

    for (j = ymin; j <= ymax; j++)
        ajout_pix(xmin, j, color);
    for (j = ymin; j <= ymax; j++)
        ajout_pix(xmax, j, color);
}

// trace une ligne du POINT p1 au point p2 dela couleur donnée
// utilise l'algorithme de Bresenham
void dessine_ligne(POINT p1, POINT p2, COULEUR couleur)
{
    int xmin, xmax;
    int ymin, ymax;
    int i, j;
    float a, b, ii, jj;

    if (p1.x < p2.x)
    {
        xmin = p1.x;
        xmax = p2.x;
    }
    else
    {
        xmin = p2.x;
        xmax = p1.x;
    }
    if (p1.y < p2.y)
    {
        ymin = p1.y;
        ymax = p2.y;
    }
    else
    {
        ymin = p2.y;
        ymax = p1.y;
    }

    if (xmin == xmax)
        for (j = ymin; j <= ymax; j++)
            ajout_pix(xmin, j, couleur);
    if (ymin == ymax)
        for (i = xmin; i <= xmax; i++)
            ajout_pix(i, ymin, couleur);

    // La variation la plus grande est en x
    if ((xmax - xmin >= ymax - ymin) && (ymax - ymin > 0))
    {
        a = (float)(p1.y - p2.y) / ((float)(p1.x - p2.x));
        b = p1.y - a * p1.x;
        for (i = xmin; i <= xmax; i++)
        {
            jj = a * i + b;
            j = jj;
            if (((jj - j) > 0.5) && (j < HAUTEUR - 1))
                j++;
            ajout_pix(i, j, couleur);
        }
    }

    // La variation la plus grande est en y
    if ((ymax - ymin > xmax - xmin) && (xmax - xmin > 0))
    {
        a = (float)(p1.y - p2.y) / ((float)(p1.x - p2.x));
        b = p1.y - a * p1.x;
        for (j = ymin; j <= ymax; j++)
        {
            ii = (j - b) / a;
            i = ii;
            if (((ii - i) > 0.5) && (i < LARGEUR - 1))
                i++;
            ajout_pix(i, j, couleur);
        }
    }
}

void dessine_rectangle_plein(POINT p1, POINT p2, COULEUR couleur)
{
    int xmin, xmax;
    int ymin, ymax;
    int i, j;

    if (p1.x < p2.x)
    {
        xmin = p1.x;
        xmax = p2.x;
    }
    else
    {
        xmin = p2.x;
        xmax = p1.x;
    }
    if (p1.y < p2.y)
    {
        ymin = p1.y;
        ymax = p2.y;
    }
    else
    {
        ymin = p2.y;
        ymax = p1.y;
    }

    for (i = xmin; i <= xmax; i++)
        for (j = ymin; j <= ymax; j++)
            ajout_pix(i, j, couleur);
}
// dessine un disque (cercle plein) de couleur voulue en donnant rayon et centre
/*void dessiner_disque(POINT centre, int rayon, COULEUR couleur)
{
    int xmin = centre.x - rayon ;
    int xmax = centre.x + rayon ;
    int ymin = centre.y - rayon ;
    int ymax = centre.y + rayon ;

    POINT p ;

    for (p.x = xmin; p.x <= xmax ; p.x++)
    {
        for (p.y = ymin; p.y <= ymax ; p.y++)
            if ( (centre.x-p.x)*(centre.x-p.x) + (centre.y-p.y)*(centre.y-p.y) <= rayon * rayon )
                change_pixel(p, couleur);
    }
}

*/

void dessine_triangle(POINT p1, POINT p2, POINT p3, COULEUR couleur)
{
    dessine_ligne(p1, p2, couleur);
    dessine_ligne(p2, p3, couleur);
    dessine_ligne(p3, p1, couleur);
}

// 4.11 Dessine un triangle rempli
// Fonction annexe qui calcule le min de 3 valeurs
int min3(int a, int b, int c)
{
    if ((a < b) && (a < c))
        return a;
    if ((b < a) && (b < c))
        return b;
    return c;
}

// Fonction annexe qui calcule le max de 3 valeurs
int max3(int a, int b, int c)
{
    if ((a > b) && (a > c))
        return a;
    if ((b > a) && (b > c))
        return b;
    return c;
}

void dessine_triangle_plein(POINT p1, POINT p2, POINT p3, COULEUR couleur)
{
    float a12, b12, a23, b23, a31, b31;
    float s1, s2, s3;
    // La droite passant par les point pi et pj
    // a pour équation : y = aij x  +  bij
    a12 = (p1.y - p2.y) / (float)(p1.x - p2.x);
    b12 = p1.y - a12 * p1.x;
    a23 = (p2.y - p3.y) / (float)(p2.x - p3.x);
    b23 = p2.y - a23 * p2.x;
    a31 = (p3.y - p1.y) / (float)(p3.x - p1.x);
    b31 = p3.y - a31 * p3.x;
    // Le signe de sk détermine de quel coté pk est de la droite [pi,pj]
    s3 = p3.y - (a12 * p3.x + b12);
    s1 = p1.y - (a23 * p1.x + b23);
    s2 = p2.y - (a31 * p2.x + b31);

    int minx, maxx, miny, maxy;
    minx = min3(p1.x, p2.x, p3.x);
    maxx = max3(p1.x, p2.x, p3.x);
    miny = min3(p1.y, p2.y, p3.y);
    maxy = max3(p1.y, p2.y, p3.y);

    int i, j;
    int ok;
    for (i = minx; i < maxx; i++)
        for (j = miny; j < maxy; j++)
        {
            ok = 1;
            // On vérifie que le point (i,j) est du bon coté
            // des 3 droites du triangle
            if (s3 * (j - (a12 * i + b12)) < 0)
                ok = 0;
            if (s1 * (j - (a23 * i + b23)) < 0)
                ok = 0;
            if (s2 * (j - (a31 * i + b31)) < 0)
                ok = 0;
            if (ok)
                ajout_pix(i, j, couleur);
        }
}

// affiche l'image sous forme .bmp (bitmap), contenue dans le même dossier
// nom est une chaine de caracteres qui est le nom (complet) du fichier image
// coin est le coin haut, gauche voulu pour l'image à afficher dans l'ecran
void affiche_image(char *nom, POINT coin)
{
    SDL_Surface *img = SDL_LoadBMP(nom);
    SDL_Rect position_img;
    position_img.x = coin.x;
    position_img.y = HAUTEUR - coin.y;
    SDL_BlitSurface(img, NULL, ecran, &position_img);
}

////////////////////////////////////////////////////////////////////////////////
// 3. Gestion des événements
/*
// renvoie le code SDLK de la prochaine touche pressée
// fonction bloquante
int attendre_touche(void){
    do {
        SDL_WaitEvent(&lastevent) ;
        teste_arret();
    }
    while (lastevent.type != SDL_KEYDOWN ) ;
    return lastevent.key.keysym.sym;
}
*/
// renvoie les coordonnees du prochain clic (gauche ou droite) de souris
// fonction bloquante
POINT attend_clic()
{
    do
    {
        SDL_WaitEvent(&lastevent);
        teste_arret();
    } while (lastevent.type != SDL_MOUSEBUTTONDOWN);
    POINT p;
    p.x = lastevent.button.x;
    p.y = HAUTEUR - lastevent.button.y;
    printf("%cClic en %4d %4d \n", 13, p.x, p.y);
    return p;
}
/*
//comme la fonction attendre clic, mais on ajoute un signe
//négatif devant les coordonnées du point si c'est un clic droit
POINT attendre_clic_gauche_droite() {
    do {
        SDL_WaitEvent(&lastevent) ;
        teste_arret();
    }
    while (lastevent.type != SDL_MOUSEBUTTONDOWN) ;
    POINT p ;
    if (lastevent.button.button==SDL_BUTTON_RIGHT)
    {
        p.x = - lastevent.button.x ;
        p.y = - lastevent.button.y ;
    }
    else
    {
        p.x = lastevent.button.x ;
        p.y = lastevent.button.y ;
    }

    return p;
}

*/
////////////////////////////////////////////////////////////////////////////////
// 3 bis : fonctions optionnelles pour les événements, non bloquantes

/*
//reinitialise la mémoire des événements à 0
void reinitialiser_evenements(void)
{
    memset(trace_evts.touches, 0, sizeof(trace_evts.touches)) ;
    dernier_clic.x = -1;
    dernier_clic.y = -1;
}
*/
/*
// memorise les evenements ayant eu lieu depuis la derniere
// reinitialisation
void traiter_evenements(void)
{

    while(SDL_PollEvent(&lastevent))
    {
        switch(lastevent.type)
        {
            case SDL_MOUSEMOTION:
                trace_evts.sourisx = lastevent.motion.x;
                trace_evts.sourisy = lastevent.motion.y;
                break;
            case SDL_KEYDOWN:
                trace_evts.touches[lastevent.key.keysym.sym]=1 ;
                break ;
            case SDL_MOUSEBUTTONDOWN:
                dernier_clic.x = lastevent.motion.x ;
                dernier_clic.y = lastevent.motion.y ;
        }

    }

}
*/
/*
// indique si la touche de code SDL en question a été pressée
// entre la derniere reinitialisation et le dernier traitement
int touche_a_ete_pressee(int code)
{
    return trace_evts.touches[code] ;
}
*/

/*
//renvoie les coordonnees du dernier clic entre la
// entre la derniere reinitialisation et le dernier traitement
// POINT (-1,-1) si pas de clic
POINT clic_a_eu_lieu()
{
    POINT res = dernier_clic ;
    dernier_clic.x = -1;
    dernier_clic.y = -1 ;
    return res;
}
*/

/*
// renvoie un point de coordonnées relatives souris obtenu
// entre la derniere reinitialisation et le dernier traitement
// (0,0) au lancement, dernière position reçue si sortie de fenêtre
POINT deplacement_souris_a_eu_lieu()
{
    POINT res;
    res.x = trace_evts.sourisx;
    res.y = trace_evts.sourisy;
    return res;
}
*/
////////////////////////////////////////////////////////////////////////////////
// 4. Affichage de texte
// pour fonctionner, la police doit se trouver dans le dossier lib
// (la police peut être changée en changeant la variable globale NOM_POLICE )

// TEXTE
TTF_Font *__police = NULL; // police courante , ne pas modidier

// affiche du texte de taille de police donnée ; coin est le coin haut gauche du texte
void affiche_texte(char *texte, int taille, POINT coin, COULEUR couleur)
{
    static int ttf_deja_init = 0;  // appel seulement la premiere fois
    static TTF_Font *polices[256]; // les polices de toutes tailles
    if (!ttf_deja_init)
    {
        TTF_Init();
        int i;
        for (i = 0; i < 256; i++)
            polices[i] = TTF_OpenFont(NOM_POLICE, i);

        ttf_deja_init = 1;
    }

    __police = polices[taille];

    if (texte[0] != '\0')
    {
        SDL_Color coul_police;
        SDL_GetRGB(couleur, ecran->format, &(coul_police.r), &(coul_police.g), &(coul_police.b));

        SDL_Surface *surftexte = TTF_RenderText_Blended(__police, texte, coul_police);
        SDL_Rect position;
        position.x = coin.x;
        position.y = HAUTEUR - coin.y;
        SDL_BlitSurface(surftexte, NULL, ecran, &position);
    }
}

void affiche_entier(int n, int taille, POINT coin, COULEUR couleur)
{
    char s[32];
    sprintf(s, "%d", n);
    affiche_texte(s, taille, coin, couleur);
}

/*
void affiche_texte(char *a_ecrire, int taille, POINT p, COULEUR C)
{
        int i;
        SDL_Color color;
        SDL_Surface *texte = NULL;
        SDL_Rect position;
        static int premiere_fois = 1;
        static TTF_Font *__police[256];
        TTF_Font *pol;

        // Initialisation de la police (n'est fait qu'une seule fois pour les tailles < 256)
        if (premiere_fois)  { TTF_Init(); for (i=0;i<256;i++) __police[i] = NULL; premiere_fois = 0;}
        if (taille>=256) pol = TTF_OpenFont(NOM_POLICE, taille);
            else {
             if (__police[taille]==NULL) __police[taille] = TTF_OpenFont(NOM_POLICE, taille);
                 pol = __police[taille];
             }
        SDL_GetRGB(C,ecran->format,&(color.r),&(color.g),&(color.b));


        if (pol) texte = TTF_RenderText_Blended(pol, "Main", color); else texte = NULL;printf("%s \n",texte);
        if (texte)  {
                position.x = p.x;
                position.y = HAUTEUR - p.y;
                SDL_BlitSurface(texte, NULL, ecran, &position);
            SDL_FreeSurface(texte);
                }
            else printf("%s\n",a_ecrire);

        taille = 0; p.x = p.y = 0; C = 0;
        printf("%s marche pas\n",a_ecrire);

}
*/

void rempli_ecran(COULEUR couleur)
{
    int i, j;
    for (i = 0; i < LARGEUR; i++)
        for (j = 0; j < HAUTEUR; j++)
            *((COULEUR *)ecran->pixels + (HAUTEUR - j - 1) * LARGEUR + i) = couleur;
}

/*
//renvoie un point qui contient la taille en pixels que prendrait ce texte si on l'affichait
//(largeur,hauteur) à la taille de police donnée
POINT taille_texte(char *texte, int taille)
{   POINT p = {-10, -10};
    affiche_texte("", taille, p, noir) ; //pour fixer __police
    TTF_SizeText(__police, texte, &p.x, &p.y);
    return p;
}
*/

////////////////////////////////////////////////////////////////////////////////
// 5. Autres

// renvoie une COULEUR (UInt32) RGB avec les valeurs entre 0 et 255 données
// en rouge r, vert g et bleu b
COULEUR fabrique_couleur(int r, int g, int b)
{
    COULEUR C;
    return ((r % 256) << 16) + ((g % 256) << 8) + (b % 256);
    return C;
}

/*
// pause le programme pour une duree en millisecondes
void attente(int duree_ms)
{
    SDL_Delay(duree_ms);
}
*/

/*
//renvoie la couleur du point donné ; renvoie noir si le point est hors de l'écran
COULEUR couleur_point(POINT p)
{

    if ((0 <= p.x) && (p.x < LARGEUR) && (0 <= p.y ) && (p.y < HAUTEUR))
    {
        return *( (Uint32*)ecran->pixels + p.y * largeur_ecran + p.x ) ;
    }
    else
        return noir ;
}
*/

/*
//renvoie un entier au hasard entre 0 et n-1
int entier_aleatoire(int n)
{
    return rand() % n ;
}
*/
