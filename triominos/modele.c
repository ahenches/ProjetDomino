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

void affiche_main_joueur(MAIN_J_TRIOMINOS mj)
{
  printf("affiche_main\nTAILLE_main_joueur : %d \n", mj.taille);
  for(int i = 0; i<mj.taille; i++){
    affiche_triomino_modele(mj.tab[i]);
  }
}

void affiche_joueurs(NB_JOUEUR nb_joueur, JOUEUR_TRIOMINOS *j)
{
  printf("affiche_tout_les_joueurs\n\nTAILLE_JOUEUR_HUMAIN : %d \nTAILLE_JOUEUR_ORDI : %d\n\n", nb_joueur.nbJouHum, nb_joueur.nbJouOrdi);
  for(int i = 0; i<nb_joueur.nbJouHum; i++){
    printf("JOUEUR : %s\n", j[i].pseudo);
    affiche_main_joueur(j[i].mainJoueur);
  }
  for(int i = 0; i<nb_joueur.nbJouOrdi; i++){
    printf("ORDI : %s\n", j[nb_joueur.nbJouHum+i].pseudo);
    affiche_main_joueur(j[nb_joueur.nbJouHum+i].mainJoueur);
  }
}

void affiche_pioche(PIOCHE_TRIOMINOS mj)
{
  printf("affiche_pioche\n\nTAILLE_pioche : %d \n", mj.taille);
  for(int i = 0; i<mj.taille; i++){
    affiche_triomino_modele(mj.tab[i]);
  }
}

int main_second()
{
    //declarations

    // JOUEUR_TRIOMINOS joueurs[15];
    // int tailleJoueurs;
    // MAIN_J_TRIOMINOS mainJoueur;
    // PIOCHE_TRIOMINOS jeuPioche;
    // EMPLACEMENT **tabEmplacement;
    //
    // // initialisation
    // NB_JOUEUR nb_joueur = {3, 7};
    // for (int i=0;i<3;i++){
    //   scanf("%s", joueurs[i].pseudo);
    //   joueurs[i].mainJoueur.taille = 0;
    //   joueurs[i].estHumain = 1;
    // }
    // initialise_ordis(nb_joueur, joueurs);
    // tabEmplacement = initialise_plateau();
    // jeuPioche = initialise_pioche();
    // jeuPioche.taille = TAILLE_PIOCHE_INITIALE;
    // mainJoueur.taille = 0;
    //
    //
    //
    //
    // affiche_joueurs(nb_joueur, joueurs);
    // affiche_pioche(jeuPioche);
    //
    // distribution(nb_joueur, joueurs, &jeuPioche);
    //
    // affiche_joueurs(nb_joueur, joueurs);
    // affiche_pioche(jeuPioche);

    TRIOMINO t = {1, 2, 4};
    if (verif_coup_valide(4, 2, t)) printf("VRAI");
    else printf("FAUX");

    // affiche_pioche(jeuPioche);
    // affiche_main_joueur(mainJoueur);
    //
    // pioche(&mainJoueur, &jeuPioche);
    //
    // affiche_pioche(jeuPioche);
    // affiche_main_joueur(mainJoueur);


    return 0 ;

}

EMPLACEMENT ** initialise_plateau()
{
  EMPLACEMENT **plateau;
  int i, j;

  plateau = (EMPLACEMENT **)(malloc(HAUTEUR_PLATEAU_MAX*sizeof(EMPLACEMENT *)));
  for (i = 0; i < HAUTEUR_PLATEAU_MAX; i++){
    plateau[i] = malloc(sizeof(EMPLACEMENT) * LARGEUR_PLATEAU_MAX);

    // for (j = 0; j < LARGEUR_PLATEAU_MAX; j++){
    //   plateau
    // }

  }
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

void initialise_ordis(NB_JOUEUR nb_joueur, JOUEUR_TRIOMINOS *joueurs)
{
  for(int i = 0; i<(nb_joueur.nbJouHum+nb_joueur.nbJouOrdi);i++)
  {
    strcpy(joueurs[nb_joueur.nbJouHum+i].pseudo, "ordi");
    joueurs[nb_joueur.nbJouHum+i].pseudo[4] = i+'0';
    joueurs[nb_joueur.nbJouHum+i].pseudo[5] = 0;
    joueurs[nb_joueur.nbJouHum+i].mainJoueur.taille = 0;
    joueurs[nb_joueur.nbJouHum+i].estHumain = 0;
  }
}

JOUEUR_TRIOMINOS joueur_qui_commence(NB_JOUEUR nb_joueur,
  JOUEUR_TRIOMINOS *joueurs, PIOCHE_TRIOMINOS *pioche_initiale)
{
  int sommeValTrioJou[(nb_joueur.nbJouHum+nb_joueur.nbJouOrdi)] ;
  int max ;
  JOUEUR_TRIOMINOS jouComm ;
  for(int i=0; i<(nb_joueur.nbJouHum+nb_joueur.nbJouOrdi); i++)
  {
    pioche(&joueurs[i].mainJoueur, pioche_initiale);
    TRIOMINO trio= joueurs[i].mainJoueur.tab[0] ;
    sommeValTrioJou[i]=trio.min+trio.sec+trio.der ;
  }
  max = sommeValTrioJou[0];
  for(int i=0; i<(nb_joueur.nbJouHum+nb_joueur.nbJouOrdi); i++)
  {
    if (sommeValTrioJou[i]>max)
      jouComm = joueurs[i] ;
    else
      jouComm = joueurs[0] ;
  }
  return(jouComm);
}

void distribution(NB_JOUEUR nb_joueur, JOUEUR_TRIOMINOS *joueurs,
  PIOCHE_TRIOMINOS *pioche_initiale)
{
  int nb_de_triomino_distribue = 3;
  for(int i = 0; i<(nb_joueur.nbJouHum+nb_joueur.nbJouOrdi);i++)
  {

    for(int j = 0; j<nb_de_triomino_distribue;j++)
    {
      pioche(&joueurs[i].mainJoueur, pioche_initiale);
    }
    // affiche_pioche(*pioche_initiale);
  }
}

void pioche(MAIN_J_TRIOMINOS *main, PIOCHE_TRIOMINOS *pioche)
{
  if (pioche->taille > 0)
  {
    srand ( time(NULL) );
    int random_number = rand() % pioche->taille;
    TRIOMINO triomino = pioche->tab[random_number];
    // affiche_triomino_modele(triomino);
    // printf("ATTENTION :%d\n",main->taille);
    main->tab[main->taille] = triomino;
    main->taille ++;
    pioche->tab[random_number] = pioche->tab[pioche->taille-1];
    pioche->taille --;
  }
}

// void jeu_ordinateur(JOUEUR_TRIOMINOS ordi, EMPLACEMENT **tabEmplacement){
  // int i, j;
  // EMPLACEMENT emplacements_possibles[HAUTEUR_PLATEAU_MAX*LARGEUR_PLATEAU_MAX];

  // for (i = 0; i < HAUTEUR_PLATEAU_MAX; i++){
    // for (j = 0; j < LARGEUR_PLATEAU_MAX; j++){
      // if (tabEmplacement[i][j].trio != NULL){
        // affiche_triomino_modele(tabEmplacement[i][j].trio);

      // }
    // }
  // }
  // return plateau;
// }

// BOOL placer_trio()

BOOL verif_coup_valide(int v1 , int v2 , TRIOMINO trio)
{
  BOOL test=false;
  if(v1<v2)
  {
    if ( (v1 == trio.min && v2==trio.der) )
      test= true;
  }
  else
  {
    if( (v1== trio.der&& v2==trio.sec) || (v1==trio.sec && v2==trio.min) )
      test= true ;
  }
  return test ;
}
