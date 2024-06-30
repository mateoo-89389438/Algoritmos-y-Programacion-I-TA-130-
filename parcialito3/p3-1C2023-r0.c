#include "feriados.h"
#include <stdlib.h>
#include <stdbool.h>

//1.
enum dia{
	LUNES, 
	MARTES, 
	MIERCOLES,
	JUEVES,
	VIERNES, 
};


struct feriados {
	// cada elemento del vector corresponde a un dia de la semana
	//el vector por defecto arranca con todos los elementos en cero
	size_t v[7]; 
}

typedef struct feriados feriados_t;


size_t feriados_totales(const feriados_t *feriados, enum dia dia){
	return feriados->v[dia];
}

bool feriados_agregar(feriados_t *feriados, enum dia dia){
	feriados->v[dia]++;
	return true;
}

//2.



