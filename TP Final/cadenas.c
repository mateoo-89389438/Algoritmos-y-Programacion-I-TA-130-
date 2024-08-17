#include "cadenas.h"

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_STRING 100


bool son_iguales(const char a[], const char b[]){
	for(size_t i = 0; ( (a[i] != '\0') || (b[i] != '\0') ); i++){
		if ( (toupper (a[i]) != toupper(b[i]) ) ){
			return false;
		}			     
	}
	return true;
}


size_t cantidad_campos(const char s[]){
	size_t cantidad = 1;
	for(size_t i = 0; s[i] != '\0'; i++){
		if(s[i] == ' '){
			cantidad++;
		}

		if(  (s[i] == ' ' )  && (s[i+1] == ':') ){
			return cantidad;
		}
	}

	return cantidad;

}


bool leer_linea(char s[]){
	char c;
	size_t i = 0;

	while( (c = getchar()) != '\n' ){
		if(c == EOF){
			return false;
		}
		s[i] = c;
		i++;
	}

	s[i] = '\0';
	return true;
}


char *leer_linea_archivos(int fd){
	char c;
	size_t i = 0;
	char *s = NULL;  
	ssize_t n;
	while ((n = read(fd, &c, sizeof(char))) == 1) { 
		if (c != '\r') {
			if (c == '\n') {
				break;
			}
			char *p = realloc(s, i + 2);  
			if (p == NULL) {
				free(s);
				return NULL;  
			}
			s = p;
			s[i] = c;
			i++;
		}
	}
	s[i] = '\0';  
	return s;  
}



bool extraer_campo(char campo[], const char s[], size_t c){

	//verifico el numero del campo pedido (c)
	if( (c<0) || (c > cantidad_campos(s)-1) ){
		return false;
	}


	char buffer[100];

	size_t g;
	for (g = 0; s[g] != '\0'; g++){
		if(s[0] == ':'){
			buffer[g] = s[g+1];
		}
		else{
			buffer[g] = s[g];
		}
	}
	buffer[g] = '\0';

	size_t i;
	size_t numeroCampo = 0;

	for(i = 0; numeroCampo != c; i++){
		if(buffer[i] == ' '){
			numeroCampo++;
		}		
	}

	//Si arranca con : 
	if(buffer[i] == ':'){
		size_t j;
		for(j =0; buffer[i+j] != '\0'; j++){
			campo[j] = buffer[i+j+1];
		}
		campo[j] = '\0';
	}
	else{
		size_t k;
		for(k =0; (buffer[i+k] != ' ') && (buffer[i+k] != '\0'); k++){
			campo[k] = buffer[i+k];
		}
		campo[k] = '\0';
	}

	return true;
}



size_t buscar_cadena(const char s[], char opciones[][MAX_STRING], size_t n_opciones){
	size_t i;
	for(i = 0; i<n_opciones; i++){
		if ( son_iguales(opciones[i],s) ){
			return i;
		}
	}

	return i++;
}

