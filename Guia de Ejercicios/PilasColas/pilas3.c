/*
Escribir una funcion que reciba por parametro dos pilas y modifique su
contenido de manera que los elemento de la primer pila queden en la 
segunda, y los de la segunda en la primera manteniendo el orden original de
los elementos. Como estructuras auxiliares, se pueden utilizar únicamente 
pilas y/o colas.
*/



void swap_pilas(pila_t *p1, pila_t *p2){

	//se necesitan 2 pilas auxiliares para mantener el ordenamiento
	pila_t *aux = pila_crear()
	pila_t *aux2 = pila_crear()

	while( !pila_esta_vacia(p1)){
		//paso todos los elemento de p1 a aux
		pila_apilar(aux, pila_desapilar(p1));
	}
	while( !pila_esta_vacia(p2)){
		//paso todos los elemento de p2 a aux2
		pila_apilar(aux2, pila_desapilar(p2));
	}
	while( !pila_esta_vacia(aux)){
		//paso todos los elemento de aux a p2
		pila_apilar(p2, pila_desapilar(aux));
	}
	while( !pila_esta_vacia(aux)){
		//paso todos los elemento de aux2 a p1
		pila_apilar(p1, pila_desapilar(aux2));
	}

	pila_destruir(aux);
	pila_destruir(aux2);
}