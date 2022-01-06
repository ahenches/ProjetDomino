#include <stdio.h>
#include "lib/lib.h"
#include "triominos/controleur.h"

int main()
{

	ouvre_fenetre(1300, 900);

	main_triominos();

	attend_clic();

	return 0;
}
