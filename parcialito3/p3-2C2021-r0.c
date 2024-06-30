#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRING 100

//EJ1
struct opcion{
	//nombre almacena una cadena con el nombre candidato votado
	char nombre[MAX_STRING];
	//nro_votos almacena la cantidad total de votos
	//por defecto incia en 1, ya que si existe el candidato es porque alguien lo votó
	size_t nro_votos; //nro_votos > 0 
};

typedef struct{
	//se representan sobre una estructura cada una de las opciones con sus votos
	//Por defecto inicia en: struct opcion == NULL
	//si una opcion existe es porque tiene un voto
	struct opcion *opciones; //no hay candidatos repetidos
	//n_op representa la cantidad de opciones que tiene al menos un voto
	//Por defecto inicia en 0 (cero)
	size_t n_op; //n_op == 0 <=> struct opcion == NULL
}votacion_t;


char *votacion_ganador(const votacion_t *v){
	size_t w = 0;
	
	for(size_t i = 1; i < v->n_op; i++){
		if(v->opciones[i-1].nro_votos < v->opciones[i].nro_votos){
			w = i;
		}
	}

	return v->opciones[w].nombre;
}




bool votacion_votar(votacion_t *v, const char *nombre){
	for(size_t j = 0; j < v->n_op; j++){
		if( !strcmp(nombre, v->opciones[j].nombre)){
			v->opciones[j].nro_votos++;
			return true;
		}
	}

	struct opcion *p = realloc(v->opciones,(v->n_op + 1)*sizeof(struct opcion));
	if(p == NULL){
		return false;
	}

	v->opciones = p;
	strcpy(v->opciones[v->n_op].nombre, nombre);
	v->opciones[v->n_op].nro_votos = 1;
	v->n_op++;
	return true;
}

//EJ2
char *leer_cadena(FILE *f){

	size_t n;
	if (fread(&n, sizeof(size_t), 1, f) != 1){
		return NULL;
	}

	char *s = malloc((n+1)*sizeof(char));
	if(s == NULL){
		return NULL;
	}

	if (fread(s, sizeof(char), n, f) != n){
		free(s);
		return NULL;
	}


	s[n] = '\0';
	return s;
}



//EJ3
int main(int argc, char *argv[]){

	if(argc != 3){
		fprintf(stderr, "Uso; %s <archivo> n\n", argv[0]);
		return 1;
	}

	size_t n = atof(argv[2]);

	FILE *fi = fopen(argv[1], "rb");
	if ( fi == NULL){
		fprintf(stderr,"Error al abrir el archivo: %s\n", argv[0]);
		return 1;
	}

	
	for(size_t i = 0; i < n; i++){

		char *string = leer_cadena(fi);
		
		if( string != NULL){
			fprintf(stderr,"Error");
			fclose(fi);
			return 1;
		}

		fprintf(stdin, "%s ", string);
		free(string);
	}
	
	fclose(fi);

	return 0;
}







