#include "tests.h"
#include "src/cajas.h"
#include "src/pokemon.h"
#include <stdio.h>
#include <stdlib.h> 

//prueba 1: funciones de pokemon.c
void prueba1(){
	char *str_pikachu = "Pikachu;10;15;10";
	char *str_charmander = "Charmander;6;20;5";
	char *str_eevee = "Eevee;12;15;7";

	pokemon_t *pikachu = pokemon_crear_desde_string(str_pikachu);
	pokemon_t *charmander = pokemon_crear_desde_string(str_charmander);
	pokemon_t *eevee = pokemon_crear_desde_string(str_eevee);

	pokemon_t **pokes = malloc(sizeof(pokemon_t*)*3);

	pokes[0] = pikachu;
	pokes[1] = charmander;
	pokes[2] = eevee;

	for (int i = 0; i < 3; i++){
		printf("---Pokemon #%i---\n", i);
		/*
		*/
		char *nombre = pokemon_nombre(pokes[i]);
		printf("Nombre: %s\n", nombre);
		free(nombre);
		//printf("Nombre: %s\n", pokemon_nombre(pokes[i]));
		printf("Nivel: %i\n", pokemon_nivel(pokes[i]));
		printf("Ataque: %i\n", pokemon_ataque(pokes[i]));
		printf("Defensa: %i\n", pokemon_defensa(pokes[i]));
		printf("---Pokemon #%i---\n\n", i);
	}

	for (int i = 0; i < 3; i++)
		pokemon_destruir(pokes[i]);

	free(pokes);
}

//Prueba 2: abrir un csv, imprimirlo, y copiarlo a otro
void prueba2(){
	caja_t* cajatest = caja_cargar_archivo("./cajatest.csv");

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

	caja_guardar_archivo(cajatest, "cajatestcp.csv");

	caja_destruir(cajatest);
}