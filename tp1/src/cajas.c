#include "cajas.h"
#include "pokemon.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_STRING_POKEMON 64 //str de 30 char max + 5 ints (10max c/u) + ;;;

struct _caja_t {
	pokemon_t **pokemones;
	int cantidad;
};

// |||FUNCIONES PRIVADAS|||

/*
 * Añade un pokemon al final de una caja.
 * Devuelve TRUE se se pudo agregar el pokemon, FALSE en caso contrario.
 */
bool caja_agregar_pokemon(caja_t *caja, pokemon_t *pokemon)
{
	if (caja == NULL || pokemon == NULL || caja->pokemones == NULL)
		return false;

	pokemon_t **temp = realloc(caja->pokemones, sizeof(pokemon_t*)*((size_t)(caja->cantidad + 1)));
	if (temp == NULL)
		return false;
	else
		caja->pokemones = temp;

	char pokecopia[MAX_STRING_POKEMON];
	
	strcpy(pokecopia, pokemon_nombre(pokemon));
	strcat(pokecopia, ";");

	char *aux = malloc(sizeof(char)*10);

	sprintf(aux, "%i", pokemon_nivel(pokemon));
	strcat(pokecopia, aux);
	strcat(pokecopia, ";");

	sprintf(aux, "%i", pokemon_ataque(pokemon));
	strcat(pokecopia, aux);
	strcat(pokecopia, ";");
	
	sprintf(aux, "%i", pokemon_defensa(pokemon));
	strcat(pokecopia, aux);
	strcat(pokecopia, "\n");

	free(aux);

	caja->pokemones[caja->cantidad] = pokemon_crear_desde_string(pokecopia);
	caja->cantidad++;
	return true;
}

/*
 * Ordena los pokemones de la caja en orden alfabético
 * No ordena según otro critero pokemones con el mismo nombre
 */
void caja_ordenar_alfabeticamente(caja_t *caja)
{
	if (caja == NULL)
		return;
	for (int i = 0; i < caja->cantidad - 1; i++){
		for (int j = 0; j < caja->cantidad - i - 1; j++){
			if (strcmp(pokemon_nombre(caja->pokemones[j]), pokemon_nombre(caja->pokemones[j+1])) >= 0){
				pokemon_t *aux = caja->pokemones[j];
				caja->pokemones[j] = caja->pokemones[j+1];
				caja->pokemones[j+1] = aux;
			}
		}
	}
}

// |||FUNCIONES PUBLICAS|||

caja_t *caja_cargar_archivo(const char *nombre_archivo)
{
	if (nombre_archivo == NULL)
		return NULL;

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL)
		return NULL;

	caja_t *caja = malloc(sizeof(caja_t));
	if (caja == NULL)
		return NULL;

	caja->cantidad = 0;
	caja->pokemones = malloc(sizeof(pokemon_t*));
	if (caja->pokemones == NULL)
		return NULL;

	while (!feof(archivo)){
		char pokemon[MAX_STRING_POKEMON];
		int scan = fscanf(archivo, "%[^\n]\n", pokemon);
		if (scan != 1)
			return NULL;

		pokemon_t **temp = realloc(caja->pokemones, sizeof(pokemon_t*)*((size_t)(caja->cantidad + 1)));
		if (temp == NULL)
			return NULL;
		else
			caja->pokemones = temp;

		caja->pokemones[caja->cantidad] = pokemon_crear_desde_string(pokemon);
		caja->cantidad++;
	}
	
	fclose(archivo);
	caja_ordenar_alfabeticamente(caja);
	return caja;
}

int caja_guardar_archivo(caja_t *caja, const char *nombre_archivo)
{
	if (caja == NULL || nombre_archivo == NULL)
		return 0;
	
	FILE *archivo = fopen(nombre_archivo, "w");
	if (archivo == NULL)
		return 0;

	int counter = 0;
	for (int i = 0; i < caja->cantidad; i++){
		int lvl, atk, def;
		lvl = pokemon_nivel(caja->pokemones[i]);
		atk = pokemon_ataque(caja->pokemones[i]);
		def = pokemon_defensa(caja->pokemones[i]);
		
		if (fprintf(archivo, "%s;%i;%i;%i\n", pokemon_nombre(caja->pokemones[i]), lvl, atk, def) > 0)
			counter++;
	}
	
	fclose(archivo);

	return counter;
}

caja_t *caja_combinar(caja_t *caja1, caja_t *caja2)
{
	if (caja1 == NULL || caja2 == NULL || caja1->pokemones == NULL || caja2->pokemones == NULL)
		return NULL;

	caja_t *caja3 = malloc(sizeof(caja_t));
	caja3->pokemones = malloc(sizeof(pokemon_t*));
	caja3->cantidad = 0;

	int i = 0;
	bool exito = true;
	while (i < caja1->cantidad && exito){
		exito = caja_agregar_pokemon(caja3, caja1->pokemones[i]);
		i++;
	}

	i = 0;
	exito = true;
	while (i < caja2->cantidad && exito){
		exito = caja_agregar_pokemon(caja3, caja2->pokemones[i]);
		i++;
	}

	caja_ordenar_alfabeticamente(caja3);
	return caja3;
}

int caja_cantidad(caja_t *caja)
{
	int pokes = 0;
	if (caja != NULL)
		pokes = caja->cantidad;
	if (pokes < 0)
		pokes = 0;
	
	return pokes;
}

pokemon_t *caja_obtener_pokemon(caja_t *caja, int n)
{
	if (caja == NULL || n < 0 || n >= caja->cantidad)
		return NULL;
	else
		return caja->pokemones[n];
}

int caja_recorrer(caja_t *caja, void (*funcion)(pokemon_t *))
{
	if (caja == NULL || funcion == NULL || caja->pokemones == NULL)
		return 0;
	
	int contador = 0;
	for (int i = 0; i < caja->cantidad; i++){
		if (caja->pokemones[i] != NULL){
			funcion(caja->pokemones[i]);
			contador++;
		}
	}
	return contador;
}

void caja_destruir(caja_t *caja)
{
	if (caja != NULL){
		for (int i = 0; i < caja->cantidad; i++)
			free(caja->pokemones[i]);
		free(caja->pokemones);
		free(caja);
	}
}
