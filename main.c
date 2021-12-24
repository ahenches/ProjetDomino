#include <stdio.h>
#include "lib/lib.h"
#include "triominos/vue.h"

int main() {
	
	ouvre_fenetre(1300,900);
	affiche_plateau_triminos();
	attend_clic();
	
	return 0;
}
