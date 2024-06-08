/*
Se tiene una cadena que representa una ecuacinón matematcia. Se quiere saber si
la misma tiene los parentesis puestos de forma consistente.

Por ejemplo: "5 + (6 * (4 - 3) + 1)" sí los tiene consistentes, mientas que 
"5 + (6 * 5) + 1)" no.

Implementar una funcion 'bool parentesis_correcto(const char *s)'
*Se tiene disponibles las primitivas del TDA pilas
*/

#include <stdbool.h>


bool parentesis_correcto(const char *s){
	pilas_t *p = pila_crear();
	if( p == NULL) return NULL;

	for(size_t i = 0; i < strlen(s), i++){
		if(s[i] == '('){
			pilar_apilar(p, s[i]);
		}
		if(s[i] == ')'){
			char tope = pila_desapilar(p);
			if(tope != '('){
				return false;
			}
		}
	}

	//pila_destruir(pila_t *pila, void (*destruir_dato)(void *));
	return pila_esta_vacia(p);
}

