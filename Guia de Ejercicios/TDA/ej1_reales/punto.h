#ifndef PUNTO_H
#define PUNTO_H

typedef struct punto punto_t;


punto_t * punto_crear(double x, double y); //constructor
void punto_destruir(punto_t *p); //destructor
punto_t * punto_copiar(punto_t *q, const punto_t *p);
punto_t * punto_clonar(const punto_t *p);
double punto_get_x(const punto_t *p);
double punto_get_y(const punto_t *p);
double punto_set_x(punto_t *q, double x);
double punto_set_y(punto_t *q, double y);
punto_t * punto_sumar(punto_t *q, const punto_t *p);
punto_t * punto_restar(punto_t *q, const punto_t *p);


#endif