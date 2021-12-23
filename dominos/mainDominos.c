#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mainDominos.h"

#define TAILLE_TAB 28 // 28 dominos en longueur ou largeur

SDL_Surface *screen = NULL;                 // totalité de l'écran
SDL_Event lastevent ;                      // utilisé pour gestion événements

DOMINO plateau [TAILLE_TAB][TAILLE_TAB]; // Plateau de jeu

// ouvrir une fenêtre de taille largeur (x), hauteur (y)
void init_fenetre(int largeur, int hauteur){
    SDL_Init(SDL_INIT_VIDEO); 
    screen = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE|SDL_DOUBLEBUF ); 

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
void _teste_arret() {
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
void actualise(){
    SDL_PollEvent(&lastevent) ;
    _teste_arret();
    SDL_Flip(screen) ;
}

POINT attendre_clic() {
    do {
        SDL_WaitEvent(&lastevent) ;
        _teste_arret();
    }
    while (lastevent.type != SDL_MOUSEBUTTONDOWN) ;
    POINT p ;
    p.x = lastevent.button.x ;
    p.y = lastevent.button.y ;

    return p;
}


//Fonction pour tester

void affiche_domino()
{
    POINT coin = {100,100};
    SDL_Surface *img = SDL_LoadBMP("./domino.bmp") ;
    SDL_Rect position_img ;
    position_img.x = coin.x;
    position_img.y = coin.y;
    SDL_BlitSurface(img,NULL,screen,&position_img);

    actualise();
}

void initialise_plateau()
{
    int i;
    int j;
    DOMINO emplacementVide;

    emplacementVide.valeur1 = -1; emplacementVide.valeur2 = -1; emplacementVide.orientation = RIEN;
    for (i = 0; i < TAILLE_TAB; i++)
    {
        for (j = 0; j < TAILLE_TAB; j++)
        {
            plateau[i][j]=emplacementVide;
        }
    }

}

void affiche_plateau()
{
    int i;
    int j;
    for (i = 0; i < TAILLE_TAB; i++)
    {
        for (j = 0; j < TAILLE_TAB; j++)
        {
            printf("|%d %d| ",plateau[i][j].valeur1, plateau[i][j].valeur2);
        }
        printf("\n");
    }

}

void genere()
{
    int i;
    int j;
    for (i = 0; i < TAILLE_TAB; i++)
    {
        for (j = 0; j < TAILLE_TAB; j++)
        {
            printf("|%d %d| ",plateau[i][j].valeur1, plateau[i][j].valeur2);
        }
        printf("\n");
    }

}
