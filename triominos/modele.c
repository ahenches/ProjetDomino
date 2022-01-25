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

    JOUEUR_TRIOMINOS joueurs[15];
    int tailleJoueurs;
    MAIN_J_TRIOMINOS mainJoueur;
    PIOCHE_TRIOMINOS jeuPioche;
    EMPLACEMENT **tabEmplacement;

    // initialisation
    NB_JOUEUR nb_joueur = {3, 7};
    for (int i=0;i<3;i++){
      scanf("%s", joueurs[i].pseudo);
      joueurs[i].mainJoueur.taille = 0;
      joueurs[i].estHumain = 1;
    }
    initialise_ordis(nb_joueur, joueurs);
    tabEmplacement = initialise_plateau();
    jeuPioche = initialise_pioche();
    jeuPioche.taille = TAILLE_PIOCHE_INITIALE;
    mainJoueur.taille = 0;

    affiche_joueurs(nb_joueur, joueurs);
    affiche_pioche(jeuPioche);

    distribution(nb_joueur, joueurs, &jeuPioche);
    TRIOMINO t = {1,2,3};
    tabEmplacement[HAUTEUR_PLATEAU_MAX/2][LARGEUR_PLATEAU_MAX/2].pointe = 's';
    tabEmplacement[HAUTEUR_PLATEAU_MAX/2][LARGEUR_PLATEAU_MAX/2].trio = t;

    TRIOMINO tt = {1,1,2};

    // placer_trio(tt, tabEmplacement, )

    affiche_joueurs(nb_joueur, joueurs);
    affiche_pioche(jeuPioche);

    // TRIOMINO t = {1, 2, 4};
    // if (verif_coup_valide(4, 2, t)) printf("VRAI");
    // else printf("FAUX");



    printf("\njeu ordinateur\n");
    jeu_ordinateur(joueurs[3], tabEmplacement);

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
    for (j = 0; j < LARGEUR_PLATEAU_MAX; j++){
      TRIOMINO t = {-1, -1, -1};
      plateau[i][j].trio = t;
      plateau[i][j].pointe = 'm';
      if ((i + j) % 2)
        plateau[i][j].direction = 'n';
      else
        plateau[i][j].direction = 's';
    }

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

void jeu_ordinateur(JOUEUR_TRIOMINOS ordi, EMPLACEMENT **tabEmplacement)
{
  int i, j, k;
  int haut, droite, gauche, bas;
  COUP coup_possible[15];
  COUP coup_impossible[15];
  int taille_coup_possible = 0, taille_coup_impossible = 0;
  BOOL coup_legal;

  for (i = 0; i < HAUTEUR_PLATEAU_MAX; i++)
  {
    for (j = 0; j < LARGEUR_PLATEAU_MAX; j++)
    {
      if (tabEmplacement[i][j].trio.min != -1)
      {
        for (k = 0; k < ordi.mainJoueur.taille; k++)
        {
          if (tabEmplacement[i][j].direction == 'n')
          // pointe est vers le nord
          // test gauche droite et bas
          {
            if (tabEmplacement[i][j].pointe == 'm')
            {
              haut = tabEmplacement[i][j].trio.min;
              droite = tabEmplacement[i][j].trio.sec;
              gauche = tabEmplacement[i][j].trio.der;
            }
            else if (tabEmplacement[i][j].pointe == 's')
            {
              haut = tabEmplacement[i][j].trio.sec;
              droite = tabEmplacement[i][j].trio.der;
              gauche = tabEmplacement[i][j].trio.min;
            }
            else
            {
              haut = tabEmplacement[i][j].trio.der;
              droite = tabEmplacement[i][j].trio.min;
              gauche = tabEmplacement[i][j].trio.sec;
            }
            // GAUCHE
            if (tabEmplacement[i][j-1].trio.min == -1)
            {
              COUP c = {k, i, j-1};
              if (verif_coup_valide(gauche, haut, ordi.mainJoueur.tab[k]))
              {
                coup_possible[taille_coup_possible] = c;
                taille_coup_possible++;
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
            // DROITE
            if (tabEmplacement[i][j+1].trio.min == -1)
            {
              COUP c = {k, i, j+1};
              if (verif_coup_valide(haut, droite, ordi.mainJoueur.tab[k]))
              {
                coup_possible[taille_coup_possible] = c;
                taille_coup_possible++;
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
            // BAS
            if (tabEmplacement[i+1][j].trio.min == -1)
            {
              COUP c = {k, i+1, j};
              if (verif_coup_valide(droite, gauche, ordi.mainJoueur.tab[k]))
              {
                coup_possible[taille_coup_possible] = c;
                taille_coup_possible++;
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
          }
          else
          {
            // pointe est vers le sud
            if (tabEmplacement[i][j].pointe == 'm')
            {
              bas = tabEmplacement[i][j].trio.min;
              gauche = tabEmplacement[i][j].trio.sec;
              droite = tabEmplacement[i][j].trio.der;
            }
            else if (tabEmplacement[i][j].pointe == 's')
            {
              bas = tabEmplacement[i][j].trio.sec;
              gauche = tabEmplacement[i][j].trio.der;
              droite = tabEmplacement[i][j].trio.min;
            }
            else
            {
              bas = tabEmplacement[i][j].trio.der;
              gauche = tabEmplacement[i][j].trio.min;
              droite = tabEmplacement[i][j].trio.sec;
            }
            // GAUCHE
            if (tabEmplacement[i][j-1].trio.min == -1)
            {
              COUP c = {k, i, j-1};
              if (verif_coup_valide(bas, gauche, ordi.mainJoueur.tab[k]))
              {
                coup_possible[taille_coup_possible] = c;
                taille_coup_possible++;
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
            // DROITE
            if (tabEmplacement[i][j+1].trio.min == -1)
            {
              COUP c = {k, i, j+1};
              if (verif_coup_valide(droite, bas, ordi.mainJoueur.tab[k]))
              {
                coup_possible[taille_coup_possible] = c;
                taille_coup_possible++;
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
            // BAS
            if (tabEmplacement[i-1][j].trio.min == -1)
            {
              COUP c = {k, i-1, j};
              if (verif_coup_valide(gauche, droite, ordi.mainJoueur.tab[k]))
              {
                coup_possible[taille_coup_possible] = c;
                taille_coup_possible++;
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
          }
        }
      }
    }
  }

  for (i = 0; i<taille_coup_possible;i++)
  {
    coup_legal = true;
    for (j = 0; j<taille_coup_impossible;j++)
    {
      // test si le coup possible est aussi un coup impossible
      if ((coup_possible[i].indice_trio_dans_main == coup_impossible[j].indice_trio_dans_main) &&
          (coup_possible[i].indice_ligne == coup_impossible[j].indice_ligne) &&
          (coup_possible[i].indice_colonne == coup_impossible[j].indice_colonne))
        coup_legal = false;
    }
    // garde que les coup légales.
    if (!coup_legal)
    {
      if (i != taille_coup_impossible-1)
        coup_possible[i] = coup_possible[taille_coup_impossible-1];
      taille_coup_possible --;
    }
  }
  for (i = 0; i<taille_coup_possible;i++)
  {
    printf("\n COUP POSSIBLE ORDI \n");
    affiche_triomino_modele(
      ordi.mainJoueur.tab[coup_possible[i].indice_trio_dans_main]);
    printf("A l'emplacement ligne : %d colonne : %d \n",
      coup_possible[i].indice_ligne, coup_possible[i].indice_colonne);
  }
}

void placer_trio (TRIOMINO TrioAPlacer, EMPLACEMENT **tabEmpl, int x, int y)
{
  // les x et y on les récupère de la vue
  // on veut placer trio dans la case tabEmpl[x][y]
  // faut ajouter variable dir dans la structure EMPLACEMENT (on peut la mettre en tant que char ou int)
  if(tabEmpl[x][y].trio.min!=-1)
    printf("case pleine! coup impossible");
  else
  {
    if(tabEmpl[x-1][y].trio.min!=-1)
    {
      if (tabEmpl[x-1][y].direction == 'n')
      {
        if (tabEmpl[x-1][y].pointe=='m' || tabEmpl[x-1][y].pointe=='s' )
        {
          if(verif_coup_valide(tabEmpl[x-1][y].trio.min,tabEmpl[x-1][y].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[x-1][y].trio.sec,tabEmpl[x-1][y].trio.der,TrioAPlacer))
          {
            tabEmpl[x][y].trio=TrioAPlacer ;
            tabEmpl[x][y].pointe='d';
          }
        }
        else
        {
          if(verif_coup_valide(tabEmpl[x-1][y].trio.der,tabEmpl[x-1][y].trio.min,TrioAPlacer))
          {
            tabEmpl[x][y].trio=TrioAPlacer ;
            if(TrioAPlacer.min==tabEmpl[x-1][y].trio.sec)
              tabEmpl[x][y].pointe='m';
            else
              tabEmpl[x][y].pointe='s';
          }
        }
      }
      else
      {
        if (tabEmpl[x-1][y].pointe=='s' || tabEmpl[x-1][y].pointe=='d' )
        {
          if(verif_coup_valide(tabEmpl[x-1][y].trio.min,tabEmpl[x-1][y].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[x-1][y].trio.sec,tabEmpl[x-1][y].trio.der,TrioAPlacer))
          {
            tabEmpl[x][y].trio=TrioAPlacer ;
            tabEmpl[x][y].pointe='m';
          }
        }
        else
        {
          if(verif_coup_valide(tabEmpl[x-1][y].trio.der,tabEmpl[x-1][y].trio.min,TrioAPlacer))
          {
            tabEmpl[x][y].trio=TrioAPlacer ;
            if(TrioAPlacer.sec==tabEmpl[x-1][y].trio.min)
              tabEmpl[x][y].pointe='s';
            else
              tabEmpl[x][y].pointe='d';
          }
        }
      }
    }
    else if(tabEmpl[x+1][y].trio.min!=-1)
    {
      if (tabEmpl[x+1][y].direction == 's')
      {
        if (tabEmpl[x+1][y].pointe=='m' || tabEmpl[x+1][y].pointe=='s' )
        {
          if(verif_coup_valide(tabEmpl[x+1][y].trio.min,tabEmpl[x+1][y].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[x+1][y].trio.sec,tabEmpl[x+1][y].trio.der,TrioAPlacer))
          {
            tabEmpl[x][y].trio=TrioAPlacer ;
            tabEmpl[x][y].pointe='d';
          }
        }
        else
        {
          if(verif_coup_valide(tabEmpl[x+1][y].trio.der,tabEmpl[x+1][y].trio.min,TrioAPlacer))
          {
            tabEmpl[x][y].trio=TrioAPlacer ;
            if(TrioAPlacer.min==tabEmpl[x+1][y].trio.min)
              tabEmpl[x][y].pointe='m';
            else
              tabEmpl[x][y].pointe='s';
          }
        }
      }
      else
      {
        if (tabEmpl[x+1][y].pointe=='s' || tabEmpl[x+1][y].pointe=='d' )
        {
          if(verif_coup_valide(tabEmpl[x+1][y].trio.min,tabEmpl[x+1][y].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[x+1][y].trio.sec,tabEmpl[x+1][y].trio.der,TrioAPlacer))
          {
            tabEmpl[x][y].trio=TrioAPlacer ;
            tabEmpl[x][y].pointe='m';
          }
        }
        else
        {
          if(verif_coup_valide(tabEmpl[x+1][y].trio.der,tabEmpl[x+1][y].trio.min,TrioAPlacer))
          {
            tabEmpl[x][y].trio=TrioAPlacer ;
            if(TrioAPlacer.sec==tabEmpl[x+1][y].trio.min)
              tabEmpl[x][y].pointe='d';
            else
              tabEmpl[x][y].pointe='s';
          }
        }
      }
    }

    else if(tabEmpl[x][y-1].trio.min != -1 && tabEmpl[x][y-1].direction=='n')
    {
      if(tabEmpl[x][y-1].pointe=='m' || tabEmpl[x][y-1].pointe=='d')
      {
        if(verif_coup_valide(tabEmpl[x][y-1].trio.min,tabEmpl[x][y-1].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[x][y-1].trio.sec,tabEmpl[x][y-1].trio.der,TrioAPlacer) )
        {
          tabEmpl[x][y].trio=TrioAPlacer ;
          tabEmpl[x][y].pointe='d';
        }
      }
      else if(verif_coup_valide(tabEmpl[x][y-1].trio.der,tabEmpl[x][y-1].trio.min,TrioAPlacer))
      {
        tabEmpl[x][y].trio=TrioAPlacer ;
        tabEmpl[x][y].pointe='d';
      }
    }

    else if (tabEmpl[x][y+1].trio.min!=-1 && tabEmpl[x][y+1].direction=='s')
    {
      if(tabEmpl[x][y+1].pointe=='m' || tabEmpl[x][y+1].pointe=='d')
      {
        if(verif_coup_valide(tabEmpl[x][y+1].trio.min,tabEmpl[x][y+1].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[x][y+1].trio.sec,tabEmpl[x][y+1].trio.der,TrioAPlacer) )
        {
          tabEmpl[x][y].trio=TrioAPlacer ;
          tabEmpl[x][y].pointe='s';
        }
      }
      else if(verif_coup_valide(tabEmpl[x][y+1].trio.der,tabEmpl[x][y+1].trio.min,TrioAPlacer))
      {
        tabEmpl[x][y].trio=TrioAPlacer ;
        if(TrioAPlacer.der==tabEmpl[x][y+1].trio.der)
          tabEmpl[x][y].pointe='d';
        else
          tabEmpl[x][y].pointe='m';
      }
    }
  }
}

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
    if( (v1== trio.der&& v2==trio.sec) || (v1==trio.sec && v2==trio.min))
      test=true;
  }
  return test;
}
