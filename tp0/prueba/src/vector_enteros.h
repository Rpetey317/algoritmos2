#ifndef VECTOR_ENTEROS_H_
#define VECTOR_ENTEROS_H_

struct vector_enteros {
	int *enteros;
	int cantidad;
};

/*
 * Crea un vector de enteros vacío (0 elementos).
 *
 * Devuelve NULL en caso de error.
 */
struct vector_enteros *vector_enteros_crear();

/*
 * Agrega un nuevo elemento al vector.
 *
 * Devuelve NULL si hubo error o el vector original si la operacion fue exitosa.
 */
struct vector_enteros *
vector_enteros_agregar_elemento(struct vector_enteros *vector, int nuevo);

/*
 * Devuelve el entero en la posicion dada del vector o 0 en caso de error.
 */
int vector_enteros_obtener_elemento(struct vector_enteros *vector,
				    int posicion);

/*
 * Modifica el valor del entero en la posicion dada.
 *
 * Devuelve el nuevo valor del entero o 0 en caso de error.
 */
int vector_enteros_modificar_elemento(struct vector_enteros *vector,
				      int posicion, int nuevo_valor);

/*
 * Devuelve la cantidad de enteros almacenados en el vector o 0 en caso de error.
 */
int vector_enteros_tamaño(struct vector_enteros *vector);

/*
 * Destruye un vector de enteros
 */
void vector_enteros_destruir(struct vector_enteros *vector);

#endif // VECTOR_ENTEROS_H_
