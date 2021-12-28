#include <stdio.h>
#include "lib/lib.h"
#include "triominos/vue.h"

int main() {
	TRIOMINO trio1;
	trio1.premier = 1; trio1.second = 2; trio1.dernier = 3;
	EMPLACEMENT emp;
	emp.triomino = trio1;
	emp.pointe = 's';
	
	ouvre_fenetre(1300,900);
	affiche_plateau_triminos();
	attend_clic();
	affiche_triomino(6,20,emp);
	affiche_triomino(7,20,emp);
	affiche_triomino(6,19,emp);
	
	attend_clic();
	
	return 0;
}
