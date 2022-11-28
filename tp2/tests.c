#include "tests.h"
#include "src/cajas.h"
#include "src/pokemon.h"
#include <stdio.h>
#include <stdlib.h>

// Privadas
void imprimir_pokemon(pokemon_t *pokemon)
{
	printf("=====INFO POKEMON=====\n");
	printf("Nombre: %s\n", pokemon_nombre(pokemon));
	printf("Nivel: %i\n", pokemon_nivel(pokemon));
	printf("Ataque: %i\n", pokemon_ataque(pokemon));
	printf("Defensa: %i\n", pokemon_defensa(pokemon));
	printf("=====INFO POKEMON=====\n");
}

// Publicas
void prueba1()
{
	char *str_pikachu = "Pikachu;10;15;10";
	char *str_charmander = "Charmander;6;20;5";
	char *str_eevee = "Eevee;12;15;7";

	pokemon_t *pikachu = pokemon_crear_desde_string(str_pikachu);
	pokemon_t *charmander = pokemon_crear_desde_string(str_charmander);
	pokemon_t *eevee = pokemon_crear_desde_string(str_eevee);

	pokemon_t **pokes = malloc(sizeof(pokemon_t *) * 3);

	pokes[0] = pikachu;
	pokes[1] = charmander;
	pokes[2] = eevee;

	for (int i = 0; i < 3; i++)
		imprimir_pokemon(pokes[i]);

	for (int i = 0; i < 3; i++)
		pokemon_destruir(pokes[i]);

	free(pokes);
}

void prueba2()
{
	caja_t *cajatest = caja_cargar_archivo("./cajatest1.csv");

	void (*imprimir_pokes)(pokemon_t *) = imprimir_pokemon;
	caja_recorrer(cajatest, imprimir_pokes);

	int guardados = caja_guardar_archivo(cajatest, "cajacopy.csv");
	printf("\nPokemones guardados en la caja copiada: %i\n", guardados);

	caja_destruir(cajatest);
}

void prueba3()
{
	caja_t *caja1 = caja_cargar_archivo("cajatest1.csv");
	caja_t *caja2 = caja_cargar_archivo("cajatest2.csv");
	caja_t *caja3 = caja_combinar(caja1, caja2);

	void (*imprimir_pokes)(pokemon_t *) = imprimir_pokemon;

	printf("\n---PRIMERA CAJA---\n");
	caja_recorrer(caja1, imprimir_pokes);
	printf("---PRIMERA CAJA---\n");

	printf("\n---SEGUNDA CAJA---\n");
	caja_recorrer(caja2, imprimir_pokes);
	printf("---SEGUNDA CAJA---\n");

	printf("\n---CAJA COMBINADA---\n");
	caja_recorrer(caja3, imprimir_pokes);
	printf("---CAJA COMBINADA---\n");

	int guardados = caja_guardar_archivo(caja3, "cajacombinada.csv");
	printf("\nPokemones guardados en la 3° caja: %i\n", guardados);

	caja_destruir(caja1);
	caja_destruir(caja2);
	caja_destruir(caja3);
}