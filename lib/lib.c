#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lib.h"


SDL_Surface *ecran = NULL;
SDL_Event lastevent;
Trace_evts trace_evts;
POINT dernier_clic = {-1, -1};
int LARGEUR = -1;
int HAUTEUR = -1;
char *NOM_POLICE = "../lib/verdana.ttf";

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


// ouvre une fenêtre de taille largeur , hauteur
void ouvre_fenetre(int largeur, int hauteur)
{
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    // initialisation des variables globales
    LARGEUR = largeur;
    HAUTEUR = hauteur;

    // pour permettre les répétitions de touche si elles restent enfoncées
    SDL_EnableKeyRepeat(5, 5);

    // initialisation du hasard
    srand(time(NULL));
}

// ferme la fenetre
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

// actualise l'affichage indispensable pour faire les affichages sinon rien ne s affiche
void actualise_affichage()
{
    SDL_PollEvent(&lastevent);
    teste_arret();
    SDL_Flip(ecran);
}

// changer la couleur du POINT pix
void change_pixel(POINT pix, COULEUR couleur)
{
    if ((0 <= pix.x) && (pix.x < LARGEUR) && (0 <= pix.y) && (pix.y < HAUTEUR))
    {
        *((Uint32 *)ecran->pixels + pix.y * largeur_ecran + pix.x) = couleur;
    }
}

//dessine le contour d un rectangle, p1 est le coin haut gauche, p2 le coin bas droit
void dessine_rectangle(POINT p1, POINT p2, COULEUR couleur)
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
        ajout_pix(i, ymin, couleur);
    for (i = xmin; i <= xmax; i++)
        ajout_pix(i, ymax, couleur);

    for (j = ymin; j <= ymax; j++)
        ajout_pix(xmin, j, couleur);
    for (j = ymin; j <= ymax; j++)
        ajout_pix(xmax, j, couleur);
}

// dessine une ligne de p1 a p2
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

//dessine un rectangle rempli,  p1 est le coin haut gauche, p2 le coin bas droit
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

//dessine le contour d un triangle, p1,p2,p3 sont ses sommets
void dessine_triangle(POINT p1, POINT p2, POINT p3, COULEUR couleur)
{
    dessine_ligne(p1, p2, couleur);
    dessine_ligne(p2, p3, couleur);
    dessine_ligne(p3, p1, couleur);
}

// calcule le min de 3 valeurs
int min3(int a, int b, int c)
{
    if ((a < b) && (a < c))
        return a;
    if ((b < a) && (b < c))
        return b;
    return c;
}

// calcule le max de 3 valeurs
int max3(int a, int b, int c)
{
    if ((a > b) && (a > c))
        return a;
    if ((b > a) && (b > c))
        return b;
    return c;
}

//dessine un triangle rempli, p1, p2 et p3 sont ses sommets
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

//affiche l'image qui se trouve a l'adresse nom, point est le coin haut gauche de l'emplacement de l'image
void affiche_image(char *nom, POINT coin)
{
    SDL_Surface *img = SDL_LoadBMP(nom);
    SDL_Rect position_img;
    position_img.x = coin.x;
    position_img.y = HAUTEUR - coin.y;
    SDL_BlitSurface(img, NULL, ecran, &position_img);
}

// renvoie les coordonnees du prochain clic de souris
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

TTF_Font *__police = NULL;

// affiche du texte de taille taille, coin est le coin haut gauche du texte
void affiche_texte(char *texte, int taille, POINT coin, COULEUR couleur)
{
    static int ttf_deja_init = 0;
    static TTF_Font *polices[256];
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

//affiche un entier de taille taille, coin est le coint haut gauche
void affiche_entier(int n, int taille, POINT coin, COULEUR couleur)
{
    char s[32];
    sprintf(s, "%d", n);
    affiche_texte(s, taille, coin, couleur);
}

//Colorie l ecran entier de la couleur donnée
void rempli_ecran(COULEUR couleur)
{
    int i, j;
    for (i = 0; i < LARGEUR; i++)
        for (j = 0; j < HAUTEUR; j++)
            *((COULEUR *)ecran->pixels + (HAUTEUR - j - 1) * LARGEUR + i) = couleur;
}

// renvoie une COULEUR (UInt32) RGB avec les valeurs entre 0 et 255 données
// en rouge r, vert g et bleu b
COULEUR fabrique_couleur(int r, int g, int b)
{
    COULEUR C;
    return ((r % 256) << 16) + ((g % 256) << 8) + (b % 256);
    return C;
}
