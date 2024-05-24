#include "complejo.h"
#include <stdio.h>

int main(){
	complejo_t *a, *b, *c;

	complejo_t *cuatro, *dos;
	cuatro = complejo_crear(4, 0);
	dos = complejo_crear(2, 0);

	//Calculo: 4.a.c

	complejo_multip(complejo_multip(cuatro, a),c);
	

	//Imprimo el numero complejo
	printf("%f + %fj", complejo_real(cuatro), complejo_imaginaria(cuatro));

	//Destructor a todo
	complejo_destruir(cuatro);
	complejo_destruir(a);
	complejo_destruir(b);
	complejo_destruir(c);

}