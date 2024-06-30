#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_STRING 100

typedef struct{
	char nombre[MAX_STRING]; //representa el nombre de la opcion votada
	size_t n_votos; //Por defecto arranca en 1 (uno). votos >= 1
	//votos no arranca en cero porque si no ni existiria.
}opcion_t;

// estructura para guardar todos los votos
typedef struct{
	//arreglo con cada una de las opciones (representada sobre una estructura). 
	//No hay opciones repetidas
	opcion_t *opciones;
	size_t n_op; //numero de opciones = largo del vector
	// n == 0 <=> opciones == NULL;
} votacion_t;


float votacion_porcentaje_opcion(const votacion_t *v, const char *opcion){

	//primero hay que calcular el total de los votos
	size_t votosTotales = 0;
	for(size_t i = 0; i < v->n_op; i++){
		votosTotales += v->opciones[i].n_votos;
	}

	//calculo el numero de votos de la opcion pedida
	size_t votosOpcion;
	for(size_t j = 0; j < v->n_op; j++){
		if( !strcmp(v->opciones[j].nombre, opcion)){
			votosOpcion = v->opciones[j].n_votos;
		}
	}

	//calculo y devuelvo el porcentaje por el nombre
	return (float)votosOpcion/votosTotales;
}



bool votacion_votar(votacion_t *v, const char *opcion){
	//si la opcion ya estaba solo le sumo un voto
	for(size_t k = 0; k < v->n_op; k++){
		if (!strcmp(v->opciones[k].nombre, opcion)){
			v->opciones[k].n_votos++;
			return true;
		}
	}

	// agrego la opcion al arreglo si no estaba
	opcion_t *p = realloc(v->opciones, (v->n_op + 1)*sizeof(opcion_t));
	if( p == NULL){
		return false;
	}

	v->opciones = p;
	strcpy(v->opciones[v->n_op].nombre, opcion);
	v->opciones[v->n_op].n_votos = 1; // votos = 1 pq se esta agregando por primera vez
	v->n_op++;
	return true;
}





//EJ2

bool escribir_doubles(const char *r, const double a[], size_t n){

	FILE *fo = fopen(r, "wb");
	if(fo = NULL){
		retrun false;
	}

	//primero escribo el n
	if (fwrite(&n, sizeof(size_t), 1, fo) != 1){
		fclose(fo);
		return false;
	}

	//despues escribo el arreglo 
	if (fwrite(a; sizeof(double), n, fo) != n){
		fclose(fo);
		return false;
	}
	//*Podria poner los dos en el mismo if pero asi queda mas legible(?

	fclose(fo);
	return true;
}

double *leer_doubles(const char *r, size_t *n){
	
	FILE *fi = fopen(r, "rb");
	if(fi = NULL){
		retrun false;
	}

	if (fread(n, sizeof(size_t), 1, fi) != 1){
		fclose(fi);
		return NULL;
	}

	double *a = malloc( (*n) * sizeof(double))
	if( a == NULL){
		fclose(fi);
		return NULL
	}

	if (fread(a, sizeof(double), *n, fi) != *n){
		free(a);
		fclose(fi);
		return NULL;
	}

	fclose(fi);
	return a;
}


//EJ3
int main(int argc, char *argv[]){

	if (argc != 5){
		fprintf(stderr, "Uso; %s <entrada> <salida> a b\n", argv[0]);
		return 1;
	}

	size_t a = atoi(argv[3]);
	size_t b = atoi(argv[4]);


	char *ri = argv[1];
	size_t n;
	double *v = leer_doubles(ri, &n);
	if( v == NULL){
		return 1;
	}

	for(size_t j = 0; j < n; j++){
		v[j] = a*(v[j]) + b;
	}

	char *ro = argv[2];
	if ( !escribir_doubles(ro, v, n) ){
		free(v);
		return 1;
	}


	free(v);
	return 0;
}





