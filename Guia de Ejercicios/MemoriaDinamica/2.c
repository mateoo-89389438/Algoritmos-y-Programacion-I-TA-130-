#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>


//a.
int * copiarNumeros1(const int * array, size_t l){
	
	int * c = malloc( l * sizeof(int));
	if(c == NULL){
		return NULL;
	}

	for(size_t i = 0; i < l; i++){
		c[i] = array[i];
	}

	return c;

}	

//b. 
bool copiarNumeros2(const int * array, size_t l, int ** p){

	int * c = malloc( l * sizeof(int));
	if(c == NULL){
		return false;
	}

	for(size_t i = 0; i < l; i++){
		c[i] = array[i];
	}

	*p = c;

	return true;
}




int main(){
	
	int valores[] = {10, 20, 30, 40};
	size_t largo_valores = sizeof(valores)/sizeof(valores[0]);


	//a.
	int * n = copiarNumeros1(valores, largo_valores);

	if ( n == NULL ){
		puts("Error al copiar arreglo");
		return 1;
	}

	for(size_t j = 0; j < largo_valores; j++){
		printf("%d ", n[j]);
	}
  	puts("");
  	free(p);

	//b.
	int * p;
	if(!(copiarNumeros2(valores, largo_valores, &p))){
		puts("Error al copiar arreglo");
		return 1;
	}

	for(size_t j = 0; j < largo_valores; j++){
		printf("%d ", p[j]);
	}
  
  	free(p);

	return 0;
}












