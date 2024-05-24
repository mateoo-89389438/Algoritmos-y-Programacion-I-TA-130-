#include "complejo.h"

#include <stdlib.h>
#include <math.h>

struct complejo{
    double real;
    double imag;
};


double complejo_real(complejo_t *a){
	return a->real;
}

double complejo_imaginaria(complejo_t *c){
	return a->imag;
}


double complejo_modulo(const complejo_t *c){
	return sqrt((c->real * c->real) + (c->imag + c->imag));
}

double complejo_argumento(const complejo_t *c){
	return atan2(c->imag, c->real)
}
