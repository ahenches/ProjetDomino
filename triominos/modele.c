#include <stdio.h>
#include <stdlib.h>

#include <time.h>


#include "../lib/lib.h"
#include "../controleur.h"
#include "controleur.h"
#include "modele.h"
#include "vue.h"

// avant main fonction de tests
void affiche_plateau_modele(EMPLACEMENT **tabEmplacement)
{
  int i, j;
  printf("\nPlateau\n");
  for (i = 0; i < HAUTEUR_PLATEAU_MAX; i++){
    for (j = 0; j < LARGEUR_PLATEAU_MAX; j++){
      if (tabEmplacement[i][j].trio.min != -1)
        printf("%d%d%d", tabEmplacement[i][j].trio.min, tabEmplacement[i][j].trio.sec, tabEmplacement[i][j].trio.der);
      else printf("XXX");
    }
    printf("\n");

  }
  printf("\n");
}

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

void affiche_joueurs(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *j)
{
  printf("affiche_tout_les_joueurs\n\nTAILLE_JOUEUR_HUMAIN : %d \nTAILLE_JOUEUR_ORDI : %d\n\n", nb_joueurs.nbJoueurHumain, nb_joueurs.nbJoueurIA);
  for(int i = 0; i<nb_joueurs.nbJoueurHumain; i++){
    printf("JOUEUR : %s\n", j[i].pseudo);
    affiche_main_joueur(j[i].mainJoueur);
  }
  for(int i = 0; i<nb_joueurs.nbJoueurIA; i++){
    printf("ORDI : %s\n", j[nb_joueurs.nbJoueurHumain+i].pseudo);
    affiche_main_joueur(j[nb_joueurs.nbJoueurHumain+i].mainJoueur);
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
    NB_JOUEURS nb_joueurs = {3, 7};
    for (int i=0;i<3;i++){
      scanf("%s", joueurs[i].pseudo);
      joueurs[i].mainJoueur.taille = 0;
      joueurs[i].estHumain = 1;
    }
    initialise_ordis(nb_joueurs, joueurs);
    tabEmplacement = initialise_plateau();
    jeuPioche = initialise_pioche();
    jeuPioche.taille = TAILLE_PIOCHE_INITIALE;
    mainJoueur.taille = 0;

    affiche_joueurs(nb_joueurs, joueurs);
    affiche_pioche(jeuPioche);

    distribution(nb_joueurs, joueurs, &jeuPioche);

    affiche_joueurs(nb_joueurs, joueurs);
    affiche_pioche(jeuPioche);

    for(int deltal=-1; deltal<1;deltal++){
      for(int deltac=-1; deltac<2;deltac++){
        TRIOMINO t = {0,2+deltal,2+deltac};
        tabEmplacement[7+deltal][24+deltac].pointe='m';
        tabEmplacement[7+deltal][24+deltac].trio = t;
      }
    }
    for(int deltal=0; deltal<2;deltal++){
      for(int deltac=-2; deltac<3;deltac++){
        TRIOMINO t = {0,3+deltal,2+deltac};
        tabEmplacement[7+deltal][24+deltac].pointe='m';
        tabEmplacement[7+deltal][24+deltac].trio = t;
      }
    }
    TRIOMINO t = {1,2,4};
    printf("DIRECTION TEST BOBOU\n%c\n",
      tabEmplacement[HAUTEUR_PLATEAU_MAX/2][LARGEUR_PLATEAU_MAX/2].direction);

    tabEmplacement[HAUTEUR_PLATEAU_MAX/2][LARGEUR_PLATEAU_MAX/2].pointe = 'm';
    tabEmplacement[HAUTEUR_PLATEAU_MAX/2][LARGEUR_PLATEAU_MAX/2].trio = t;
    affiche_plateau_modele(tabEmplacement);
    TRIOMINO triom = {2,2,2};
    TRIOMINO nul = {-1,-1,-1};
    tabEmplacement[8][25].pointe='m';
    affiche_triomino_modele(tabEmplacement[8][25].trio);
    // tabEmplacement[8][25].trio = nul;
    affiche_triomino_modele(tabEmplacement[8][25].trio);
    affiche_plateau_modele(tabEmplacement);
    // if(est_hexagone(triom, tabEmplacement, 8, 25)) printf("VRAI");
    // else printf("FAUX");
    // affiche_plateau_modele(tabEmplacement);

    for(int deltal=0; deltal<2;deltal++){
      for(int deltac=0; deltac<3;deltac++){
        TRIOMINO t = {2,2,2};
        tabEmplacement[7+deltal][24+deltac].pointe='m';
        int r = est_hexagone(t, tabEmplacement, 7+deltal, 24+deltac);
        if(r==0) printf("AUCUN");
        else if (r==1) printf("SIMPLE");
        else if (r==2) printf("DOUBLE");
        else if (r==3) printf("TRIPLE");
      }
    }

    // TRIOMINO tt = {1,5,5};
    // printf("Score %d\n", placer_trio(tt, tabEmplacement, HAUTEUR_PLATEAU_MAX/2, LARGEUR_PLATEAU_MAX/2 + 1));
    // affiche_plateau_modele(tabEmplacement);
    // TRIOMINO ttt = {2,2,3};
    // printf("Score %d\n", placer_trio(ttt, tabEmplacement, HAUTEUR_PLATEAU_MAX/2 + 1, LARGEUR_PLATEAU_MAX/2));

    // affiche_joueurs(nb_joueurs, joueurs);
    // affiche_pioche(jeuPioche);


    // TRIOMINO trio = {1, 2, 4};
    // if (verif_coup_valide(4, 2, t)) printf("VRAI");
    // else printf("FAUX");

    // TRIOMINO trio = {2, 3, 4};
    // joueurs[3].mainJoueur.tab[joueurs[3].mainJoueur.taille++] = trio;

    // for (int ll = 0; ll<joueurs[3].mainJoueur.taille;ll++){
    //   affiche_triomino_modele(joueurs[3].mainJoueur.tab[ll]);
    // }

    // printf("\njeu ordinateur\n");
    // printf("SCORE ordi : %d\n", jeu_ordinateur(joueurs[3], tabEmplacement));
    // affiche_plateau_modele(tabEmplacement);

    // affiche_pioche(jeuPioche);
    // affiche_main_joueur(mainJoueur);
    //
    // pioche(&mainJoueur, &jeuPioche);
    //
    // affiche_pioche(jeuPioche);
    // affiche_main_joueur(mainJoueur);

    return 0 ;
}

void initialise_ordis(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs)
{
  for(int i = 0; i<nb_joueurs.nbJoueurIA;i++)
  {
    strcpy(joueurs[nb_joueurs.nbJoueurHumain+i].pseudo, "ordi");
    joueurs[nb_joueurs.nbJoueurHumain+i].pseudo[4] = i+'0';
    joueurs[nb_joueurs.nbJoueurHumain+i].pseudo[5] = 0;
    joueurs[nb_joueurs.nbJoueurHumain+i].mainJoueur.taille = 0;
    joueurs[nb_joueurs.nbJoueurHumain+i].score = 0;
    joueurs[nb_joueurs.nbJoueurHumain+i].estHumain = 0;
  }
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

int joueur_qui_commence(NB_JOUEURS nb_joueurs,
  JOUEUR_TRIOMINOS *joueurs, PIOCHE_TRIOMINOS pioche_initiale)
{
  int sommeValTrioJou[(nb_joueurs.nbJoueurHumain+nb_joueurs.nbJoueurIA)];
  int max_indice;

  for(int i=0; i<(nb_joueurs.nbJoueurHumain+nb_joueurs.nbJoueurIA); i++)
  {
    pioche(&joueurs[i].mainJoueur, &pioche_initiale);
    TRIOMINO trio = joueurs[i].mainJoueur.tab[0];
    sommeValTrioJou[i] = trio.min+trio.sec+trio.der;
  }
  max_indice = 0;
  for(int i=0; i<(nb_joueurs.nbJoueurHumain+nb_joueurs.nbJoueurIA); i++)
  {
    if (sommeValTrioJou[i]>sommeValTrioJou[max_indice])
      max_indice = i;
  }
  return max_indice;
}

void distribution(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs,
  PIOCHE_TRIOMINOS *pioche_initiale)
{
  int nb_de_triomino_distribue = 3;
  for(int i = 0; i<(nb_joueurs.nbJoueurHumain+nb_joueurs.nbJoueurIA);i++)
  {

    for(int j = 0; j<nb_de_triomino_distribue;j++)
    {
      pioche(&joueurs[i].mainJoueur, pioche_initiale);
    }
    // affiche_pioche(*pioche_initiale);
  }
}

BOOL test_fin(NB_JOUEURS nb_joueurs, JOUEUR_TRIOMINOS *joueurs,
  PIOCHE_TRIOMINOS pioche, EMPLACEMENT **tabEmplacement)
{
  if (pioche.taille > 0)  // pioche n'est pas vide
    return false;
  else  // pioche est vide
  {
    BOOL partieFinie = true;
    COUP *coups;
    int taille_coups_possible;
    for(int i = 0; i<(nb_joueurs.nbJoueurHumain+nb_joueurs.nbJoueurIA);i++)
    {
      taille_coups_possible = trouve_coups_legaux(joueurs[i], tabEmplacement,
        &coups);
      if (taille_coups_possible != 0)
      {
        partieFinie = false;
      }
    }
    return partieFinie;
  }
}

BOOL pioche(MAIN_J_TRIOMINOS *main, PIOCHE_TRIOMINOS *pioche)
{
  // affiche_pioche(*pioche);
  if (pioche->taille > 0)
  {
    if (main->taille < MAX_TAILLE_MAIN)
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
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

void rearrange_main_joueur(MAIN_J_TRIOMINOS main, int indice_main)
{
  if (indice_main != main.taille - 1)
    main.tab[indice_main] = main.tab[main.taille-1];
  main.taille --;
}

BOOL est_plateau_vide(EMPLACEMENT **tabEmplacement)
{
  BOOL est_vide = true;
  int i, j;

  for (i = 0; i < HAUTEUR_PLATEAU_MAX; i++){
    for (j = 0; j < LARGEUR_PLATEAU_MAX; j++){
      if (tabEmplacement[i][j].trio.min != -1)
        est_vide = false;
    }
  }
  return est_vide;
}

int jeu_ordinateur(JOUEUR_TRIOMINOS ordi, EMPLACEMENT **tabEmplacement)
{
  if (est_plateau_vide(tabEmplacement))
  {
    srand ( time(NULL) );
    int random_number = rand() % ordi.mainJoueur.taille;
    TRIOMINO trio_joue = ordi.mainJoueur.tab[random_number];
    tabEmplacement[HAUTEUR_PLATEAU_MAX/2][LARGEUR_PLATEAU_MAX/2].trio =
      trio_joue;
    rearrange_main_joueur(ordi.mainJoueur, random_number);
    affiche_triomino_modele(trio_joue);
  }
  else
  {
    COUP *coups;
    int taille_coups;

    taille_coups = trouve_coups_legaux(ordi, tabEmplacement, &coups);
    if (taille_coups > 0)
    {
      srand ( time(NULL) );
      int random_number = rand() % taille_coups;
      COUP coup_joue = coups[random_number];
      TRIOMINO trio_joue = ordi.mainJoueur.tab[coup_joue.indice_trio_dans_main];
      tabEmplacement[coup_joue.indice_ligne][coup_joue.indice_colonne].trio =
        trio_joue;
      rearrange_main_joueur(ordi.mainJoueur, coup_joue.indice_trio_dans_main);
      return (trio_joue.min + trio_joue.sec + trio_joue.der);
    }
    else
    {
      return 0;
    }
  }
}

int trouve_coups_legaux(JOUEUR_TRIOMINOS joueur, EMPLACEMENT **tabEmplacement,
  COUP *coups_legaux[N_COUPS_MAXIMAL])
{
  int i, j, k;
  int haut, droite, gauche, bas;
  COUP coup_possible[N_COUPS_MAXIMAL];
  COUP coup_impossible[100];
  int taille_coup_possible = 0, taille_coup_impossible = 0;
  BOOL coup_legal;

  for (i = 0; i < HAUTEUR_PLATEAU_MAX; i++)
  {
    for (j = 0; j < LARGEUR_PLATEAU_MAX; j++)
    {
      if (tabEmplacement[i][j].trio.min != -1)
      {
        for (k = 0; k < joueur.mainJoueur.taille; k++)
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
            if (j-1 >= 0 && tabEmplacement[i][j-1].trio.min == -1)
            {
              COUP c = {k, i, j-1};
              if (verif_coup_valide(gauche, haut, joueur.mainJoueur.tab[k]))
              {
                if (taille_coup_possible < N_COUPS_MAXIMAL-1){
                  coup_possible[taille_coup_possible] = c;
                  taille_coup_possible++;
                }
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
            // DROITE
            if (j+1 < LARGEUR_PLATEAU_MAX-1 &&
              tabEmplacement[i][j+1].trio.min == -1)
            {
              COUP c = {k, i, j+1};
              if (verif_coup_valide(haut, droite, joueur.mainJoueur.tab[k]))
              {
                if (taille_coup_possible < N_COUPS_MAXIMAL-1){
                  coup_possible[taille_coup_possible] = c;
                  taille_coup_possible++;
                }
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
            // BAS
            if (i+1 < HAUTEUR_PLATEAU_MAX-1 &&
              tabEmplacement[i+1][j].trio.min == -1)
            {
              COUP c = {k, i+1, j};
              if (verif_coup_valide(droite, gauche, joueur.mainJoueur.tab[k]))
              {
                if (taille_coup_possible < N_COUPS_MAXIMAL-1){
                  coup_possible[taille_coup_possible] = c;
                  taille_coup_possible++;
                }
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
            if (j-1 >= 0 && tabEmplacement[i][j-1].trio.min == -1)
            {
              COUP c = {k, i, j-1};
              if (verif_coup_valide(bas, gauche, joueur.mainJoueur.tab[k]))
              {
                if (taille_coup_possible < N_COUPS_MAXIMAL-1){
                  coup_possible[taille_coup_possible] = c;
                  taille_coup_possible++;
                }
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
            // DROITE
            if (j+1 < LARGEUR_PLATEAU_MAX-1 &&
              tabEmplacement[i][j+1].trio.min == -1)
            {
              COUP c = {k, i, j+1};
              if (verif_coup_valide(droite, bas, joueur.mainJoueur.tab[k]))
              {
                if (taille_coup_possible < N_COUPS_MAXIMAL-1){
                  coup_possible[taille_coup_possible] = c;
                  taille_coup_possible++;
                }
              }
              else
              {
                coup_impossible[taille_coup_impossible] = c;
                taille_coup_impossible++;
              }
            }
            // BAS
            if (i-1 >= 0 && tabEmplacement[i-1][j].trio.min == -1)
            {
              COUP c = {k, i-1, j};
              if (verif_coup_valide(gauche, droite, joueur.mainJoueur.tab[k]))
              {
                if (taille_coup_possible < N_COUPS_MAXIMAL-1){
                  coup_possible[taille_coup_possible] = c;
                  taille_coup_possible++;
                }
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
  *coups_legaux = coup_possible;
  return taille_coup_possible;
}

int placer_trio (TRIOMINO TrioAPlacer, EMPLACEMENT **tabEmpl, int l, int c)
{
  // retourne le score du coup avec les figures si il y en a
  // les c et l on les récupère de la vue
  // on veut placer trio dans la case tabEmpl[l][c]
  // faut ajouter variable dir dans la structure EMPLACEMENT (on peut la mettre en tant que char ou int)
  if(tabEmpl[l][c].trio.min!=-1)
  {
    printf("case pleine! coup impossible");
    return 0 ;
  }
  else
  {
    if(tabEmpl[l-1][c].trio.min!=-1)
    {
      if (tabEmpl[l-1][c].direction == 'n')
      {
        if (tabEmpl[l-1][c].pointe=='m' || tabEmpl[l-1][c].pointe=='s' )
        {
          if(verif_coup_valide(tabEmpl[l-1][c].trio.min,tabEmpl[l-1][c].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[l-1][c].trio.sec,tabEmpl[l-1][c].trio.der,TrioAPlacer))
          {
            tabEmpl[l][c].trio=TrioAPlacer ;
            tabEmpl[l][c].pointe='d';
            return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
              est_hexagone(TrioAPlacer, tabEmpl, l, c);
          }
        }
        else
        {
          if(verif_coup_valide(tabEmpl[l-1][c].trio.der,tabEmpl[l-1][c].trio.min,TrioAPlacer))
          {
            tabEmpl[l][c].trio=TrioAPlacer ;
            if(TrioAPlacer.min==tabEmpl[l-1][c].trio.sec)
              tabEmpl[l][c].pointe='m';
            else
              tabEmpl[l][c].pointe='s';
            return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
              est_hexagone(TrioAPlacer , tabEmpl, l, c);

          }
        }
      }
      else
      {
        if (tabEmpl[l-1][c].pointe=='s' || tabEmpl[l-1][c].pointe=='d' )
        {
          if(verif_coup_valide(tabEmpl[l-1][c].trio.min,tabEmpl[l-1][c].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[l-1][c].trio.sec,tabEmpl[l-1][c].trio.der,TrioAPlacer))
          {
            tabEmpl[l][c].trio=TrioAPlacer ;
            tabEmpl[l][c].pointe='m';
            return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
              est_hexagone(TrioAPlacer , tabEmpl, l, c);
          }
        }
        else
        {
          if(verif_coup_valide(tabEmpl[l-1][c].trio.der,tabEmpl[l-1][c].trio.min,TrioAPlacer))
          {
            tabEmpl[l][c].trio=TrioAPlacer ;
            if(TrioAPlacer.sec==tabEmpl[l-1][c].trio.min)
              tabEmpl[l][c].pointe='s';
            else
              tabEmpl[l][c].pointe='d';
            return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
              est_hexagone(TrioAPlacer , tabEmpl, l, c);
          }
        }
      }
    }
    else if(tabEmpl[l+1][c].trio.min!=-1)
    {
      if (tabEmpl[l+1][c].direction == 's')
      {
        if (tabEmpl[l+1][c].pointe=='m' || tabEmpl[l+1][c].pointe=='s' )
        {
          if(verif_coup_valide(tabEmpl[l+1][c].trio.min,tabEmpl[l+1][c].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[l+1][c].trio.sec,tabEmpl[l+1][c].trio.der,TrioAPlacer))
          {
            tabEmpl[l][c].trio=TrioAPlacer ;
            tabEmpl[l][c].pointe='d';
            return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
              est_hexagone(TrioAPlacer , tabEmpl, l, c);
          }
        }
        else
        {
          if(verif_coup_valide(tabEmpl[l+1][c].trio.der,tabEmpl[l+1][c].trio.min,TrioAPlacer))
          {
            tabEmpl[l][c].trio=TrioAPlacer ;
            if(TrioAPlacer.min==tabEmpl[l+1][c].trio.min)
              tabEmpl[l][c].pointe='m';
            else
              tabEmpl[l][c].pointe='s';
            return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
              est_hexagone(TrioAPlacer , tabEmpl, l, c);
          }
        }
      }
      else
      {
        if (tabEmpl[l+1][c].pointe=='s' || tabEmpl[l+1][c].pointe=='d' )
        {
          if(verif_coup_valide(tabEmpl[l+1][c].trio.min,tabEmpl[l+1][c].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[l+1][c].trio.sec,tabEmpl[l+1][c].trio.der,TrioAPlacer))
          {
            tabEmpl[l][c].trio=TrioAPlacer ;
            tabEmpl[l][c].pointe='m';
            return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
              est_hexagone(TrioAPlacer , tabEmpl, l, c);
          }
        }
        else
        {
          if(verif_coup_valide(tabEmpl[l+1][c].trio.der,tabEmpl[l+1][c].trio.min,TrioAPlacer))
          {
            tabEmpl[l][c].trio=TrioAPlacer ;
            if(TrioAPlacer.sec==tabEmpl[l+1][c].trio.min)
              tabEmpl[l][c].pointe='d';
            else
              tabEmpl[l][c].pointe='s';
            return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
              est_hexagone(TrioAPlacer , tabEmpl, l, c);
          }
        }
      }
    }

    else if(tabEmpl[l][c-1].trio.min != -1 && tabEmpl[l][c-1].direction=='n')
    {
      if(tabEmpl[l][c-1].pointe=='m' || tabEmpl[l][c-1].pointe=='d')
      {
        if(verif_coup_valide(tabEmpl[l][c-1].trio.min,tabEmpl[l][c-1].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[l][c-1].trio.sec,tabEmpl[l][c-1].trio.der,TrioAPlacer) )
        {
          tabEmpl[l][c].trio=TrioAPlacer ;
          tabEmpl[l][c].pointe='d';
          return (TrioAPlacer.min + TrioAPlacer.sec + TrioAPlacer.der)+
            est_hexagone(TrioAPlacer , tabEmpl, l, c);
        }
      }
      else if(verif_coup_valide(tabEmpl[l][c-1].trio.der,tabEmpl[l][c-1].trio.min,TrioAPlacer))
      {
        tabEmpl[l][c].trio=TrioAPlacer ;
        tabEmpl[l][c].pointe='d';
        return (TrioAPlacer.min + TrioAPlacer.sec + TrioAPlacer.der)+
          est_hexagone(TrioAPlacer , tabEmpl, l, c);
      }
    }

    else if (tabEmpl[l][c+1].trio.min!=-1 && tabEmpl[l][c+1].direction=='s')
    {
      if(tabEmpl[l][c+1].pointe=='m' || tabEmpl[l][c+1].pointe=='d')
      {
        if(verif_coup_valide(tabEmpl[l][c+1].trio.min,tabEmpl[l][c+1].trio.sec,TrioAPlacer) || verif_coup_valide(tabEmpl[l][c+1].trio.sec,tabEmpl[l][c+1].trio.der,TrioAPlacer) )
        {
          tabEmpl[l][c].trio=TrioAPlacer;
          tabEmpl[l][c].pointe='s';
          return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
            est_hexagone(TrioAPlacer , tabEmpl, l, c);
        }
      }
      else if(verif_coup_valide(tabEmpl[l][c+1].trio.der,tabEmpl[l][c+1].trio.min,TrioAPlacer))
      {
        tabEmpl[l][c].trio=TrioAPlacer ;
        if(TrioAPlacer.der==tabEmpl[l][c+1].trio.der)
          tabEmpl[l][c].pointe='d';
        else
          tabEmpl[l][c].pointe='m';
        return (TrioAPlacer.min + TrioAPlacer.sec +TrioAPlacer.der)+
          est_hexagone(TrioAPlacer , tabEmpl, l, c);
      }
    }
  }
}

int est_hexagone(TRIOMINO TrioAPlacer , EMPLACEMENT **tabEmpl, int l, int c)
{
  HEXAGONE resultat = AUCUN;
  if (tabEmpl[l][c].direction == 'n')
  {
    BOOL hexagoneEstForme = true;
    for(int deltaL = -1; deltaL<=0; deltaL++)
    {
      for(int deltaC = -1; deltaC<=1; deltaC++)
      {
        if (tabEmpl[l+deltaL][c+deltaC].trio.min == -1)
          hexagoneEstForme = false;
      }
    }
    if (hexagoneEstForme) resultat++;

    hexagoneEstForme = true;
    for(int deltaL = 0; deltaL<=1; deltaL++)
    {
      for(int deltaC = 0; deltaC<=2; deltaC++)
      {
        if (tabEmpl[l+deltaL][c+deltaC].trio.min == -1)
          hexagoneEstForme = false;
      }
    }
    if (hexagoneEstForme) resultat++;

    hexagoneEstForme = true;
    for(int deltaL = 0; deltaL<=1; deltaL++)
    {
      for(int deltaC = -2; deltaC<=0; deltaC++)
      {
        if (tabEmpl[l+deltaL][c+deltaC].trio.min == -1)
          hexagoneEstForme = false;
      }
    }
    if (hexagoneEstForme) resultat++;

    return resultat;
  }
  else // if (tabEmpl[l][c].direction == 's')
  {
    BOOL hexagoneEstForme = true;
    for(int deltaL = 0; deltaL<=1; deltaL++)
    {
      for(int deltaC = -1; deltaC<=1; deltaC++)
      {
        if (tabEmpl[l+deltaL][c+deltaC].trio.min == -1)
          hexagoneEstForme = false;
      }
    }
    if (hexagoneEstForme) resultat++;

    hexagoneEstForme = true;
    for(int deltaL = -1; deltaL<=0; deltaL++)
    {
      for(int deltaC = 0; deltaC<=2; deltaC++)
      {
        if (tabEmpl[l+deltaL][c+deltaC].trio.min == -1)
          hexagoneEstForme = false;
      }
    }
    if (hexagoneEstForme) resultat++;

    hexagoneEstForme = true;
    for(int deltaL = -1; deltaL<=0; deltaL++)
    {
      for(int deltaC = -2; deltaC<=0; deltaC++)
      {
        if (tabEmpl[l+deltaL][c+deltaC].trio.min == -1)
          hexagoneEstForme = false;
      }
    }
    if (hexagoneEstForme) resultat++;
    switch (resultat) {
      case AUCUN: resultat = 0;break;
      case SIMPLE: resultat = 50;break;
      case DOUBLE: resultat = 60;break;
      case TRIPLE: resultat = 70;break;
      default : resultat = 0;break;
    }
    return resultat;
  }
  return false;
}

BOOL est_pont(TRIOMINO TrioAPlacer , EMPLACEMENT **tabEmpl, int l, int c)
{
  int bas, gauche, haut, droite;
  int valeur_pointe_pont_origine, valeur_pointe_pont_destination;
  BOOL estPont;
  if (tabEmpl[l][c].direction == 'n')
  {
    bas = (l+1<= HAUTEUR_PLATEAU_MAX-1 && tabEmpl[l+1][c].trio.min != -1);
    gauche = (c-1>= 0 && tabEmpl[l][c-1].trio.min != -1);
    droite = (c+1<= LARGEUR_PLATEAU_MAX && tabEmpl[l][c+1].trio.min != -1);
    if ((bas + gauche + droite) != 1)
    {
      return false;
    }
    else
    {
      if (bas == 1) return false ;
      else if (gauche == 1)
      {
        estPont = true;
        for(int deltaL = -1; deltaL<=0; deltaL++)
        {
          for (int deltaC = -1; deltaC<4; deltaC++)
          {
            if (!(deltaL == 0 && deltaC == 1))
            {
              if (l+deltaL>= 0 && l+deltaL<= HAUTEUR_PLATEAU_MAX-1 &&
                  c+deltaC>= 0 && c+deltaC<= LARGEUR_PLATEAU_MAX-1 &&
                tabEmpl[l+deltaL][c+deltaC].trio.min == -1) estPont = false;
            }

            if (tabEmpl[l][c].pointe == 'm')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.sec;
            else if (tabEmpl[l][c].pointe == 's')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.der;
            else // if (tabEmpl[l][c+2].pointe == 'd')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.min;

            if (tabEmpl[l][c+2].pointe == 'm')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.der;
            else if (tabEmpl[l][c+2].pointe == 's')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.min;
            else // if (tabEmpl[l][c+2].pointe == 'd')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.sec;
            if (valeur_pointe_pont_origine != valeur_pointe_pont_destination)
              estPont = false;
          }
        }
        return estPont;
      }
      else // if (droite == 1)
      {
        estPont = true;
        for(int deltaL = -1; deltaL<=0; deltaL++)
        {
          for (int deltaC = -3; deltaC<2; deltaC++)
          {
            if (!(deltaL == 0 && deltaC == -1))
            {
              if (l+deltaL>= 0 && l+deltaL<= HAUTEUR_PLATEAU_MAX-1 &&
                  c+deltaC>= 0 && c+deltaC<= LARGEUR_PLATEAU_MAX-1 &&
                tabEmpl[l+deltaL][c+deltaC].trio.min == -1) estPont = false;
            }

            if (tabEmpl[l][c].pointe == 'm')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.der;
            else if (tabEmpl[l][c].pointe == 's')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.min;
            else // if (tabEmpl[l][c+2].pointe == 'd')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.sec;

            if (tabEmpl[l][c+2].pointe == 'm')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.sec;
            else if (tabEmpl[l][c+2].pointe == 's')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.der;
            else // if (tabEmpl[l][c+2].pointe == 'd')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.min;
            if (valeur_pointe_pont_origine != valeur_pointe_pont_destination)
              estPont = false;
          }
        }
        return estPont;
      }
    }
  }
  else // if (tabEmpl[l][c].direction == 's')
  {
    haut = (l-1>= 0 && tabEmpl[l-1][c].trio.min != -1);
    gauche = (c-1>= 0 && tabEmpl[l][c-1].trio.min != -1);
    droite = (c+1<= LARGEUR_PLATEAU_MAX && tabEmpl[l][c+1].trio.min != -1);
    if ((haut + gauche + droite) != 1)
    {
      return false;
    }
    else
    {
      if (haut == 1) return false ;
      else if (gauche == 1)
      {
        estPont = true;
        for(int deltaL = 0; deltaL<=0; deltaL++)
        {
          for (int deltaC = -1; deltaC<4; deltaC++)
          {
            if (!(deltaL == 0 && deltaC == 1))
            {
              if (l+deltaL>= 0 && l+deltaL<= HAUTEUR_PLATEAU_MAX-1 &&
                  c+deltaC>= 0 && c+deltaC<= LARGEUR_PLATEAU_MAX-1 &&
                tabEmpl[l+deltaL][c+deltaC].trio.min == -1) estPont = false;
            }

            if (tabEmpl[l][c].pointe == 'm')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.der;
            else if (tabEmpl[l][c].pointe == 's')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.min;
            else // if (tabEmpl[l][c+2].pointe == 'd')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.sec;

            if (tabEmpl[l][c+2].pointe == 'm')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.sec;
            else if (tabEmpl[l][c+2].pointe == 's')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.der;
            else // if (tabEmpl[l][c+2].pointe == 'd')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.min;
            if (valeur_pointe_pont_origine != valeur_pointe_pont_destination)
              estPont = false;

          }
        }
        return estPont;
      }
      else // if (droite == 1)
      {
        estPont = true;
        for(int deltaL = 0; deltaL<=1; deltaL++)
        {
          for (int deltaC = -3; deltaC<2; deltaC++)
          {
            if (!(deltaL == 0 && deltaC == -1))
            {
              if (l+deltaL>= 0 && l+deltaL<= HAUTEUR_PLATEAU_MAX-1 &&
                  c+deltaC>= 0 && c+deltaC<= LARGEUR_PLATEAU_MAX-1 &&
                tabEmpl[l+deltaL][c+deltaC].trio.min == -1) estPont = false;
            }

            if (tabEmpl[l][c].pointe == 'm')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.sec;
            else if (tabEmpl[l][c].pointe == 's')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.der;
            else // if (tabEmpl[l][c+2].pointe == 'd')
              valeur_pointe_pont_origine = tabEmpl[l][c].trio.min;

            if (tabEmpl[l][c+2].pointe == 'm')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.der;
            else if (tabEmpl[l][c+2].pointe == 's')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.min;
            else // if (tabEmpl[l][c+2].pointe == 'd')
              valeur_pointe_pont_destination = tabEmpl[l][c+2].trio.sec;
            if (valeur_pointe_pont_origine != valeur_pointe_pont_destination)
              estPont = false;
          }
        }
        return estPont;
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
