#include <stdio.h>
#include <stdlib.h>

#include <time.h>


#include "../lib/lib.h"
#include "controleur.h"
#include "modele.h"
#include "vue.h"




// avant main fonction de tests
void affiche_triomino_modele(TRIOMINO t)
{
  printf("%d  %d  %d\n", t.min, t.sec, t.der);
}

void affiche_main_joueur(MAIN_TRIOMINOS mj)
{
  printf("affiche_main_joueur\n\n");
  for(int i = 0; i<mj.taille; i++){
    affiche_triomino_modele(mj.tab[i]);
  }
}

int main_second()
{
    //declarations

    MAIN_TRIOMINOS mainJoueur; // TRIOMINO * init_main_joueur();
    PIOCHE_TRIOMINOS jeuPioche;
    EMPLACEMENT **tabEmplacement;

    // initialise_plateau
    tabEmplacement = initialise_plateau();
    jeuPioche = initialise_pioche();
    jeuPioche.taille = TAILLE_PIOCHE_INITIALE;

    for(int i=0; i < TAILLE_PIOCHE_INITIALE; i++)
    {
      affiche_triomino_modele(jeuPioche.tab[i]);
    }



    mainJoueur.taille = 0;

    pioche(mainJoueur, jeuPioche);


    return 0 ;

}

EMPLACEMENT ** initialise_plateau()
{
  EMPLACEMENT **plateau;
  int i;

  plateau = (EMPLACEMENT **)(malloc(HAUTEUR_PLATEAU_MAX*sizeof(EMPLACEMENT *)));
  for (i = 0; i < HAUTEUR_PLATEAU_MAX; i++)
    plateau[i] = malloc(sizeof(EMPLACEMENT) * LARGEUR_PLATEAU_MAX);
  return plateau;
}

PIOCHE_TRIOMINOS initialise_pioche()
{
  PIOCHE_TRIOMINOS pioche_triominos;
  int indicePioche;
  // TRIOMINO t;

  // pioche = malloc(sizeof(TRIOMINO) * TAILLE_PIOCHE_INITIALE);

  indicePioche = 0;
  for (int i=0 ; i<6 ; i++)
  {
    for (int j=i ; j<6 ; j++)
    {
      for (int k=j ; k<6 ; k++)
      {
        TRIOMINO t = {i, j, k};
        pioche_triominos.tab[indicePioche] = t;
        indicePioche++;
      }
    }
  }
  return pioche_triominos;
}

void pioche(MAIN_TRIOMINOS main, PIOCHE_TRIOMINOS pioche)
{
  // int tab_indices_triominos_restants[TAILLE_PIOCHE_INITIALE];
  // int indice_indices_triominos_restants;
  //
  // indice_indices_triominos_restants = 0;
  // for (int i=0;i<TAILLE_PIOCHE_INITIALE;i++)
  // {
  //   if (pioche[i].min) != -1)
  //     indices_triominos_restants[indice_indices_triominos_restants++] = i;
  // }
  if (pioche.taille > 0)
  {
    srand ( time(NULL) );
    int random_number = rand() % pioche.taille;
    TRIOMINO triomino = pioche.tab[random_number];
  }
}
