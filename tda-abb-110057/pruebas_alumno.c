#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

bool contar(void *_el1, void *aux)
{
	if (_el1) {
		(*(int *)aux)++;
		return true;
	}
	return false;
}

int comparador(void *_el1, void *_el2)
{
	return *(int *)_el1 - *(int *)_el2;
}

void pruebas_crear_abb()
{
	pa2m_nuevo_grupo("Creando árbol");

	abb_t *abb = abb_crear(comparador);
	pa2m_afirmar(abb != NULL,
		     "Se puede crear un abb con un comparador no NULL");
	pa2m_afirmar(abb_vacio(abb), "El abb está vacío");
	pa2m_afirmar(abb_tamanio(abb) == 0, "La cantidad de elementos es 0");
	pa2m_afirmar(!abb->nodo_raiz, "El elemento raíz es NULL");

	abb_destruir(abb);
}

void insertar_elementos_validos_no_es_error()
{
	pa2m_nuevo_grupo("Insertar elementos");

	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5;
	abb_t *abb = abb_crear(comparador);

	abb = abb_insertar(abb, &cuatro);
	pa2m_afirmar(abb_tamanio(abb) == 1,
		     "Se inserta un elemento y la cantidad de elementos es 1");

	pa2m_afirmar(abb->nodo_raiz != NULL, "El elemento raíz no es NULL");

	abb = abb_insertar(abb, &dos);
	pa2m_afirmar(abb_tamanio(abb) == 2,
		     "Se inserta un elemento y la cantidad de elementos es 2");

	pa2m_afirmar(abb->nodo_raiz->izquierda != NULL,
		     "El elemento raíz izquierda no es NULL");

	abb = abb_insertar(abb, &tres);
	pa2m_afirmar(abb_tamanio(abb) == 3,
		     "Se inserta un elemento y la cantidad de elementos es 3");

	abb = abb_insertar(abb, &uno);
	pa2m_afirmar(abb_tamanio(abb) == 4,
		     "Se inserta un elemento y la cantidad de elementos es 4");

	abb = abb_insertar(abb, &uno);
	pa2m_afirmar(abb_tamanio(abb) == 5,
		     "Se inserta un elemento y la cantidad de elementos es 5");

	abb = abb_insertar(abb, &cinco);
	pa2m_afirmar(abb_tamanio(abb) == 6,
		     "Se inserta un elemento y la cantidad de elementos es 6");
	pa2m_afirmar(abb->nodo_raiz->derecha != NULL,
		     "El elemento raíz derecha no es NULL");

	abb_destruir(abb);
}

void pruebas_insertar_elemento_abb()
{
	insertar_elementos_validos_no_es_error();
}

void buscar_elemento_existente_no_es_error()
{
	pa2m_nuevo_grupo("Buscar elemento existente");

	int uno = 1, tres = 3, cuatro = 4;
	abb_t *abb = abb_crear(comparador);

	abb = abb_insertar(abb, &cuatro);
	abb = abb_insertar(abb, &tres);
	abb = abb_insertar(abb, &tres);
	abb = abb_insertar(abb, &uno);

	pa2m_afirmar(*(int *)abb_buscar(abb, &tres) == tres,
		     "Se busca el elemento 3 y se encuentra");
	pa2m_afirmar(*(int *)abb_buscar(abb, &cuatro) == cuatro,
		     "Se busca el elemento 4 y se encuentra");

	abb_destruir(abb);
}

void buscar_elemento_inexistente_es_error()
{
	pa2m_nuevo_grupo("Buscar elemento inexistente");

	int cuatro = 4, cinco = 5, seis = 6;
	abb_t *abb = abb_crear(comparador);
	abb = abb_insertar(abb, &cuatro);

	pa2m_afirmar(!abb_buscar(abb, &cinco),
		     "No se encuentra el elemento 5 y se devuelve NULL");
	pa2m_afirmar(!abb_buscar(abb, &seis),
		     "No se encuentra el elemento 6 y se devuelve NULL");

	abb_destruir(abb);
}

void pruebas_buscar_elemento_abb()
{
	buscar_elemento_existente_no_es_error();
	buscar_elemento_inexistente_es_error();
}

void quitar_elemento_existente_no_es_error()
{
	pa2m_nuevo_grupo("Quitar elemento existente");

	int uno = 1, tres = 3, cuatro = 4, cinco = 5, seis = 6, ocho = 8,
	    nueve = 9;
	abb_t *abb = abb_crear(comparador);

	abb = abb_insertar(abb, &seis);
	abb = abb_insertar(abb, &ocho);
	abb = abb_insertar(abb, &tres);
	abb = abb_insertar(abb, &cuatro);
	abb = abb_insertar(abb, &uno);
	abb = abb_insertar(abb, &nueve);
	abb = abb_insertar(abb, &cinco);

	pa2m_afirmar(abb_tamanio(abb) == 7, "La cantidad de elementos es 7");

	pa2m_afirmar(*(int *)abb_quitar(abb, &nueve) == nueve,
		     "Se elimina el elemento 9");
	pa2m_afirmar(abb_tamanio(abb) == 6, "La cantidad de elementos es 6");

	pa2m_afirmar(*(int *)abb_quitar(abb, &uno) == uno,
		     "Se elimina el elemento 1");
	pa2m_afirmar(abb_tamanio(abb) == 5, "La cantidad de elementos es 5");

	pa2m_afirmar(*(int *)abb_quitar(abb, &seis) == seis,
		     "Se elimina el primer elemento, el 6");
	pa2m_afirmar(
		*(int *)abb->nodo_raiz->elemento == cinco,
		"El predecesor inorden es 5, y pasa a ser el primer elemento");
	pa2m_afirmar(abb_tamanio(abb) == 4, "La cantidad de elementos es 4");

	pa2m_afirmar(*(int *)abb_quitar(abb, &ocho) == ocho,
		     "Se elimina el elemento 8");
	pa2m_afirmar(abb_tamanio(abb) == 3, "La cantidad de elementos es 3");

	pa2m_afirmar(*(int *)abb_quitar(abb, &tres) == tres,
		     "Se elimina el elemento 3");
	pa2m_afirmar(abb_tamanio(abb) == 2, "La cantidad de elementos es 2");

	pa2m_afirmar(*(int *)abb_quitar(abb, &cuatro) == cuatro,
		     "Se elimina el elemento 4");
	pa2m_afirmar(abb_tamanio(abb) == 1, "La cantidad de elementos es 1");

	abb_destruir(abb);
}

void quitar_elemento_repetido_elimina_el_primero_encontrado()
{
	pa2m_nuevo_grupo("Quitar elemento repetido");

	int ocho = 8, nueve = 9, diez = 10;
	abb_t *abb = abb_crear(comparador);

	abb = abb_insertar(abb, &ocho);
	abb = abb_insertar(abb, &nueve);
	abb = abb_insertar(abb, &diez);
	abb = abb_insertar(abb, &ocho);

	pa2m_afirmar(abb_tamanio(abb) == 4, "La cantidad de elementos es 4");

	pa2m_afirmar(
		*(int *)abb_quitar(abb, &ocho) == ocho,
		"Se elimina el elemento 8 que está repetido. Se elimina el primero encontrado");
	pa2m_afirmar(abb_tamanio(abb) == 3, "La cantidad de elementos es 3");

	abb_destruir(abb);
}

void quitar_elemento_inexistente_es_error()
{
	pa2m_nuevo_grupo("Quitar elemento inexistente");

	int seis = 6, siete = 7, diez = 10;
	abb_t *abb = abb_crear(comparador);
	abb = abb_insertar(abb, &seis);
	pa2m_afirmar(
		!abb_quitar(abb, &siete),
		"Se intenta sacar el elemento 7 y no se encuentra. Se devuelve NULL");
	pa2m_afirmar(
		abb_tamanio(abb) == 1,
		"No se modifica la cantidad. La cantidad de elementos es 1");
	pa2m_afirmar(
		!abb_quitar(abb, &diez),
		"Se intenta sacar el elemento 10 y no se encuentra. Se devuelve NULL");
	pa2m_afirmar(
		abb_tamanio(abb) == 1,
		"No se modifica la cantidad. La cantidad de elementos es 1");

	abb_destruir(abb);
}

void quitar_ultimo_elemento_no_es_error()
{
	pa2m_nuevo_grupo("Quitar ultimo elemento");

	int seis = 6;
	abb_t *abb = abb_crear(comparador);
	abb = abb_insertar(abb, &seis);

	pa2m_afirmar(*(int *)abb_quitar(abb, &seis) == seis,
		     "Se elimina el último elemento, el 6");
	pa2m_afirmar(abb_vacio(abb), "El árbol esta vació");
	pa2m_afirmar(abb_tamanio(abb) == 0, "La cantidad de elementos es 0");

	abb_destruir(abb);
}

void pruebas_quitar_elemento_abb()
{
	quitar_elemento_existente_no_es_error();
	quitar_elemento_repetido_elimina_el_primero_encontrado();
	quitar_elemento_inexistente_es_error();
	quitar_ultimo_elemento_no_es_error();
}

void arbol_null_es_error()
{
	pa2m_nuevo_grupo("Árbol nulo");

	int uno = 1;
	abb_t *abb = abb_crear(NULL);
	void *vector = malloc(1 * sizeof(int *));

	pa2m_afirmar(!abb, "No se puede crear un abb con un comparador nulo");
	pa2m_afirmar(!abb_insertar(abb, &uno),
		     "No se puede insertar un elemento con un árbol nulo");
	pa2m_afirmar(!abb_buscar(abb, &uno),
		     "No se puede buscar un elemento con un árbol nulo");
	pa2m_afirmar(!abb_quitar(abb, &uno),
		     "No se puede eliminar un elemento con un árbol nulo");
	pa2m_afirmar(abb_con_cada_elemento(abb, INORDEN, contar, NULL) == 0,
		     "No se puede recorrer el árbol con un árbol nulo");
	pa2m_afirmar(
		abb_recorrer(abb, INORDEN, vector, 1) == 0,
		"No se puede insertar elementos en el vector, con un árbol nulo");

	free(vector);
}

void arbol_se_crea_bien_pero_despues_se_le_asigna_comparador_null_es_error()
{
	pa2m_nuevo_grupo("Comparador nulo");

	int uno = 1;
	void *vector = malloc(1 * sizeof(int *));
	abb_t *abb = abb_crear(comparador);
	abb->comparador = NULL;

	pa2m_afirmar(!abb_insertar(abb, &uno),
		     "No se puede insertar un elemento con un comparador nulo");
	pa2m_afirmar(!abb_buscar(abb, &uno),
		     "No se puede buscar un elemento con un comparador nulo");
	pa2m_afirmar(!abb_quitar(abb, &uno),
		     "No se puede quitar un elemento con un comparador nulo");

	free(vector);
	abb_destruir(abb);
}

void recorrer_arbol_con_parametros_nulos_es_error()
{
	pa2m_nuevo_grupo("Parámetros nulos con cada elemento");

	abb_t *abb = abb_crear(comparador);
	void *vector = malloc(1 * sizeof(int *));

	pa2m_afirmar(abb_con_cada_elemento(abb, INORDEN, NULL, NULL) == 0,
		     "No se puede recorrer el árbol con una función bool nula");
	pa2m_afirmar(abb_con_cada_elemento(abb, 0, contar, NULL) == 0,
		     "No se puede recorrer el árbol con un recorrido erróneo");
	pa2m_afirmar(
		abb_recorrer(abb, INORDEN, NULL, 1) == 0,
		"No se puede insertar elementos en el vector, con un vector nulo");
	pa2m_afirmar(
		abb_recorrer(abb, 0, vector, 1) == 0,
		"No se puede insertar elementos en el vector, con un recorrido erróneo");

	free(vector);
	abb_destruir(abb);
}

void pruebas_con_null_abb()
{
	arbol_null_es_error();
	arbol_se_crea_bien_pero_despues_se_le_asigna_comparador_null_es_error();
	recorrer_arbol_con_parametros_nulos_es_error();
}

void recorrer_el_arbol_con_recorrido_valido_no_es_error()
{
	pa2m_nuevo_grupo("Recorrer el árbol");

	int contador = 0;
	int uno = 1, tres = 3, cuatro = 4, cinco = 5;
	abb_t *abb = abb_crear(comparador);
	abb = abb_insertar(abb, &cuatro);
	abb = abb_insertar(abb, &tres);
	abb = abb_insertar(abb, &uno);
	abb = abb_insertar(abb, &tres);
	abb = abb_insertar(abb, &cinco);

	pa2m_afirmar(abb_con_cada_elemento(abb, INORDEN, contar, &contador) ==
			     5,
		     "Se puede recorrer el árbol por INORDEN");
	pa2m_afirmar(contador == 5,
		     "Se contó la cantidad correcta de elementos");
	contador = 0;
	pa2m_afirmar(abb_con_cada_elemento(abb, PREORDEN, contar, &contador) ==
			     5,
		     "Se puede recorrer el árbol por PREORDEN");
	pa2m_afirmar(contador == 5,
		     "Se contó la cantidad correcta de elementos");
	contador = 0;
	pa2m_afirmar(abb_con_cada_elemento(abb, POSTORDEN, contar, &contador) ==
			     5,
		     "Se puede recorrer el árbol por POSTORDEN");
	pa2m_afirmar(contador == 5,
		     "Se contó la cantidad correcta de elementos");

	abb_destruir(abb);
}

void pruebas_iterador_abb()
{
	recorrer_el_arbol_con_recorrido_valido_no_es_error();
}

void vector_recorrido_por_preorden()
{
	pa2m_nuevo_grupo("Rellenar vector por PREORDEN");

	size_t tamanio = 7;
	void **vector = malloc(tamanio * sizeof(int *));
	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6,
	    siete = 7;

	abb_t *abb = abb_crear(comparador);
	abb_insertar(abb, &cuatro);
	abb_insertar(abb, &seis);
	abb_insertar(abb, &cinco);
	abb_insertar(abb, &siete);
	abb_insertar(abb, &dos);
	abb_insertar(abb, &tres);
	abb_insertar(abb, &uno);

	int contador = 0;
	pa2m_afirmar(abb_recorrer(abb, PREORDEN, vector, tamanio) == 7,
		     "Se puede recorrer el árbol por PREORDEN");
	for (int i = 0; i < tamanio; i++) {
		if (vector[i])
			contador++;
	}
	pa2m_afirmar(contador == 7,
		     "El vector tiene la cantidad correcta de elementos");
	pa2m_afirmar(*((int *)vector[0]) == 4,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*((int *)vector[6]) == 7,
		     "El último elemento del vector es el correcto");

	free(vector);
	abb_destruir(abb);
}

void vector_recorrido_por_inorden()
{
	pa2m_nuevo_grupo("Rellenar vector por INORDEN");

	size_t tamanio = 7;
	void **vector = malloc(tamanio * sizeof(int *));
	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6,
	    siete = 7;

	abb_t *abb = abb_crear(comparador);
	abb_insertar(abb, &cuatro);
	abb_insertar(abb, &seis);
	abb_insertar(abb, &cinco);
	abb_insertar(abb, &siete);
	abb_insertar(abb, &dos);
	abb_insertar(abb, &tres);
	abb_insertar(abb, &uno);

	int contador = 0;
	pa2m_afirmar(abb_recorrer(abb, INORDEN, vector, tamanio) == 7,
		     "Se puede recorrer el árbol por INORDEN");
	for (int i = 0; i < tamanio; i++) {
		if (vector[i])
			contador++;
	}
	pa2m_afirmar(contador == 7,
		     "El vector tiene la cantidad correcta de elementos");
	pa2m_afirmar(*((int *)vector[0]) == 1,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*((int *)vector[6]) == 7,
		     "El último elemento del vector es el correcto");

	free(vector);
	abb_destruir(abb);
}

void vector_recorrido_por_postorden()
{
	pa2m_nuevo_grupo("Rellenar vector por POSTORDEN");

	size_t tamanio = 7;
	void **vector = malloc(tamanio * sizeof(int *));
	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6,
	    siete = 7;

	abb_t *abb = abb_crear(comparador);
	abb_insertar(abb, &cuatro);
	abb_insertar(abb, &seis);
	abb_insertar(abb, &cinco);
	abb_insertar(abb, &siete);
	abb_insertar(abb, &dos);
	abb_insertar(abb, &tres);
	abb_insertar(abb, &uno);

	int contador = 0;
	pa2m_afirmar(abb_recorrer(abb, POSTORDEN, vector, tamanio) == 7,
		     "Se puede recorrer el árbol por POSTORDEN");
	for (int i = 0; i < tamanio; i++) {
		if (vector[i])
			contador++;
	}
	pa2m_afirmar(contador == 7,
		     "El vector tiene la cantidad correcta de elementos");
	pa2m_afirmar(*((int *)vector[0]) == 1,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*((int *)vector[6]) == 4,
		     "El último elemento del vector es el correcto");

	free(vector);
	abb_destruir(abb);
}

void pruebas_iterador_vector_abb()
{
	vector_recorrido_por_preorden();
	vector_recorrido_por_inorden();
	vector_recorrido_por_postorden();
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== PRUEBAS DEL TDA - ABB ========================");

	pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN");
	pruebas_crear_abb();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR");
	pruebas_insertar_elemento_abb();

	pa2m_nuevo_grupo("PRUEBAS DE BUSQUEDA");
	pruebas_buscar_elemento_abb();

	pa2m_nuevo_grupo("PRUEBAS DE ELIMINACION");
	pruebas_quitar_elemento_abb();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR");
	pruebas_iterador_abb();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR Y VECTOR");
	pruebas_iterador_vector_abb();

	pa2m_nuevo_grupo("PRUEBAS CON NULL");
	pruebas_con_null_abb();

	return pa2m_mostrar_reporte();
}
