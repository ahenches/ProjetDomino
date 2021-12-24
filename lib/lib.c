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

SDL_Surface *ecran = NULL;                 // totalité de l'écran
SDL_Event lastevent ;                      // utilisé pour gestion événements
Trace_evts trace_evts ;                    // idem
POINT dernier_clic = {-1,-1};
int LARGEUR = -1 ;                         // largeur de l'écran en pixels
int HAUTEUR = -1 ;                         // hauteur de l'écran en pixels
//char *NOM_POLICE = "../lib/verdana.ttf" ;
char *NOM_POLICE = "../lib/verdana.ttf" ;
#define octets_par_pixel ecran->format->BytesPerPixel
#define largeur_ecran (ecran->pitch / 4)
int dans_ecran(int x, int y)
	{
	if (x<0) return 0;
	if (x>=LARGEUR) return 0;
	if (y<0) return 0;
	if (y>=HAUTEUR) return 0;
	return 1;
	}
#define ajout_pix(x,y,couleur)  if (dans_ecran((x),(y))) *((COULEUR *)ecran->pixels + (HAUTEUR-(y)-1) * LARGEUR + (x)) = (couleur)


////////////////////////////////////////////////////////////////////////////////
// 1. Ouvrir et fermer une fenêtre

// ouvrir une fenêtre de taille largeur (x), hauteur (y)
void ouvre_fenetre(int largeur, int hauteur){
    SDL_Init(SDL_INIT_VIDEO); 
    ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE|SDL_DOUBLEBUF ); 

    //initialisation des variables globales
    LARGEUR = largeur ;
    HAUTEUR = hauteur ;
    //printf("LARGEUR %d HAUTEUR %d\n",LARGEUR,HAUTEUR);

    // pour permettre les répétitions de touche si elles restent enfoncées
    SDL_EnableKeyRepeat(5, 5);

    //initialisation du hasard
    srand(time(NULL));
}


// terminer le programme
void ferme_fenetre(){
    SDL_Quit();
    exit(0);
}

// teste si la fin du programme a été demandée et le termine si nécessaire
void teste_arret() {
    if ((lastevent.type == SDL_QUIT) || 
            ( (lastevent.type == SDL_KEYDOWN )
              && (lastevent.key.keysym.sym == SDLK_ESCAPE)) 
       )
        ferme_fenetre() ;
}


///////////////////////////////////////////////////////////////////////////////
// 2. Fonctions de dessin

// actualise l'affichage des modifications graphiques
// sans appel à cet fonction les modifications sont non apparentes
void actualise_affichage(){
    SDL_PollEvent(&lastevent) ;
    teste_arret();
    SDL_Flip(ecran) ;
}


// fonction de dessin principale
// changer la couleur du POINT pix
void change_pixel(POINT pix, COULEUR couleur) {
    if ((0 <= pix.x) && (pix.x < LARGEUR) && (0 <= pix.y ) && (pix.y < HAUTEUR))
    {
        *( (Uint32*)ecran->pixels + pix.y * largeur_ecran + pix.x ) = couleur ;
    }
}


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

// trace une ligne du POINT p1 au point p2 dela couleur donnée
// utilise l'algorithme de Bresenham
void dessine_ligne(POINT p1, POINT p2, COULEUR couleur)
{
    // signes deplacement x et y
    int dx, dy ;

    if (p1.x < p2.x)
        dx = 1 ;
    else if (p1.x > p2.x)
        dx = -1 ;
    else
        dx = 0 ;

    if (p1.y < p2.y)
        dy = 1 ;
    else if (p1.y > p2.y)
        dy = -1 ;
    else
        dy = 0 ;

    // valeur absolue pente
    float pente_abs ; 

    float erreur = 0;
    POINT p ; // point courant

    //lignes horizontales et certicales : plus rapide
    if (dy == 0) 
    {
        p.y = p1.y ;
        for(p.x = p1.x ; p.x != p2.x ; p.x += dx)
            change_pixel(p,couleur);
    }
    else if (dx == 0)
    {  
        p.x = p1.x ;
        for(p.y = p1.y ; p.y != p2.y ; p.y += dy)
            change_pixel(p,couleur);
    }
    else
    {

        pente_abs  = (p2.y - p1.y)/((float)(p2.x - p1.x)) ;
        if (pente_abs < 0)
            pente_abs = - pente_abs ;

        if (pente_abs <=1 )
        {
            {
                p.y = p1.y ; 
                for(p.x = p1.x ; p.x != p2.x ; p.x += dx)
                {
                    change_pixel(p, couleur);
                    erreur += pente_abs ;
                    if (erreur > 0.5)
                    {
                        erreur -= 1 ;
                        p.y += dy ;
                    }
                }
            }
        }
        else 
        {
            pente_abs = 1/pente_abs ;
            p.x = p1.x ; 
            for(p.y = p1.y ; p.y != p2.y ; p.y += dy)
            {
                change_pixel(p, couleur);
                erreur += pente_abs ;
                if (erreur > 0.5)
                {
                    erreur -= 1 ;
                    p.x += dx ;
                }
            }
        }
    }
    change_pixel(p2,couleur);
}

void dessine_rectangle_plein(POINT p1, POINT p2, COULEUR couleur)
{
	int xmin, xmax;
	int ymin, ymax;
	int i,j;
	
	if (p1.x < p2.x) {xmin=p1.x; xmax=p2.x;} else{xmin=p2.x; xmax=p1.x;}
	if (p1.y < p2.y) {ymin=p1.y; ymax=p2.y;} else{ymin=p2.y; ymax=p1.y;}
	
	for (i=xmin;i<=xmax;i++) for (j=ymin;j<=ymax;j++) ajout_pix(i,j,couleur);
}
//dessine un disque (cercle plein) de couleur voulue en donnant rayon et centre
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



// affiche l'image sous forme .bmp (bitmap), contenue dans le même dossier
// nom est une chaine de caracteres qui est le nom (complet) du fichier image
// coin est le coin haut, gauche voulu pour l'image à afficher dans l'ecran
void affiche_image(char *nom, POINT coin){
    SDL_Surface *img = SDL_LoadBMP(nom) ;
    SDL_Rect position_img ;
    position_img.x = coin.x;
    position_img.y = coin.y;
    SDL_BlitSurface(img,NULL,ecran,&position_img);
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
POINT attend_clic() {
    do {
        SDL_WaitEvent(&lastevent) ;
        teste_arret();
    }
    while (lastevent.type != SDL_MOUSEBUTTONDOWN) ;
    POINT p ;
    p.x = lastevent.button.x ;
    p.y = lastevent.button.y ;

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
TTF_Font * __police = NULL ;  // police courante , ne pas modidier

//affiche du texte de taille de police donnée ; coin est le coin haut gauche du texte
void affiche_texte(char *texte, int taille, POINT coin, COULEUR couleur)
{
    static int ttf_deja_init = 0 ; //appel seulement la premiere fois
    static TTF_Font *polices[256] ; //les polices de toutes tailles
    if (!ttf_deja_init)
    {
        TTF_Init();
        int i;
        for(i=1;i<256;i++)
            polices[i] = TTF_OpenFont(NOM_POLICE, i);

        ttf_deja_init = 1;
    }

    __police = polices[taille] ;

    if (texte[0] != '\0')
    {
        SDL_Color coul_police ;
        SDL_GetRGB(couleur,ecran->format,&(coul_police.r),&(coul_police.g),&(coul_police.b));

        SDL_Surface *surftexte= TTF_RenderText_Blended(__police, texte, coul_police);
        SDL_Rect position;
        position.x = coin.x;
        position.y=  coin.y;
        SDL_BlitSurface(surftexte, NULL, ecran, &position);
    }
}

void rempli_ecran(COULEUR couleur)
{
	int i,j;
	for (i=0;i<LARGEUR;i++)
		for (j=0;j<HAUTEUR;j++) *((COULEUR *)ecran->pixels + (HAUTEUR-j-1) * HAUTEUR + i) = couleur;
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
    return ((r%256)<<16) + ((g%256)<<8) + (b%256);
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
