#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#define CERO 0

typedef struct vector {
	void **array;
	size_t tope;
	size_t cantidad;
} vector_t;

/**
 * Devuelve true si el arbol no es nulo, no esta vacio y no es nulo su comparador.
 * Caso contrario, retorna false.
 */
bool abb_valido(abb_t *arbol)
{
	return arbol && !abb_vacio(arbol) && arbol->comparador;
}

/**
 * Libera la memoria reservada por el nodo.
 */
void nodo_destruir(nodo_abb_t *nodo)
{
	free(nodo);
}

/*
* Reserva e inicializa memoria para un nodo.
* Caso contrario retorna NULL.
*/
nodo_abb_t *nodo_crear(void *elemento)
{
	nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));

	if (!nodo)
		return NULL;

	nodo->elemento = elemento;
	return nodo;
}

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;

	abb_t *arbol = calloc(1, sizeof(abb_t));

	if (!arbol)
		return NULL;

	arbol->comparador = comparador;
	return arbol;
}

/*
* Recorre el árbol de forma recursiva, hasta encontrar donde insertar el elemento.
* Si se puede insertar, se retornar el nodo creado, sino la misma raiz.
*/
nodo_abb_t *abb_insertar_rec(nodo_abb_t *raiz, void *elemento,
			     abb_comparador comparador)
{
	if (!raiz)
		return nodo_crear(elemento);

	int comparacion = comparador(elemento, raiz->elemento);

	if (comparacion <= CERO) {
		raiz->izquierda =
			abb_insertar_rec(raiz->izquierda, elemento, comparador);
		if (!raiz->izquierda)
			return NULL;
	} else {
		raiz->derecha =
			abb_insertar_rec(raiz->derecha, elemento, comparador);
		if (!raiz->derecha)
			return NULL;
	}
	return raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol || !arbol->comparador)
		return NULL;

	nodo_abb_t *nueva_raiz =
		abb_insertar_rec(arbol->nodo_raiz, elemento, arbol->comparador);

	if (!nueva_raiz)
		return NULL;

	arbol->nodo_raiz = nueva_raiz;
	arbol->tamanio++;
	return arbol;
}

/**
 * Recibe la raíz izquierda del nodo a borrar, desciende por la rama derecha de forma recursiva y busca la raíz que está más a la derecha.
 * Una vez encontrada retorna esa raiz.
*/
nodo_abb_t *predecesor_inorden_rec(nodo_abb_t *raiz, void **elemento_derecho)
{
	if (!raiz->derecha) {
		*elemento_derecho = raiz->elemento;
		nodo_abb_t *izquierda = raiz->izquierda;
		nodo_destruir(raiz);
		return izquierda;
	}
	raiz->derecha = predecesor_inorden_rec(raiz->derecha, elemento_derecho);
	return raiz;
}

/**
 * Recorre el arbol de forma recursiva hasta encontrar el elemento buscado, y luego busca el predecesor inorden.
 * Si se puede eliminar el elemento, se reemplaza su raiz. Sino, no.
*/
nodo_abb_t *abb_quitar_rec(nodo_abb_t *raiz, void *elemento,
			   abb_comparador comparador, void **elemento_a_borrar,
			   bool *eliminado)
{
	if (!raiz)
		return NULL;

	nodo_abb_t *izq = raiz->izquierda;
	nodo_abb_t *der = raiz->derecha;
	int comparacion = comparador(elemento, raiz->elemento);

	if (comparacion < CERO)
		raiz->izquierda = abb_quitar_rec(izq, elemento, comparador,
						 elemento_a_borrar, eliminado);
	else if (comparacion > CERO)
		raiz->derecha = abb_quitar_rec(der, elemento, comparador,
					       elemento_a_borrar, eliminado);
	else {
		*elemento_a_borrar = raiz->elemento;
		*eliminado = true;
		if (izq && der) {
			void *elemento_derecho = NULL;
			raiz->izquierda =
				predecesor_inorden_rec(izq, &elemento_derecho);
			raiz->elemento = elemento_derecho;
		} else {
			nodo_destruir(raiz);
			return !izq ? der : izq;
		}
	}
	return raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!abb_valido(arbol))
		return NULL;

	void *elemento_a_borrar = NULL;
	bool eliminado = false;
	arbol->nodo_raiz = abb_quitar_rec(arbol->nodo_raiz, elemento,
					  arbol->comparador, &elemento_a_borrar,
					  &eliminado);
	if (eliminado)
		arbol->tamanio--;
	return elemento_a_borrar;
}

/*
* Recorre el árbol, hasta encontrar el elemento buscado.
* Si se encuentra, se retorna. Sino, se devuelve NULL.
*/
void *abb_buscar_rec(nodo_abb_t *raiz, void *elemento,
		     abb_comparador comparador)
{
	if (!raiz)
		return NULL;

	int comparacion = comparador(elemento, raiz->elemento);

	if (comparacion < CERO)
		return abb_buscar_rec(raiz->izquierda, elemento, comparador);
	else if (comparacion > CERO)
		return abb_buscar_rec(raiz->derecha, elemento, comparador);

	return raiz->elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return !abb_valido(arbol) ? NULL :
				    abb_buscar_rec(arbol->nodo_raiz, elemento,
						   arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	return !arbol || abb_tamanio(arbol) == CERO ? true : false;
}

size_t abb_tamanio(abb_t *arbol)
{
	return !arbol ? CERO : arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol, NULL);
}

/**
 * Recorre el arbol por el recorrido POSTORDEN de forma recursiva, y va liberando la memoria de los nodos.
 * Si la función destructor no es nula, se la aplica a los elementos.
 */
nodo_abb_t *abb_destruir_todo_rec(nodo_abb_t *raiz, void (*destructor)(void *))
{
	if (!raiz)
		return NULL;

	raiz->izquierda = abb_destruir_todo_rec(raiz->izquierda, destructor);
	raiz->derecha = abb_destruir_todo_rec(raiz->derecha, destructor);

	if (destructor)
		destructor(raiz->elemento);
	nodo_destruir(raiz);
	return NULL;
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;

	if (abb_vacio(arbol)) {
		free(arbol);
		return;
	}

	arbol->nodo_raiz = abb_destruir_todo_rec(arbol->nodo_raiz, destructor);

	free(arbol);
}

/**
 * Recorre el arbol por el recorrido POSTORDEN de forma recursiva y le aplica a cada elemento una función.
 * Devuelve true si se pudo recorrer y aplicar la función sin problemas, sino false.
*/
bool recorrer_por_postorden_rec(nodo_abb_t *raiz,
				bool (*funcion)(void *, void *), void *aux,
				size_t *contador)
{
	if (!raiz)
		return true;

	if (!recorrer_por_postorden_rec(raiz->izquierda, funcion, aux,
					contador))
		return false;

	if (!recorrer_por_postorden_rec(raiz->derecha, funcion, aux, contador))
		return false;

	(*contador)++;
	if (!funcion(raiz->elemento, aux))
		return false;

	return true;
}

/**
 * Recorre el arbol por el recorrido PREORDEN de forma recursiva y le aplica a cada elemento una función.
 * Devuelve true si se pudo recorrer y aplicar la función sin problemas, sino false.
*/
bool recorrer_por_preorden_rec(nodo_abb_t *raiz,
			       bool (*funcion)(void *, void *), void *aux,
			       size_t *contador)
{
	if (!raiz)
		return true;

	(*contador)++;
	if (!funcion(raiz->elemento, aux))
		return false;

	if (!recorrer_por_preorden_rec(raiz->izquierda, funcion, aux, contador))
		return false;

	if (!recorrer_por_preorden_rec(raiz->derecha, funcion, aux, contador))
		return false;

	return true;
}

/**
 * Recorre el arbol por el recorrido INORDEN de forma recursiva y le aplica a cada elemento una función.
 * Devuelve true si se pudo recorrer y aplicar la función sin problemas, sino false.
*/
bool recorrer_por_inorden_rec(nodo_abb_t *raiz, bool (*funcion)(void *, void *),
			      void *aux, size_t *contador)
{
	if (!raiz)
		return true;

	if (!recorrer_por_inorden_rec(raiz->izquierda, funcion, aux, contador))
		return false;

	(*contador)++;
	if (!funcion(raiz->elemento, aux))
		return false;

	if (!recorrer_por_inorden_rec(raiz->derecha, funcion, aux, contador))
		return false;

	return true;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!abb_valido(arbol) || !funcion)
		return 0;

	size_t i = CERO;

	if (recorrido == INORDEN)
		recorrer_por_inorden_rec(arbol->nodo_raiz, funcion, aux, &i);
	else if (recorrido == PREORDEN)
		recorrer_por_preorden_rec(arbol->nodo_raiz, funcion, aux, &i);
	else if (recorrido == POSTORDEN)
		recorrer_por_postorden_rec(arbol->nodo_raiz, funcion, aux, &i);

	return i;
}

/**
 * Rellena el vector de forma recursiva, mientras que su cantidad no supere al tope.
 * Si puede agregarse un elemento retorna true, sino false.
*/
bool rellenar_vector(void *elemento, void *aux)
{
	if (!aux)
		return false;

	vector_t *vector = aux;

	if (vector->cantidad >= vector->tope)
		return false;

	vector->array[vector->cantidad] = elemento;
	vector->cantidad++;
	return true;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!abb_valido(arbol) || !array)
		return 0;

	vector_t vector = { .array = array,
			    .tope = tamanio_array,
			    .cantidad = 0 };

	abb_con_cada_elemento(arbol, recorrido, rellenar_vector, &vector);
	return vector.cantidad;
}