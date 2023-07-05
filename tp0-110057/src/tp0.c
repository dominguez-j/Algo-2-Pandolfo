#include "tp0.h"

#include <stdio.h>
#include <string.h>

/**
 * Funcion que ordena el vector de pokemones por salud. De menor a mayor salud.
 */
void ordenar_pokemones_por_salud(hospital_t *hospital)
{
	pokemon_t poke_aux;

	for (size_t i = 1; i < hospital->cantidad_pokemon; i++) {
		for (size_t j = 0; j < hospital->cantidad_pokemon - i; j++) {
			if (hospital->pokemones[j].salud >
			    hospital->pokemones[j + 1].salud) {
				poke_aux = hospital->pokemones[j];
				hospital->pokemones[j] =
					hospital->pokemones[j + 1];
				hospital->pokemones[j + 1] = poke_aux;
			}
		}
	}
}

/**
 * Reserva memoria para un hospital y la inicializa.
 * Se puede asumir que los pokemones están ordenados
 *
 * Devuelve NULL en caso de no poder.
 */
hospital_t *hospital_crear(pokemon_t *pokemones, size_t cantidad_pokemones,
			   size_t cantidad_entrenadores)
{
	if (!pokemones || cantidad_pokemones <= 0)
		return NULL;

	hospital_t *hospital = malloc(sizeof(hospital_t));

	if (!hospital)
		return NULL;

	pokemon_t *poke_aux = malloc(cantidad_pokemones * sizeof(pokemon_t));

	if (!poke_aux) {
		free(hospital);
		return NULL;
	}

	hospital->cantidad_pokemon = cantidad_pokemones;
	hospital->cantidad_entrenadores = cantidad_entrenadores;
	hospital->pokemones = poke_aux;

	for (size_t i = 0; i < cantidad_pokemones; i++)
		pokemon_copiar(&hospital->pokemones[i], pokemones[i]);

	ordenar_pokemones_por_salud(hospital);

	return hospital;
}

/**
 * Devuelve la cantidad de entrenadores que actualmente hacen atender a sus
 * pokemon en el hospital.
 */
size_t hospital_cantidad_entrenadores(hospital_t *hospital)
{
	return !hospital ? 0 : hospital->cantidad_entrenadores;
}

/**
 * Devuelve la cantidad de pokemon que son atendidos actualmente en el hospital.
 */
size_t hospital_cantidad_pokemones(hospital_t *hospital)
{
	return !hospital ? 0 : hospital->cantidad_pokemon;
}

/**
 * Aplica una función a cada uno de los pokemon almacenados en el hospital. La
 * función debe aplicarse a cada pokemon en orden de prioridad del pokemon. A menor salud,
 * mayor prioridad tiene un pokemon.
 *
 * La función a aplicar recibe el pokemon y devuelve true o false. Si la función
 * devuelve true, se debe seguir aplicando la función a los próximos pokemon si
 * quedan. Si la función devuelve false, no se debe continuar.
 *
 * Devuelve la cantidad de pokemon a los que se les aplicó la función (hayan devuelto true o false).
 */
size_t hospital_a_cada_pokemon(hospital_t *hospital,
			       bool (*funcion)(pokemon_t *p, void *aux),
			       void *aux)
{
	if (!funcion || !hospital)
		return 0;

	size_t i = 0;
	size_t cant_pokemon = hospital_cantidad_pokemones(hospital);
	bool seguir = true;

	while (seguir && i < cant_pokemon) {
		seguir = funcion(&hospital->pokemones[i], aux);
		i++;
	}

	return i;
}

/**
 * Dados dos pokemones, la funcion devuelve true si son iguales, es decir, todos sus atributos son identicos
 * o false en caso contrario.
 */
bool pokemones_comparar(pokemon_t *pokemon1, pokemon_t *pokemon2)
{
	if (!pokemon1 || !pokemon2)
		return false;

	if (pokemon1->id == pokemon2->id &&
	    pokemon1->salud == pokemon2->salud &&
	    strcmp(pokemon1->nombre_entrenador, pokemon2->nombre_entrenador) ==
		    0)
		return true;

	return false;
}

/**
 * Funcion que copia lo que hay en poke_origen a poke_destino. Si alguna de las dos variables es NULL,
 * devuelve false. Si no, se copia el pokemon y se devuelve true.
 */
bool pokemon_copiar(pokemon_t *poke_destino, pokemon_t poke_origen)
{
	if (!poke_destino)
		return false;

	poke_destino->id = poke_origen.id;
	poke_destino->salud = poke_origen.salud;
	strcpy(poke_destino->nombre_entrenador, poke_origen.nombre_entrenador);

	return true;
}

/**
 *  Cuando ocurre una emergencia, llegan nuevos pokemones en ambulancia, que deben ser ingresados al hospital.
 *  Se debe mantener el orden de prioridad de los pokemones! Los pokemones con menor salud deben estar lo más adelante
 *  en la fila posible
 *  Devuelve -1 en caso de error o 0 en caso de éxito
 */
int hospital_aceptar_emergencias(hospital_t *hospital,
				 pokemon_t *pokemones_ambulancia,
				 size_t cant_pokes_ambulancia,
				 size_t cant_nuevos_entrenadores)
{
	if (!hospital || !pokemones_ambulancia)
		return ERROR;

	if (cant_pokes_ambulancia == 0)
		return EXITO;

	size_t total = cant_pokes_ambulancia + hospital->cantidad_pokemon;

	pokemon_t *poke_aux =
		realloc(hospital->pokemones, total * sizeof(pokemon_t));

	if (!poke_aux)
		return ERROR;

	hospital->pokemones = poke_aux;

	bool seguir = true;
	size_t j = 0;

	for (size_t i = hospital->cantidad_pokemon; i < total && seguir; i++) {
		seguir = pokemon_copiar(&hospital->pokemones[i],
					pokemones_ambulancia[j]);
		j++;
	}

	if (!seguir)
		return ERROR;

	hospital->cantidad_pokemon += cant_pokes_ambulancia;
	hospital->cantidad_entrenadores += cant_nuevos_entrenadores;

	ordenar_pokemones_por_salud(hospital);

	return EXITO;
}

/**
 *  Libera el hospital y toda la memoria utilizada por el mismo.
 */
void hospital_destruir(hospital_t *hospital)
{
	free(hospital->pokemones);
	free(hospital);
}
