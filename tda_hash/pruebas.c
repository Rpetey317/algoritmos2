#include "src/hash.h"
#include "pa2m.h"

void crearHash()
{
	hash_t *hash = hash_crear(0);
	pa2m_afirmar(hash != NULL, "Puedo crear un hash");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El nuevo hash se crea vacío");
	pa2m_afirmar(
		hash_capacidad(hash) == CAPACIDAD_MIN,
		"Intentear crear un hash con capacidad debajo de la mínima crea uno con la capacidad mínima");

	hash_t *hash2 = hash_crear(10);
	pa2m_afirmar(hash_capacidad(hash2) == 10,
		     "Puedo crear un hash con capacidad 10");

	hash_t *hash3 = hash_crear(1000);
	pa2m_afirmar(hash_capacidad(hash3) == 1000,
		     "Puedo crear un hash con capacidad 1000");

	hash_t *hash4 = hash_crear(123456);
	pa2m_afirmar(hash_capacidad(hash4) == 123456,
		     "Puedo crear un hash con capacidad 123,456");

	const char *clave = "hola";
	int valor = 3;
	hash_insertar(hash, clave, (void *)&valor, NULL);
	hash_insertar(hash2, clave, (void *)&valor, NULL);
	pa2m_afirmar(hash_contiene(hash, clave),
		     "Puedo insertar un elemento en el hash");
	hash_quitar(hash, clave);
	pa2m_afirmar(!hash_contiene(hash, clave),
		     "Puedo quitar un elemento del hash");

	hash_destruir(hash);
	hash_destruir(hash2);
	hash_destruir(hash3);
	hash_destruir(hash4);

	pa2m_afirmar(
		true,
		"Puedo destruir hashes existentes, con y sin elementos (no debería haber errores de memoria");
}

void insercionesHash()
{
	const char *c0 = "Cero", *c1 = "Uno", *c2 = "Dos", *c3 = "Tres",
		   *c4 = "Cuatro", *c5 = "Cinco", *c6 = "Seis", *c7 = "Siete",
		   *c8 = "Ocho", *c9 = "Nueve", *c10 = "Diez", *c11 = "Once",
		   *c12 = "Doce", *c13 = "Trece", *c14 = "Catorce",
		   *c15 = "Quince";

	const char *claves[] = { c0, c1, c2,  c3,  c4,	c5,  c6,  c7,
				 c8, c9, c10, c11, c12, c13, c14, c15 };
	int numeros[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	hash_t *hash = hash_crear(12);

	hash_t *retv =
		hash_insertar(hash, claves[0], (void *)&numeros[0], NULL);
	pa2m_afirmar(retv != NULL, "Puedo insertar un elemento al hash");
	pa2m_afirmar(hash_contiene(hash, claves[0]),
		     "El elemento recién insertado está en el hash");
	pa2m_afirmar(
		hash_obtener(hash, claves[0]) == &numeros[0],
		"Busco y encuentro el elemento recién insertado en el hash");

	hash_insertar(hash, claves[1], (void *)&numeros[1], NULL);
	hash_insertar(hash, claves[2], (void *)&numeros[2], NULL);
	hash_insertar(hash, claves[3], (void *)&numeros[3], NULL);
	hash_insertar(hash, claves[4], (void *)&numeros[4], NULL);

	bool flag = true;
	for (int i = 0; i < 5; i++) {
		flag = flag && hash_contiene(hash, claves[i]);
	}
	pa2m_afirmar(flag, "Inserto 5 elementos al hash, todos están");

	flag = !hash_contiene(hash, claves[5]);
	pa2m_afirmar(flag, "Busco un elemento que no está y no lo encuentro");
	hash_insertar(hash, claves[5], (void *)&numeros[5], NULL);
	flag = flag && hash_contiene(hash, claves[5]);
	pa2m_afirmar(
		flag,
		"Inserto un elemento que antes no estaba, ahora lo encuentro");

	hash_destruir(hash);

	//====================SEPARADOR====================//

	hash = hash_crear(12);

	for (size_t i = 0; i < 16; i++) {
		hash_insertar(hash, claves[i], &numeros[i], NULL);
	}
	flag = true;
	for (int i = 0; i < 16; i++) {
		flag = flag && hash_contiene(hash, claves[i]);
	}
	pa2m_afirmar(hash_cantidad(hash) == 16,
		     "Puedo insertar más elementos que la capacidad inicial");
	pa2m_afirmar(flag, "Encuentro todos los elementos insertados");

	int cien = 100;
	void *anterior = NULL;
	hash_insertar(hash, claves[0], &cien, &anterior);
	pa2m_afirmar(
		hash_obtener(hash, claves[0]) == &cien,
		"Inserto un elemento con una clave duplicada, cambia el valor almacenado");
	pa2m_afirmar(
		anterior == &numeros[0],
		"Al insertar un elemento duplicado me devuelven lo que tenía almacenado antes en esa clave");

	hash_destruir(hash);
}

void quitarHash()
{
	const char *claves[] = { "Cero",   "Uno",   "Dos",     "Tres",
				 "Cuatro", "Cinco", "Seis",    "Siete",
				 "Ocho",   "Nueve", "Diez",    "Once",
				 "Doce",   "Trece", "Catorce", "Quince" };

	int numeros[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	hash_t *hash = hash_crear(24);

	for (size_t i = 0; i < 16; i++) {
		hash_insertar(hash, claves[i], &numeros[i], NULL);
	}
	void *aux = NULL;
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de hash");
	crearHash();

	pa2m_nuevo_grupo("Pruebas de insertar elementos");
	insercionesHash();

	pa2m_nuevo_grupo("Pruebas de eliminar elementos");
	quitarHash();

	return pa2m_mostrar_reporte();
}
