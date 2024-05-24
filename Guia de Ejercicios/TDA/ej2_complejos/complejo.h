#ifndef COMPLEJO_H
#define COMPLEJO_H

typedef struct complejo complejo_t;

complejo_t *complejo_crear(double real, double imag); //Constructor
complejo_t *complejo_crear_ma(double modulo, double argumento); //Constructor
void complejo_destruir(complejo_t *c); //Destructor

//Primitivas
complejo_t *complejo_clonar(const complejo_t *c);

complejo_t *complejo_sumar(complejo_t *a, const complejo_t *b);
complejo_t *complejo_multip(complejo_t *a, const complejo_t *b);
complejo_t *complejo_restar(complejo_t *a, const complejo_t *b);
complejo_t *complejo_dividir(complejo_t *a, const complejo_t *b);
double complejo_modulo(complejo_t *c);
double complejo_argumento(complejo_t *c);
double complejo_real(complejo_t *c);
double complejo_imaginaria(complejo_t *c);

//*Como el primer argumento de cada funcion no tiene const es ahi donde se guarda
//el resultado de la operacion, al igual que en strcpm, strlen, strcpy, etc.
#endif 
