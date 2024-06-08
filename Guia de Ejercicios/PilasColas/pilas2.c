/*
Escribir una funcion 'reemplazar' que tome una 'pila', un 'valor_nuevo' y un 
'valor_viejo' y reemplace en la 'pila' todas las ocurrencias de 'valor_viejo'
por 'valor_nuevo'. Al finalizar la ejecucion, la pila debe quedar en el mismo estado
que tenia antes de ejecutarse.
*/

void reemplazar(pila_t *pila, int original, int reeemplazo){
	pila_t *p_aux = pila_crear();

	while( !pila_esta_vacia(pila)){
		int elem = pila_desapilar(pila);
		if(elem == original){
			elem = reemplazo;
		}
		pila_apilar(p_aux, elem);
	}

	while( !pila_esta_vacia(p_aux)){
		int elem = pila_desapilar(p_aux);
		pila_apilar(pila, elem);
	}
	pila_destruir(p_aux);
}

