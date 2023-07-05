#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

int es_elemento_buscado(void *elemento, void *buscado)
{
	if (!elemento || !buscado)
		return -1;

	if (*(char *)elemento == *(char *)buscado)
		return 0;

	return -1;
}

void insertar_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd';
	char *elemento = NULL;

	pa2m_nuevo_grupo("INSERTANDO ELEMENTO");

	lista_t *lista = lista_crear();
	lista_iterador_t *it = lista_iterador_crear(lista);

	pa2m_afirmar(!lista_insertar(NULL, &d),
		     "No se puede insertar en una lista nula");

	lista_insertar(lista, &a);
	elemento = lista_elemento_en_posicion(lista, 0);
	pa2m_afirmar(*(char *)elemento == a,
		     "Se puede agregar el elemento A al final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La cantidad de elementos es 1");

	lista_insertar(lista, &b);
	elemento = lista_elemento_en_posicion(lista, 1);
	pa2m_afirmar(*elemento == b,
		     "Se puede agregar el elemento B al final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La cantidad de elementos es 2");

	lista_insertar(lista, &c);
	elemento = lista_elemento_en_posicion(lista, 2);
	pa2m_afirmar(*elemento == c,
		     "Se puede agregar el elemento C al final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "La cantidad de elementos es 3");

	elemento = lista_primero(lista);
	pa2m_afirmar(*elemento == a, "El primer elemento es A");

	elemento = lista_ultimo(lista);
	pa2m_afirmar(*elemento == c, "El ultimo elemento es C");

	for (; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		elemento = lista_iterador_elemento_actual(it);

	pa2m_afirmar(*elemento == c,
		     "Usando el iterador, el elemento en el final es C");

	lista_iterador_destruir(it);
	lista_destruir(lista);
}

void insertar_en_pos_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("INSERTANDO ELEMENTO EN POSICION DADA");

	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_insertar_en_posicion(NULL, &e, 0),
		     "No se puede insertar en una lista nula");

	lista_insertar_en_posicion(lista, &b, 0);
	elemento = lista_elemento_en_posicion(lista, 0);
	pa2m_afirmar(*elemento == b, "Se inserta el elemento B en lista vacía");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La cantidad de elementos es 1");

	lista_insertar_en_posicion(lista, &a, 0);
	elemento = lista_elemento_en_posicion(lista, 0);
	pa2m_afirmar(*elemento == a,
		     "Se inserta el elemento A en la posicion 0");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La cantidad de elementos es 2");

	elemento = lista_primero(lista);
	pa2m_afirmar(*elemento == a, "El elemento A es el primero");

	lista_insertar_en_posicion(lista, &c, 2);
	elemento = lista_elemento_en_posicion(lista, 2);
	pa2m_afirmar(*elemento == c,
		     "Se inserta el elemento C en la posicion 2");
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "La cantidad de elementos es 3");

	elemento = lista_ultimo(lista);
	pa2m_afirmar(*elemento == c, "El elemento C es el último");

	lista_insertar_en_posicion(lista, &d, 10);
	elemento = lista_ultimo(lista);
	pa2m_afirmar(
		*elemento == d,
		"Se ingresa posicion inexistente y se inserta el elemento D en el final");
	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "La cantidad de elementos es 4");

	lista_destruir(lista);
}

void quitar_lista()
{
	char a = 'a', b = 'b', c = 'c';
	char *elemento = NULL;

	pa2m_nuevo_grupo("QUITANDO ELEMENTO");

	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_quitar(NULL),
		     "No se puede quitar elementos de una lista nula");

	pa2m_afirmar(!lista_quitar(lista),
		     "No se puede quitar elementos con lista vacía");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "La cantidad de elementos es 3");

	elemento = lista_quitar(lista);
	pa2m_afirmar(*elemento == c,
		     "Se puede quitar el elemento C del final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La cantidad de elementos es 2");

	elemento = lista_ultimo(lista);
	pa2m_afirmar(*elemento == b, "El ultimo elemento es B");

	elemento = lista_quitar(lista);
	pa2m_afirmar(*elemento == b,
		     "Se puede quitar el elemento B del final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "La cantidad de elementos es 1");

	elemento = lista_ultimo(lista);
	pa2m_afirmar(*elemento == a, "El ultimo elemento es A");

	elemento = lista_primero(lista);
	pa2m_afirmar(*elemento == a, "El primer elemento es A");

	lista_destruir(lista);
}

void quitar_en_pos_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("QUITANDO ELEMENTO EN POSICION DADA");

	lista_t *lista = lista_crear();

	elemento = lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(elemento == NULL,
		     "No se puede quitar elementos con lista vacía");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &e);

	elemento = lista_ultimo(lista);
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "La cantidad de elementos es 5");
	pa2m_afirmar(*elemento == e, "El ultimo elemento es E");
	elemento = lista_quitar_de_posicion(lista, 10);
	pa2m_afirmar(
		*elemento == e,
		"Se ingresa posicion inexistente, se quita el elemento E en la ultima posicion");
	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "La cantidad de elementos es 4");

	elemento = lista_ultimo(lista);
	pa2m_afirmar(*elemento == d, "El ultimo elemento es D");

	elemento = lista_quitar_de_posicion(lista, 2);
	pa2m_afirmar(*elemento == c,
		     "Se puede quitar el elemento C en la posicion 2");
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "La cantidad de elementos es 3");

	elemento = lista_ultimo(lista);
	pa2m_afirmar(*elemento == d, "El ultimo elemento es D");

	elemento = lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(*elemento == a,
		     "Se puede quitar el elemento A en la posicion 0");

	elemento = lista_primero(lista);
	pa2m_afirmar(*elemento == b, "El primer elemento es B");

	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "La cantidad de elementos es 2");

	lista_destruir(lista);
}

void buscar_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("BUSCANDO ELEMENTO");

	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_buscar_elemento(NULL, es_elemento_buscado, &e),
		     "No se puede buscar un elemento con una lista nula");
	pa2m_afirmar(!lista_buscar_elemento(lista, es_elemento_buscado, &e),
		     "No se puede buscar un elemento con una lista vacía");

	elemento = lista_buscar_elemento(lista, es_elemento_buscado, &a);
	pa2m_afirmar(elemento == NULL,
		     "No se puede buscar elemento en lista vacía");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);

	elemento = lista_buscar_elemento(lista, es_elemento_buscado, &a);
	pa2m_afirmar(*elemento == a, "Se encuentra el elemento A");

	elemento = lista_buscar_elemento(lista, es_elemento_buscado, &c);
	pa2m_afirmar(*elemento == c, "Se encuentra el elemento C");

	elemento = lista_buscar_elemento(lista, es_elemento_buscado, &d);
	pa2m_afirmar(*elemento == d, "Se encuentra el elemento D");

	elemento = lista_buscar_elemento(lista, es_elemento_buscado, &e);
	pa2m_afirmar(elemento == NULL,
		     "No se puede buscar un elemento inexistente");

	lista_destruir(lista);
}

void buscar_en_pos_lista()
{
	char a = 'a', b = 'b', c = 'c', d = 'd';
	char *elemento = NULL;

	pa2m_nuevo_grupo("BUSCANDO ELEMENTO EN POSICION DADA");

	lista_t *lista = lista_crear();

	elemento = lista_elemento_en_posicion(lista, 0);
	pa2m_afirmar(elemento == NULL,
		     "No se puede buscar elemento en lista vacía");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);

	elemento = lista_elemento_en_posicion(lista, 0);
	pa2m_afirmar(*elemento == a, "El elemento en la posicion 0 es A");

	elemento = lista_elemento_en_posicion(lista, 2);
	pa2m_afirmar(*elemento == c, "El elemento en la posicion 2 es C");

	elemento = lista_elemento_en_posicion(lista, 3);
	pa2m_afirmar(*elemento == d, "El elemento en la posicion 3 es D");

	elemento = lista_elemento_en_posicion(lista, 10);
	pa2m_afirmar(elemento == NULL,
		     "No se puede buscar elemento en posicion inexistente");

	lista_destruir(lista);
}

void pruebas_creacion_y_destruccion_listas()
{
	pa2m_nuevo_grupo("CREANDO");

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crear una lista");
	pa2m_afirmar(lista_vacia(lista), "La lista está vacía");
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "La cantidad de elementos es 0");
	pa2m_afirmar(lista_primero(lista) == NULL,
		     "El primer elemento de una lista vacia es nulo");
	pa2m_afirmar(lista_ultimo(lista) == NULL,
		     "El ultimo elemento de una lista vacia es nulo");

	char a = 'a', b = 'b', c = 'c', d = 'd';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);

	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(it != NULL, "Se puede crear un iterador");

	size_t i = 0;
	for (; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		i++;

	pa2m_afirmar(
		i == lista_tamanio(lista),
		"Se pudo recorrer todos los elementos, con el iterador externo");

	lista_iterador_destruir(it);
	lista_destruir(lista);

	insertar_lista();
	insertar_en_pos_lista();
	quitar_lista();
	quitar_en_pos_lista();
	buscar_lista();
	buscar_en_pos_lista();
}

void pruebas_creacion_y_destruccion_colas()
{
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("CREANDO");

	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se puede crear una cola");
	pa2m_afirmar(cola_vacia(cola), "La cola está vacía");
	pa2m_afirmar(cola_tamanio(cola) == 0, "La cantidad de elementos es 0");
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "El primer elemento de una cola vacia es nulo");

	pa2m_nuevo_grupo("ENCOLANDO");

	pa2m_afirmar(!cola_encolar(NULL, &e),
		     "No se puede encolar con una cola nula");

	cola_encolar(cola, &a);

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == a, "Se puede encolar el elemento A");
	pa2m_afirmar(cola_tamanio(cola) == 1,
		     "La cantidad de elementos en la cola es 1");
	cola_encolar(cola, &b);
	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "La cantidad de elementos en la cola es 2");
	cola_encolar(cola, &c);
	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "La cantidad de elementos en la cola es 3");
	cola_encolar(cola, &d);
	pa2m_afirmar(cola_tamanio(cola) == 4,
		     "La cantidad de elementos en la cola es 4");

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == a, "El frente de la cola es A");

	pa2m_nuevo_grupo("DESENCOLANDO");

	pa2m_afirmar(!cola_desencolar(NULL),
		     "No se puede desencolar con una cola nula");

	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(char *)elemento == a,
		     "Se puede desencolar el elemento A");
	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "La cantidad de elementos en la cola es 3");

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == b, "El nuevo frente es B");

	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(char *)elemento == b,
		     "Se puede desencolar el elemento B");
	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "La cantidad de elementos en la cola es 2");

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == c, "El nuevo frente es C");

	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(char *)elemento == c,
		     "Se puede desencolar el elemento C");
	pa2m_afirmar(cola_tamanio(cola) == 1,
		     "La cantidad de elementos en la cola es 1");

	elemento = cola_frente(cola);
	pa2m_afirmar(*(char *)elemento == d, "El nuevo frente es D");

	elemento = cola_desencolar(cola);
	pa2m_afirmar(*(char *)elemento == d,
		     "Se puede desencolar una cola de un elemento");
	pa2m_afirmar(cola_vacia(cola),
		     "La cantidad de elementos en la cola es 0");

	cola_destruir(cola);
}

void pruebas_creacion_y_destruccion_pilas()
{
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	char *elemento = NULL;

	pa2m_nuevo_grupo("CREANDO");

	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se puede crear una pila");
	pa2m_afirmar(pila_vacia(pila), "La pila está vacía");
	pa2m_afirmar(pila_tamanio(pila) == 0, "La cantidad de elementos es 0");
	pa2m_afirmar(pila_tope(pila) == NULL,
		     "El primer elemento de una pila vacia es nulo");

	pa2m_nuevo_grupo("APILANDO");

	pa2m_afirmar(!pila_apilar(NULL, &e),
		     "No se puede apilar con una pila nula");

	pila_apilar(pila, &a);
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == a, "El tope de la pila es A");
	pa2m_afirmar(pila_tamanio(pila) == 1, "La cantidad de elementos es 1");

	pila_apilar(pila, &b);
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == b, "El tope de la pila es B");
	pa2m_afirmar(pila_tamanio(pila) == 2, "La cantidad de elementos es 2");

	pila_apilar(pila, &c);
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == c, "El tope de la pila es C");
	pa2m_afirmar(pila_tamanio(pila) == 3, "La cantidad de elementos es 3");

	pila_apilar(pila, &d);
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == d, "El tope de la pila es D");
	pa2m_afirmar(pila_tamanio(pila) == 4, "La cantidad de elementos es 4");

	pa2m_nuevo_grupo("DESAPILANDO");

	pa2m_afirmar(!pila_desapilar(NULL),
		     "No se puede desapilar con una pila nula");

	elemento = pila_desapilar(pila);
	pa2m_afirmar(*(char *)elemento == d,
		     "Se puede desapilar el elemento D");
	pa2m_afirmar(pila_tamanio(pila) == 3, "La cantidad de elementos es 3");
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == c, "El nuevo tope es c");

	elemento = pila_desapilar(pila);
	pa2m_afirmar(*(char *)elemento == c,
		     "Se puede desapilar el elemento C");
	pa2m_afirmar(pila_tamanio(pila) == 2, "La cantidad de elementos es 2");
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == b, "El nuevo tope es B");

	elemento = pila_desapilar(pila);
	pa2m_afirmar(*(char *)elemento == b,
		     "Se puede desapilar el elemento b");
	pa2m_afirmar(pila_tamanio(pila) == 1, "La cantidad de elementos es 1");
	elemento = pila_tope(pila);
	pa2m_afirmar(*(char *)elemento == a, "El nuevo tope es a");

	elemento = pila_desapilar(pila);
	pa2m_afirmar(*(char *)elemento == a,
		     "Se puede desapilar el elemento A");
	pa2m_afirmar(pila_vacia(pila), "La cantidad de elementos es 0");
	elemento = pila_tope(pila);
	pa2m_afirmar(!elemento, "No se puede desapilar con una pila vacía");

	pila_destruir(pila);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS DEL TDA - LISTAS ========================");

	pa2m_nuevo_grupo(
		"======================== LISTAS ========================");
	pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN Y DESTRUCCIÓN");
	pruebas_creacion_y_destruccion_listas();
	pa2m_nuevo_grupo(
		"========================================================");

	pa2m_nuevo_grupo(
		"======================== COLAS ========================");
	pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN Y DESTRUCCIÓN");
	pruebas_creacion_y_destruccion_colas();
	pa2m_nuevo_grupo(
		"=======================================================");

	pa2m_nuevo_grupo(
		"======================== PILAS ========================");
	pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN Y DESTRUCCIÓN");
	pruebas_creacion_y_destruccion_pilas();
	pa2m_nuevo_grupo(
		"=======================================================");

	return pa2m_mostrar_reporte();
	return 0;
}