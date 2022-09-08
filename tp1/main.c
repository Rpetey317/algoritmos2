#include "src/cajas.h"
#include "src/pokemon.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	//Prueba 2: abrir un csv e imprimirlo
	caja_t* cajatest = caja_cargar_archivo("./caja1.csv");

	for (int i = 0; i < caja_cantidad(cajatest); i++){
		int lvl, atk, def;
		lvl = pokemon_nivel(caja_obtener_pokemon(cajatest, i));
		atk = pokemon_ataque(caja_obtener_pokemon(cajatest, i));
		def = pokemon_defensa(caja_obtener_pokemon(cajatest, i));

		printf("---Pokemon #%i---\n", i);
		
		char *nombre = pokemon_nombre(caja_obtener_pokemon(cajatest, i));
		printf("Nombre: %s\n", nombre);
		free(nombre);

		printf("Nivel: %i\n", lvl);
		printf("Ataque: %i\n", atk);
		printf("Defensa: %i\n", def);
		printf("---Pokemon #%i---\n\n", i);
	}

	caja_destruir(cajatest);

	return 0;
}
