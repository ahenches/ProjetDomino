#include <stdio.h>
#include <stdlib.h>
#include "../lib/lib.h"
#include "controleur.h"
#include "modele.h"
#include "vue.h"


#define TAILLE_PIOCHE_INITIALE 56
// avant main fonction de tests
void affiche_triomino_modele(TRIOMINO t)
{
  printf("%d  %d  %d\n", t.min, t.sec, t.der);
}
void affiche_main_joueur(MAIN_JOUEUR mj)
{
  printf("affiche_main_joueur\n\n");
  for(int i = 0; i<mj.taille; i++){
    affiche_triomino_modele(mj.tab[i]);
  }
}

int main_second()
{
    //declarations
    // int nbPersonne;
    // int nbTrio;
    int taillePioche;

    MAIN_JOUEUR mainJoueur; // TRIOMINO * init_main_joueur();
    TRIOMINO *tabPioche;
    EMPLACEMENT **tabEmplacement;



    // initialise_plateau
    tabEmplacement = initialise_plateau();
    tabPioche = initialise_pioche();
    taillePioche = TAILLE_PIOCHE_INITIALE;

    // for(int i=0; i < TAILLE_PIOCHE_INITIALE; i++)
    // {
    //   affiche_triomino_modele(tabPioche[i]);
    // }



    mainJoueur.taille = 0;

    pioche(mainJoueur, tabPioche, taillePioche);

    // TRIO TRIOMINOS[4][9];
    //
    // // Nombre de joueurs
    // printf("Entrez le nombre de joueurs: ");
    // scanf("%d", &nbPersonne);
    //
    // if ( (nbPersonne==3) || (nbPersonne==4) )
    //     nbTrio = 7;
    // else if(nbPersonne==2)
    //     nbTrio = 9 ;
    // //Mains des joueurs
    // TRIOMINOS[nbPersonne][nbTrio];
    //
    //
    // // créer la pioche
    // for(int j=0 ; j<nb; j++)
    // {
    //   for (int i=0 ; i<nbTrio ; i++)
    //   {
    //       printf("MIN du triomino n%d: ",i+1);
    //       scanf("%d", &TRIOMINOS[j][i].min);
    //       printf("SEC du triomino n%d: ",i+1);
    //       scanf("%d", &TRIOMINOS[j][i].sec);
    //       printf("DER du triomino n%d: ",i+1);
    //       scanf("%d", &TRIOMINOS[j][i].der);
    //   }
    // }
    // PIOCHE
    // printf("La liste des TRIOMINOS: \n");
    // printf("-------------------------- \n");
    // for(int j=0 ; j<nb ; j++)
    // {
    //     for (int i=0 ; i<nbTrio ; i++)
    //     {
    //         printf("%d/ MIN: %d SEC: %d DER: %d\n",i+1,TRIOMINOS[j][i].min,TRIOMINOS[j][i].sec,TRIOMINOS[j][i].der);
    //     }
    //     printf("-------------------------- \n");
    // }
    return 0 ;

}

EMPLACEMENT ** initialise_plateau() 
{
  EMPLACEMENT **plateau;
  int i;

  plateau = (EMPLACEMENT **) (malloc(52*sizeof(EMPLACEMENT *)));
  for (i = 0; i < 52; i++)
    plateau[i] = malloc(sizeof(EMPLACEMENT) * 52);
  return plateau;
}

TRIOMINO * initialise_pioche()
{
  TRIOMINO *pioche;
  int indicePioche;
  // TRIOMINO t;

  pioche = malloc(sizeof(TRIOMINO) * TAILLE_PIOCHE_INITIALE);

  indicePioche = 0;
  for (int i=0 ; i<6 ; i++)
  {
    for (int j=i ; j<6 ; j++)
    {
      for (int k=j ; k<6 ; k++)
      {
        TRIOMINO t = {i, j, k};
        pioche[indicePioche] = t;
        indicePioche++;
      }
    }
  }
  return pioche;
}

void pioche(MAIN_JOUEUR main, TRIOMINO *pioche, int taillePioche)
{
  // je vais le faire
}
