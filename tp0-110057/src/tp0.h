//Este archivo NO SE PUEDE MODIFICAR

#ifndef TP0_H_
#define TP0_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1
#define EXITO 0
#define MAX_NOMBRE 30

typedef struct _hospital_pkm_t hospital_t;
typedef struct _pkm_t pokemon_t;

struct _hospital_pkm_t {
	pokemon_t *pokemones;
	size_t cantidad_pokemon;
	size_t cantidad_entrenadores;
};

struct _pkm_t {
	size_t id;
	size_t salud;
	char nombre_entrenador[MAX_NOMBRE];
};

/**
 * Reserva memoria para un hospital y la inicializa.
 * Se puede asumir que los pokemones están ordenados
 *
 * Devuelve NULL en caso de no poder.
 */
hospital_t *hospital_crear(pokemon_t *pokemones, size_t cantidad_pokemones,
			   size_t cantidad_entrenadores);

/**
 * Devuelve la cantidad de entrenadores que actualmente hacen atender a sus
 * pokemon en el hospital.
 */
size_t hospital_cantidad_entrenadores(hospital_t *hospital);

/**
 * Devuelve la cantidad de pokemon que son atendidos actualmente en el hospital.
 */
size_t hospital_cantidad_pokemones(hospital_t *hospital);

/**
 * Aplica una función a cada uno de los pokemon almacenados en el hospital. La
 * función debe aplicarse a cada pokemon en orden alfabético.
 *
 * La función a aplicar recibe el pokemon y la variable auxiliar que se le paso a hospital_a_cada_pokemon
 * y devuelve true o false. Si la función devuelve true, se debe seguir aplicando la función a los próximos 
 * pokemon si quedan. Si la función devuelve false, no se debe continuar.
 *
 * Devuelve la cantidad de pokemon a los que se les aplicó la función (hayan devuelto true o false).
 */
size_t hospital_a_cada_pokemon(hospital_t *hospital,
			       bool (*funcion)(pokemon_t *p, void *aux),
			       void *aux);

/**
 *  Cuando ocurre una emergencia, llegan nuevos pokemones en ambulancia, que deben ser ingresados al hospital.
 *  Se debe mantener el orden de prioridad de los pokemones! Los pokemones con menor salud deben estar lo más adelante
 *  en la fila posible
 *  Devuelve -1 en caso de error o 0 en caso de éxito
 */
int hospital_aceptar_emergencias(hospital_t *hospital,
				 pokemon_t *pokemones_ambulancia,
				 size_t cant_pokes_ambulancia,
				 size_t cant_nuevos_entrenadores);

/**
 * Dados dos pokemones, la funcion devuelve true si son iguales, es decir, todos sus atributos son identicos
 * o false en caso contrario.
 */
bool pokemones_comparar(pokemon_t *pokemon1, pokemon_t *pokemon2);

/**
 * Funcion que copia lo que hay en poke_origen a poke_destino. Si poke_destino es NULL,
 * devuelve false. Si no, se copia el pokemon y se devuelve true.
 */
bool pokemon_copiar(pokemon_t *poke_destino, pokemon_t poke_origen);

/**
 *  Libera el hospital y toda la memoria utilizada por el mismo.
 */
void hospital_destruir(hospital_t *hospital);

#endif // TP0_H_
