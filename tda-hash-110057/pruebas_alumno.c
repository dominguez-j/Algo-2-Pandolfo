#include "pa2m.h"
#include "src/hash.h"
#include <string.h>
#include <stdlib.h>

bool recorrer_todo(const char *clave, void *valor, void *aux)
{
	size_t *n = (size_t *)aux;
	(*n)++;
	return true;
}

bool recorrer_parcialemente(const char *clave, void *valor, void *aux)
{
	size_t *n = (size_t *)aux;
	if (*n < 4)
		(*n)++;
	return true;
}

bool recorrer_con_false(const char *clave, void *valor, void *aux)
{
	size_t *n = (size_t *)aux;
	(*n)++;
	return false;
}

void crear_hash_con_capacidad_menor_a_la_minima_no_es_error()
{
	pa2m_nuevo_grupo("Creando hash con capacidad menor a la minima");
	hash_t *hash = hash_crear(2);
	pa2m_afirmar(hash != NULL,
		     "Se puede crear un hash con capacidad menor a la minima");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash está vacío");

	hash_destruir(hash);
}

void crear_hash_con_capacidad_valida_no_es_error()
{
	pa2m_nuevo_grupo(
		"Creando hash con capacidad mayor o igual a la minima");
	hash_t *hash = hash_crear(10);
	pa2m_afirmar(hash != NULL,
		     "Se puede crear un hash con capacidad mayor a la minima");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash está vacío");

	hash_destruir(hash);
}

void pruebas_crear_hash()
{
	crear_hash_con_capacidad_menor_a_la_minima_no_es_error();
	crear_hash_con_capacidad_valida_no_es_error();
}

void insertar_par_con_clave_valida_no_es_error()
{
	pa2m_nuevo_grupo("Insertando par con clave válida, no repetida");
	hash_t *hash = hash_crear(5);
	hash_t *aux = hash_insertar(hash, "AAA", "Pablo", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <AAA|Pablo>");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La cantidad de pares es 1");

	aux = hash_insertar(hash, "BBB", "Juan", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <BBB|Juan>");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La cantidad de pares es 2");

	aux = hash_insertar(hash, "CCC", "Jose", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <CCC|Jose>");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de pares es 3");

	aux = hash_insertar(hash, "DDD", "Jorge", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <DDD|Jorge>");
	pa2m_afirmar(hash_cantidad(hash) == 4, "La cantidad de pares es 4");

	hash_destruir(hash);
}

void inserto_par_con_clave_repetida_no_es_error()
{
	pa2m_nuevo_grupo("Insertando par con clave válida, repetida");

	hash_t *hash = hash_crear(4);
	hash_t *aux = hash_insertar(hash, "AAA", "Pablo", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <AAA|Pablo>");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La cantidad de pares es 1");

	aux = hash_insertar(hash, "BBB", "Juan", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <BBB|Juan>");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La cantidad de pares es 2");

	aux = hash_insertar(hash, "CCC", "Jose", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <CCC|Jose>");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de pares es 3");

	aux = hash_insertar(hash, "AAA", "Martin", NULL);
	pa2m_afirmar(aux != NULL,
		     "Se ingresa un par <AAA|Martin>, clave repetida");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de pares es 3, no se ve modificada");
	void *elemento = hash_obtener(hash, "AAA");
	pa2m_afirmar(strcmp(elemento, "Martin") == 0,
		     "Se cambió Pablo por Martin");

	void *anterior = NULL;
	aux = hash_insertar(hash, "CCC", "Javier", &anterior);
	pa2m_afirmar(aux != NULL,
		     "Se ingresa un par <CCC|Javier>, clave repetida");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de pares es 3");
	pa2m_afirmar(strcmp(anterior, "Jose") == 0,
		     "Se cambió Jose por Javier");

	hash_destruir(hash);
}

void insertar_hasta_rehashear_no_es_error()
{
	pa2m_nuevo_grupo("Insertando hasta rehashear");
	hash_t *hash = hash_crear(3);
	hash_t *aux = hash_insertar(hash, "AAA", "Pablo", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <AAA|Pablo>");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La cantidad de pares es 1");

	aux = hash_insertar(hash, "BBB", "Juan", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <BBB|Juan>");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La cantidad de pares es 2");

	aux = hash_insertar(hash, "CCC", "Jose", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <CCC|Jose>");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de pares es 3");

	aux = hash_insertar(hash, "DDD", "Maria", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <DDD|Maria>");
	pa2m_afirmar(hash_cantidad(hash) == 4, "La cantidad de pares es 4");

	aux = hash_insertar(hash, "EEE", "Rodolfo", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <EEE|Rodolfo>");
	pa2m_afirmar(hash_cantidad(hash) == 5, "La cantidad de pares es 5");

	aux = hash_insertar(hash, "FFF", "Camila", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <FFF|Camila>");
	pa2m_afirmar(hash_cantidad(hash) == 6, "La cantidad de pares es 6");

	aux = hash_insertar(hash, "GGG", "Luna", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <GGG|Luna>");
	pa2m_afirmar(hash_cantidad(hash) == 7, "La cantidad de pares es 7");

	aux = hash_insertar(hash, "HHH", "Lucas", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <HHH|Lucas>");
	pa2m_afirmar(hash_cantidad(hash) == 8, "La cantidad de pares es 8");

	aux = hash_insertar(hash, "III", "Tomas", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <III|Tomas>");
	pa2m_afirmar(hash_cantidad(hash) == 9, "La cantidad de pares es 9");

	aux = hash_insertar(hash, "JJJ", "Tadeo", NULL);
	pa2m_afirmar(aux != NULL, "Se ingresa un par <JJJ|Tadeo>");
	pa2m_afirmar(hash_cantidad(hash) == 10, "La cantidad de pares es 10");

	hash_destruir(hash);
}

void pruebas_insertar_elemento_hash()
{
	insertar_par_con_clave_valida_no_es_error();
	inserto_par_con_clave_repetida_no_es_error();
	insertar_hasta_rehashear_no_es_error();
}

void buscar_elemento_con_clave_existente_no_es_error()
{
	pa2m_nuevo_grupo("Buscar elemento con clave existente");
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);

	void *elemento = hash_obtener(hash, "AAA");
	pa2m_afirmar(strcmp(elemento, "Pablo") == 0,
		     "Se ingresa AAA y se encuentra a Pablo");
	elemento = hash_obtener(hash, "DDD");
	pa2m_afirmar(strcmp(elemento, "Tomas") == 0,
		     "Se ingresa EEE y se encuentra a Tomas");

	hash_destruir(hash);
}

void buscar_elemento_con_clave_inexistente_es_error()
{
	pa2m_nuevo_grupo("Buscar elemento con clave inexistente");
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);

	bool existe = hash_obtener(hash, "FFF");
	pa2m_afirmar(!existe,
		     "Se ingresa FFF y no se encuentra a nadie con esa clave");

	hash_destruir(hash);
}

void pruebas_buscar_elemento_hash()
{
	buscar_elemento_con_clave_existente_no_es_error();
	buscar_elemento_con_clave_inexistente_es_error();
}

void quitar_elemento_con_clave_existente_no_es_error()
{
	pa2m_nuevo_grupo("Quitar elemento con clave existente");
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);

	void *elemento = hash_obtener(hash, "BBB");
	hash_t *aux = hash_quitar(hash, "BBB");
	pa2m_afirmar(aux != NULL, "Se quitó la clave BBB");
	pa2m_afirmar(strcmp(elemento, "Juan") == 0,
		     "El elemento de esa clave era Juan");
	elemento = hash_obtener(hash, "AAA");
	aux = hash_quitar(hash, "AAA");
	pa2m_afirmar(aux != NULL, "Se quitó la clave AAA");
	pa2m_afirmar(strcmp(elemento, "Pablo") == 0,
		     "El elemento de esa clave era Pablo");
	elemento = hash_obtener(hash, "CCC");
	aux = hash_quitar(hash, "CCC");
	pa2m_afirmar(aux != NULL, "Se quitó la clave CCC");
	pa2m_afirmar(strcmp(elemento, "Jose") == 0,
		     "El elemento de esa clave era Jose");
	elemento = hash_obtener(hash, "DDD");
	aux = hash_quitar(hash, "DDD");
	pa2m_afirmar(aux != NULL, "Se quitó la clave DDD");
	pa2m_afirmar(strcmp(elemento, "Tomas") == 0,
		     "El elemento de esa clave era Tomas");

	hash_destruir(hash);
}

void quitar_elemento_con_clave_inexistente_es_error()
{
	pa2m_nuevo_grupo("Quitar elemento con clave inexistente");
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);

	hash_t *aux = hash_quitar(hash, "FFF");
	pa2m_afirmar(
		!aux,
		"Se ingresa FFF y no se puede quitar un par con clave inexistente");

	hash_destruir(hash);
}

void pruebas_quitar_elemento_hash()
{
	quitar_elemento_con_clave_existente_no_es_error();
	quitar_elemento_con_clave_inexistente_es_error();
}

void recorrer_todo_el_hash_con_funcion_valida()
{
	pa2m_nuevo_grupo("Iterar hash completo");
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);
	hash_insertar(hash, "FFF", "Camila", NULL);
	hash_insertar(hash, "GGG", "Luna", NULL);
	hash_insertar(hash, "HHH", "Lucas", NULL);

	size_t n = 0;
	size_t contados = hash_con_cada_clave(hash, recorrer_todo, &n);

	pa2m_afirmar(hash_cantidad(hash) == 8,
		     "Se crea un hash con cantidad 8");
	pa2m_afirmar(n == contados, "Se invocó 8 veces la función");

	hash_destruir(hash);
}

void recorrer_parcialmente_el_hash_con_funcion_valida()
{
	pa2m_nuevo_grupo("Iterar hash parcialmente");
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);
	hash_insertar(hash, "FFF", "Camila", NULL);
	hash_insertar(hash, "GGG", "Luna", NULL);
	hash_insertar(hash, "HHH", "Lucas", NULL);

	size_t n = 0;
	size_t contados = hash_con_cada_clave(hash, recorrer_todo, &n);

	pa2m_afirmar(hash_cantidad(hash) == 8,
		     "Se crea un hash con cantidad 8");
	pa2m_afirmar(n == contados, "Se invocó 4 veces la función");

	hash_destruir(hash);
}

void recorrer_el_hash_con_funcion_false()
{
	pa2m_nuevo_grupo("Iterar hash con función false");
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);

	size_t n = 0;
	size_t contados = hash_con_cada_clave(hash, recorrer_con_false, &n);

	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "Se crea un hash con cantidad 5");
	pa2m_afirmar(n == contados, "Se invocó 1 vez la función");

	hash_destruir(hash);
}

void pruebas_iterador_hash()
{
	recorrer_todo_el_hash_con_funcion_valida();
	recorrer_parcialmente_el_hash_con_funcion_valida();
	recorrer_el_hash_con_funcion_false();
}

void destruir_todo_el_hash_no_es_error()
{
	pa2m_nuevo_grupo("Creando 5 pares y destruyendo todo el hash");

	hash_t *hash = hash_crear(10);
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "Se crea un hash, la cantidad de pares es 0");
	hash_insertar(hash, "AAA", malloc(sizeof(int)), NULL);
	pa2m_afirmar(hash_cantidad(hash) == 1, "La cantidad de pares es 1");
	hash_insertar(hash, "BBB", malloc(sizeof(int)), NULL);
	pa2m_afirmar(hash_cantidad(hash) == 2, "La cantidad de pares es 2");
	hash_insertar(hash, "CCC", malloc(sizeof(int)), NULL);
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de pares es 3");
	hash_insertar(hash, "DDD", malloc(sizeof(int)), NULL);
	pa2m_afirmar(hash_cantidad(hash) == 4, "La cantidad de pares es 4");
	hash_insertar(hash, "EEE", malloc(sizeof(int)), NULL);
	pa2m_afirmar(hash_cantidad(hash) == 5, "La cantidad de pares es 5");

	hash_destruir_todo(hash, free);
}

void destruir_el_hash_no_es_error()
{
	pa2m_nuevo_grupo("Creando 5 pares y destruyendo el hash");

	hash_t *hash = hash_crear(10);
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "Se crea un hash, la cantidad de pares es 0");
	hash_insertar(hash, "AAA", "Pablo", NULL);
	pa2m_afirmar(hash_cantidad(hash) == 1, "La cantidad de pares es 1");
	hash_insertar(hash, "BBB", "Martin", NULL);
	pa2m_afirmar(hash_cantidad(hash) == 2, "La cantidad de pares es 2");
	hash_insertar(hash, "CCC", "Jose", NULL);
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de pares es 3");
	hash_insertar(hash, "DDD", "Juan", NULL);
	pa2m_afirmar(hash_cantidad(hash) == 4, "La cantidad de pares es 4");
	hash_insertar(hash, "EEE", "Luz", NULL);
	pa2m_afirmar(hash_cantidad(hash) == 5, "La cantidad de pares es 5");

	hash_destruir(hash);
}

void pruebas_creación_y_destruccion()
{
	destruir_todo_el_hash_no_es_error();
	destruir_el_hash_no_es_error();
}

void insertar_par_con_clave_null_es_error()
{
	hash_t *hash = hash_crear(4);
	hash_t *aux = hash_insertar(hash, NULL, "Pablo", NULL);

	pa2m_afirmar(aux == NULL, "No se puede insertar un par con clave NULL");

	hash_destruir(hash);
}

void insertar_par_con_clave_valida_y_elemento_null_no_es_error()
{
	hash_t *hash = hash_crear(2);
	hash_t *aux = hash_insertar(hash, "AAA", NULL, NULL);

	pa2m_afirmar(aux != NULL, "Se puede insertar un par con elemento NULL");

	hash_destruir(hash);
}

void obtener_elemento_con_clave_null_es_error()
{
	hash_t *hash = hash_crear(4);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);

	void *elemento = hash_obtener(hash, NULL);

	pa2m_afirmar(elemento == NULL,
		     "No se puede obtener elemento con clave NULL");

	hash_destruir(hash);
}

void quitar_par_con_clave_null_es_error()
{
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);

	hash_t *aux = hash_quitar(hash, NULL);
	pa2m_afirmar(!aux, "No se puede quitar un par con clave NULL");

	hash_destruir(hash);
}

void recorrer_hash_con_funcion_null_es_error()
{
	pa2m_nuevo_grupo("Iterar hash con función null");
	hash_t *hash = hash_crear(10);
	hash_insertar(hash, "AAA", "Pablo", NULL);
	hash_insertar(hash, "BBB", "Juan", NULL);
	hash_insertar(hash, "CCC", "Jose", NULL);
	hash_insertar(hash, "DDD", "Tomas", NULL);
	hash_insertar(hash, "EEE", "Nicolas", NULL);

	size_t contados = hash_con_cada_clave(hash, NULL, NULL);

	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "Se crea un hash con cantidad 5");
	pa2m_afirmar(contados == 0, "Se invocó 0 veces la función");

	hash_destruir(hash);
}

void pruebas_null_hash()
{
	insertar_par_con_clave_null_es_error();
	insertar_par_con_clave_valida_y_elemento_null_no_es_error();
	obtener_elemento_con_clave_null_es_error();
	quitar_par_con_clave_null_es_error();
	recorrer_hash_con_funcion_null_es_error();
}

int main()
{
	pa2m_nuevo_grupo(
		"\n========================  PRUEBAS DEL TDA - HASH ========================");

	pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN");
	pruebas_crear_hash();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR");
	pruebas_insertar_elemento_hash();

	pa2m_nuevo_grupo("PRUEBAS DE BUSQUEDA");
	pruebas_buscar_elemento_hash();

	pa2m_nuevo_grupo("PRUEBAS DE ELIMINACION");
	pruebas_quitar_elemento_hash();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR");
	pruebas_iterador_hash();

	pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN Y DESTRUCCIÓN");
	pruebas_creación_y_destruccion();

	pa2m_nuevo_grupo("PRUEBAS DE NULL");
	pruebas_null_hash();

	return pa2m_mostrar_reporte();
}
