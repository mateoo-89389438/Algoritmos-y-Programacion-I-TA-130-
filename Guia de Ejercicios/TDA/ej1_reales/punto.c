#include "punto.h"


struct punto {
    double x;
    double y;
};


punto_t * punto_crear(double x, double y){ //constructor

	punto_t * p = malloc(sizeof(punto_t)) 
	if(p == NULL){
		return NULL;
	}
	p->x = x;
	p->y = y;
	return p;
} 


void punto_destruir(punto_t *p){ //destructor
	free(p);
}

punto_t * punto_copiar(punto_t *q, const punto_t *p){ 
	q->x = p->x;
	q->y = p->y;
	return q;
}

punto_t * punto_clonar(const punto_t *p) { 
    return punto_crear(p->x, p->y);
}

double punto_get_x(const punto_t *p){
	return p->x;
}

double punto_get_y(const punto_t *p){
	return p->y;
}

double punto_set_x(punto_t *q, double x){
	q->x = x;
	return q->x;
}

double punto_set_y(punto_t *q, double y){
	q->y = y;
	return q->y;
}

punto_t * punto_sumar(punto_t *q, const punto_t *p){
	q->x += p->x;
	q->y += p->y;
	return q;	
}

punto_t * punto_restar(punto_t *q, const punto_t *p){
	q->x -= p->x;
	q->y -= p->y;
	return q;	
}

















