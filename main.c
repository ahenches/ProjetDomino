#include <stdio.h>
#include "lib/lib.h"
#include "triominos/vue.h"

int main() {
	TRIOMINO trio1;
	trio1.premier = 1; trio1.second = 2; trio1.dernier = 3;
	EMPLACEMENT emp;
	emp.triomino = trio1;
	emp.pointe = 's';
	
	CASE case1;
	case1.l = 6; case1.c = 20;
	
	ouvre_fenetre(1300,900);
	affiche_plateau_triminos();
	attend_clic();
	
	affiche_triomino(case1,emp);
	case1.l = 7;
	affiche_triomino(case1,emp);
	
	case1.l = 6; case1.c = 19;
	affiche_triomino(case1,emp);
	
	case1.l = 6; case1.c = 18;
	affiche_emplacement_possible(case1);
	
	attend_clic();
	
	return 0;
}
