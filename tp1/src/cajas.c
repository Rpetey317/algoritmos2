#include "cajas.h"
#include "pokemon.h"
#include <stdlib.h>

struct _caja_t {
	//definir la estructura de la caja
};

caja_t *caja_cargar_archivo(const char *nombre_archivo)
{
	return NULL;
}

int caja_guardar_archivo(caja_t *caja, const char *nombre_archivo)
{
	return 0;
}

caja_t *caja_combinar(caja_t *caja1, caja_t *caja2)
{
	return NULL;
}

int caja_cantidad(caja_t *caja)
{
	return 0;
}

pokemon_t *caja_obtener_pokemon(caja_t *caja, int n)
{
	return NULL;
}

int caja_recorrer(caja_t *caja, void (*funcion)(pokemon_t *))
{
	return 0;
}

void caja_destruir(caja_t *caja)
{
}
