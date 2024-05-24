#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//EJ1
#define MASK_ALTA1 0x07 //0000 0111
#define MASK_BAJA1 0x1F //0001 1111
#define SHIFT_ALTA 5
#define MASK_ALTA2 0x40  //0100 0000
#define MASK_BAJA2 0x60  //0110 0000

uint8_t obtener_byte(uint8_t alta, uint8_t baja){
	uint8_t byte;
	byte = (alta & MASK_ALTA1) << SHIFT_ALTA;
	byte += baja & MASK_BAJA1;
	return byte;
}

void generar_byte(uint8_t byte, uint8_t *alta, uint8_t *baja){
	*alta = (((byte & (MASK_ALTA1 << SHIFT_ALTA)) >> SHIFT_ALTA) | MASK_ALTA2);
	*baja = ((byte & MASK_BAJA1) | MASK_BAJA2);
}


char **clonar_arreglo_cadenas(const char *ss[]) {
  size_t i = 0;
  char ** v = NULL;
  while(ss[i] != NULL){

  	//Memoria para el arreglo de punteros (filas)
  	char ** w = realloc(v, (i+1)*sizeof(char *));
  	if(w == NULL){
  		return NULL;
  	}
  	v = w;

  	//Memoria para cada elemento particular (columnas)
  	char * p = realloc(v[i], (strlen(ss[i]))*sizeof(char));
  	if(p == NULL){
  		free(v);
  		return NULL;
  	}

  	v[i] = p;
  	strcpy(v[i], ss[i]);
  	i++;
  }
  v[i] = NULL;
  return v;

}


void destruir_arreglo_cadenas(char *ss[]){
	for(size_t i = 0; ss[i] != NULL; i++){
		free(ss[i]);
	}
	free(ss);
}
	


//EJ3
int *generar_aleatorios(int max, size_t *n){
	int * v = NULL;
	//*n = 0;
	int gen;
	size_t i = 0;
	while((gen = rand()) < max){
		//genero un w para que si falla realloc no se pierda lo que ya se pidio
		int * w = realloc(v, sizeof(int)* ++i);
		if( w == NULL){
			free(v);
			return v;
		}
		v[i] = gen;
		//i++;
	}
	*n = i;
	return v;
}

int *generar_aleatorios(int max, size_t *n){
	int * v = NULL;
	*n = 0;

	while((int c = rand()) <= max){

		int * w = realloc(v, sizeof(int)*((*n)+1));
		if( w == NULL){
			break;
		}
		v = w;
		v[*n] = c;
		(*n)++;
	}
	return v;
}



int main(){

	//EJ1
	//a.
	uint8_t alta = 0x45;  //0100 0101
	uint8_t baja = 0x79;  //0111 1001
	uint8_t n = obtener_byte(alta, baja);
	printf("Byte obtenido: %d\n", n);

	//b.
	uint8_t a;
	uint8_t b;
	generar_byte(n, &a, &b);
	printf("Alta: %d\nBaja: %d\n", a, b);
	return 0;



	//EJ2

  	// Defino el arreglo de cadenas 
  	const char *cadenas_originales[] = {"Hola", "mundo", "!", NULL};

  	//Clona el arreglo de cadenas
  	char **cadenas_clonadas = clonar_arreglo_cadenas(cadenas_originales);

  	//Imprime las cadenas clonadas
  	for (size_t i = 0; cadenas_clonadas[i] != NULL; i++) {
    	printf("%s\n", cadenas_clonadas[i]);
  	}

  	//Destruccion del arreglo de cadenas clonadas
  	destruir_arreglo_cadenas(cadenas_clonadas);

  	return 0;

  	//EJ3
  
  	// Variable para almacenar el tamaño del arreglo generado
  	size_t vec_len;

  	// Genera el arreglo de números aleatorios
  	int *vec = generar_aleatorios(100, &vec_len);

  	if( vec == NULL){
  		return 1;
  	}

  	// Imprime los números aleatorios generados
  	for (size_t i = 0; i < vec_len; i++) {
    	printf("%d\n", vec[i]);
 	 }
  	printf("\n");

  	// Libera la memoria asignada al arreglo
  	free(vec);

}