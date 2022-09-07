#include "tests.h"
#include "src/cajas.h"
#include "src/pokemon.h"
#include <stdio.h>
#include <stdlib.h> 

void prueba1(){
    //test 1: pokemon.c
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