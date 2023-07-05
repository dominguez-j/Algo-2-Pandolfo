#include "pa2m.h"
#include "src/tp0.h"
#include <string.h>

#define MAX_NOMBRE 30

typedef struct aux {
	pokemon_t pokemones[10];
	size_t tope;
} aux_t;

// ~ CREACIÓN Y DESTRUCCIÓN ~
void pruebas_creacion_y_destruccion()
{
	pa2m_afirmar(
		hospital_crear(NULL, 10, 5) == NULL,
		"No se puede crear un hospital con vector de pokemones nulo");

	pokemon_t pokemones[2] = {
		{ .id = 2, .salud = 3, .nombre_entrenador = "Luis" },
		{ .id = 12, .salud = 6, .nombre_entrenador = "Luis" }
	};

	hospital_t *hospital = hospital_crear((pokemon_t *)pokemones, 2, 1);
	pa2m_afirmar(hospital != NULL, "Se crea un hospital correctamente");
	pa2m_afirmar(hospital_cantidad_entrenadores(hospital) == 1,
		     "La cantidad de entrenadores es 1");
	pa2m_afirmar(hospital_cantidad_pokemones(hospital) == 2,
		     "La cantidad de pokemones es 2");

	hospital_destruir(hospital);
}

// ~ REVISAR POKEMONES ~
// Iterador Interno

bool revisar_totalmente(pokemon_t *poke, void *aux)
{
	return true;
}

bool buscar_id(pokemon_t *poke, void *id)
{
	if (poke->id == *(size_t *)id)
		return false;
	return true;
}

void iterador_parametros_nulos_resulta_en_error()
{
	pokemon_t pokes_hospital[2] = {
		{ .id = 2, .salud = 3, .nombre_entrenador = "Luis" },
		{ .id = 12, .salud = 6, .nombre_entrenador = "Luis" }
	};
	hospital_t *hospital =
		hospital_crear((pokemon_t *)pokes_hospital, 2, 1);
	int aux = 8;

	pa2m_afirmar(hospital_a_cada_pokemon(NULL, revisar_totalmente, &aux) ==
			     0,
		     "No es posible revisar un hospital nulo");
	pa2m_afirmar(hospital_a_cada_pokemon(hospital, NULL, &aux) == 0,
		     "No es posible revisar un hospital con una función nula");
	pa2m_afirmar(
		hospital_a_cada_pokemon(hospital, revisar_totalmente, NULL) ==
			2,
		"Es posible revisar un hospital valido con una funcion valida y "
		"un aux nulo");

	hospital_destruir(hospital);
}

void se_puede_revisar_todo_el_hospital()
{
	pokemon_t pokes_hospital[3] = {
		{ .id = 2, .salud = 3, .nombre_entrenador = "Luis" },
		{ .id = 12, .salud = 6, .nombre_entrenador = "Luis" },
		{ .id = 8, .salud = 16, .nombre_entrenador = "Maria" }
	};
	hospital_t *hospital =
		hospital_crear((pokemon_t *)pokes_hospital, 3, 2);

	pa2m_afirmar(hospital_a_cada_pokemon(hospital, revisar_totalmente,
					     NULL) == 3,
		     "Es posible revisar todos los pokemones del hospital");

	hospital_destruir(hospital);
}

void se_puede_revisar_parte_del_hospital()
{
	size_t primer_id = 2;
	size_t segundo_id = 15;
	size_t tercer_id = 8;
	size_t inexistente_id = 18;

	pokemon_t pokes_hospital[3] = {
		{ .id = primer_id, .salud = 3, .nombre_entrenador = "Luis" },
		{ .id = segundo_id, .salud = 6, .nombre_entrenador = "Luis" },
		{ .id = tercer_id, .salud = 16, .nombre_entrenador = "Maria" }
	};
	hospital_t *hospital =
		hospital_crear((pokemon_t *)pokes_hospital, 3, 2);

	pa2m_afirmar(
		hospital_a_cada_pokemon(hospital, buscar_id, &primer_id) == 1,
		"Es posible buscar el primer poke con el iterador interno");
	pa2m_afirmar(
		hospital_a_cada_pokemon(hospital, buscar_id, &segundo_id) == 2,
		"Es posible buscar un poke del medio con el iterador interno");
	pa2m_afirmar(
		hospital_a_cada_pokemon(hospital, buscar_id, &tercer_id) == 3,
		"Es posible buscar el ultimo poke con el iterador interno");
	pa2m_afirmar(
		hospital_a_cada_pokemon(hospital, buscar_id, &inexistente_id) ==
			3,
		"Es posible buscar un poke que no esta con el iterador interno");

	hospital_destruir(hospital);
}

void pruebas_iterador_interno()
{
	pa2m_nuevo_grupo("Parámetros nulos");
	iterador_parametros_nulos_resulta_en_error();

	pa2m_nuevo_grupo("Iterar el hospital es posible");
	se_puede_revisar_todo_el_hospital();
	se_puede_revisar_parte_del_hospital();
}

// ~ EMERGENCIAS ~

void ambulancia_parametros_nulos_resulta_en_error()
{
	pokemon_t pokes_ambulancia[2] = {
		{ .id = 2, .salud = 3, .nombre_entrenador = "Luis" },
		{ .id = 12, .salud = 6, .nombre_entrenador = "Luis" }
	};
	hospital_t *hospital =
		hospital_crear((pokemon_t *)pokes_ambulancia, 2, 1);

	pa2m_afirmar(
		hospital_aceptar_emergencias(
			NULL, (pokemon_t *)pokes_ambulancia, 2, 2) == ERROR,
		"No se puede ingresar pokes por ambulancia a un hospital nulo");
	pa2m_afirmar(
		hospital_aceptar_emergencias(hospital, NULL, 0, 0) == ERROR,
		"No se puede ingresar pokes nulos por ambulancia a un hospital válido");

	hospital_destruir(hospital);
}

bool pokemones_a_vector(pokemon_t *poke, void *aux_)
{
	aux_t *aux = aux_;
	pokemon_copiar(&aux->pokemones[aux->tope], *poke);
	aux->tope++;
	return true;
}

void hospital_puede_recibir_ambulancia_vacia()
{
	pokemon_t pokes_hospital[2] = {
		{ .id = 24, .salud = 3, .nombre_entrenador = "Carlos" },
		{ .id = 453, .salud = 34, .nombre_entrenador = "Maria" }
	};
	pokemon_t pokes_ambulancia[3];

	hospital_t *hospital = hospital_crear(pokes_hospital, 2, 2);
	pa2m_afirmar(hospital_aceptar_emergencias(hospital, pokes_ambulancia, 0,
						  0) == EXITO,
		     "El hospital acepto la ambulancia vacia");
	pa2m_afirmar(hospital_cantidad_entrenadores(hospital) == 2,
		     "La cantidad de entrenadores es la original");
	pa2m_afirmar(hospital_cantidad_pokemones(hospital) == 2,
		     "La cantidad de pokemones es la original");

	aux_t aux;
	aux.tope = 0;
	pa2m_afirmar(
		hospital_a_cada_pokemon(hospital, pokemones_a_vector, &aux) ==
			2,
		"Se iteran todos los pokemones correctamente y se guardan en un vector");
	pa2m_afirmar(
		pokemones_comparar(&aux.pokemones[0], &pokes_hospital[0]),
		"El primer pokemon en el vector es el mismo que se encuentra al "
		"principio en el hospital");
	pa2m_afirmar(
		pokemones_comparar(&aux.pokemones[1], &pokes_hospital[1]),
		"El segundo y ultimo pokemon en el vector es el mismo que se "
		"encuentra al principio en el hospital");

	hospital_destruir(hospital);
}

void hospital_puede_recibir_pokes_por_ambulancia()
{
	size_t cant_pokes_inicial = 2;
	size_t cant_entrenadores_inicial = 2;
	pokemon_t pokes_hospital[2] = {
		{ .id = 24, .salud = 3, .nombre_entrenador = "Carlos" },
		{ .id = 453, .salud = 34, .nombre_entrenador = "Maria" }
	};

	size_t cant_pokes_ambulancia = 4;
	size_t cant_entrenadores_nuevos = 2;
	pokemon_t pokes_ambulancia[4] = {
		{ .id = 2, .salud = 1, .nombre_entrenador = "Luis" },
		{ .id = 12, .salud = 8, .nombre_entrenador = "Maria" },
		{ .id = 1212, .salud = 13, .nombre_entrenador = "Tamara" },
		{ .id = 172, .salud = 70, .nombre_entrenador = "Tamara" }
	};

	hospital_t *hospital = hospital_crear(
		pokes_hospital, cant_pokes_inicial, cant_entrenadores_inicial);
	pa2m_afirmar(
		hospital_aceptar_emergencias(hospital, pokes_ambulancia,
					     cant_pokes_ambulancia,
					     cant_entrenadores_nuevos) == EXITO,
		"Los pokes de la ambulancia se ingresan al hospital correctamente");
	pa2m_afirmar(hospital_cantidad_entrenadores(hospital) ==
			     cant_entrenadores_inicial +
				     cant_entrenadores_nuevos,
		     "La cantidad de entrenadores se actualizó correctamente");
	pa2m_afirmar(hospital_cantidad_pokemones(hospital) ==
			     cant_pokes_ambulancia + cant_pokes_inicial,
		     "La cantidad de pokemones se actualizó correctamente");

	aux_t aux;
	aux.tope = 0;
	pa2m_afirmar(
		hospital_a_cada_pokemon(hospital, pokemones_a_vector, &aux) ==
			cant_pokes_ambulancia + cant_pokes_inicial,
		"Se iteran todos los pokemones correctamente y se guardan en un vector");
	pa2m_afirmar(pokemones_comparar(&aux.pokemones[0],
					&pokes_ambulancia[0]),
		     "El primer pokemon en el vector es el que deberia ser");
	pa2m_afirmar(pokemones_comparar(&aux.pokemones[1], &pokes_hospital[0]),
		     "El segundo pokemon en el vector es el que deberia ser");
	pa2m_afirmar(pokemones_comparar(&aux.pokemones[2],
					&pokes_ambulancia[1]),
		     "El tercer pokemon en el vector es el que deberia ser");
	pa2m_afirmar(pokemones_comparar(&aux.pokemones[3],
					&pokes_ambulancia[2]),
		     "El cuarto pokemon en el vector es el que deberia ser");
	pa2m_afirmar(pokemones_comparar(&aux.pokemones[4], &pokes_hospital[1]),
		     "El quinto pokemon en el vector es el que deberia ser");
	pa2m_afirmar(
		pokemones_comparar(&aux.pokemones[5], &pokes_ambulancia[3]),
		"El sexto y ultimo pokemon en el vector es el que deberia ser");

	hospital_destruir(hospital);
}

void pruebas_emergencias()
{
	pa2m_nuevo_grupo("Parámetros nulos");
	ambulancia_parametros_nulos_resulta_en_error();

	pa2m_nuevo_grupo("Ambulancia vacia");
	hospital_puede_recibir_ambulancia_vacia();

	pa2m_nuevo_grupo("Agregando al hospital pokes de la ambulancia");
	hospital_puede_recibir_pokes_por_ambulancia();
}

int main()
{
	pa2m_nuevo_grupo("------------ PRUEBAS DEL TP0 ------------");

	pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN Y DESTRUCCIÓN");
	pruebas_creacion_y_destruccion();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO");
	pruebas_iterador_interno();

	pa2m_nuevo_grupo("PRUEBAS DE EMERGENCIAS");
	pruebas_emergencias();

	return pa2m_mostrar_reporte();
}