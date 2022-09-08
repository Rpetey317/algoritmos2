#include "tests.h"
#include "src/cajas.h"
#include "src/pokemon.h"
#include <stdio.h>
#include <stdlib.h> 


void imprimir_pokemon(pokemon_t *pokemon)
{
	printf("=====INFO POKEMON=====\n");
	char *nombre = pokemon_nombre(pokemon);
	printf("Nombre: %s\n", nombre);
	free(nombre);
	printf("Nivel: %i\n", pokemon_nivel(pokemon));
	printf("Ataque: %i\n", pokemon_ataque(pokemon));
	printf("Defensa: %i\n", pokemon_defensa(pokemon));
	printf("=====INFO POKEMON=====\n");
}

/*
 * Crea 3 pokemones de una string y los imprime
 */ 
void prueba1()
{
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

	for (int i = 0; i < 3; i++)
		imprimir_pokemon(pokes[i]);

	for (int i = 0; i < 3; i++)
		pokemon_destruir(pokes[i]);

	free(pokes);
}

//Prueba 2: abre un csv,lo imprime, y lo copia a otro
void prueba2()
{
	caja_t* cajatest = caja_cargar_archivo("./cajatest1.csv");

	/*
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
	*/
	void (*imprimir_pokes)(pokemon_t*) = imprimir_pokemon;
	caja_recorrer(cajatest, imprimir_pokes);

	caja_guardar_archivo(cajatest, "cajatestcp.csv");

	caja_destruir(cajatest);
}

/*
 * Abre 2 archivos, los combina, y guarda el resultado en un 3ro
 */
void prueba3()
{
	caja_t *caja1 = caja_cargar_archivo("cajatest1.csv");
	caja_t *caja2 = caja_cargar_archivo("cajatest2.csv");
	caja_t *caja3 = caja_combinar(caja1, caja2);

	void (*imprimir_pokes)(pokemon_t*) = imprimir_pokemon;

	printf("\n---PRIMERA CAJA---\n");
	caja_recorrer(caja1, imprimir_pokes);
	printf("---PRIMERA CAJA---\n");
	
	printf("\n---SEGUNDA CAJA---\n");
	caja_recorrer(caja2, imprimir_pokes);
	printf("---SEGUNDA CAJA---\n");
	
	printf("\n---CAJA COMBINADA---\n");
	caja_recorrer(caja3, imprimir_pokes);
	printf("---CAJA COMBINADA---\n");

	caja_guardar_archivo(caja3, "cajacombinada.csv");

	caja_destruir(caja1);
	caja_destruir(caja2);
	caja_destruir(caja3);
}