/*
Escribir una funcion que recibe una cola e invierte el orden de us elementos.
La funcion debe modificar la Cola recibida, **no** devolver una nueva.
*/



void cola_invertir(cola_t *c){

	cola_t *aux = pila_crear();
	if( aux == NULL) return;

	while( !cola_esta_vacia(c)){
		pila_apilar(aux, cola_desencolar(c));
	}

	while( !pila_esta_vacia(aux)){
		cola_encolar(c, pila_desapilar(aux));
	}

	pila_destruir(aux);

}