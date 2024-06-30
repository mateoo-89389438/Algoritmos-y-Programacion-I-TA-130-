#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CADENA 100


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




bool extraer_campo(char campo[], const char s[], size_t c){

  	//verifico el numero del campo pedido (c)
	if( (c<0) || (c > cantidad_campos(s)-1) ){
		return false;
	}

	char buffer[100];

  	//copio todo a la cadena buffer
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

  	//trabajo solamente con el buffer
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



size_t buscar_cadena(const char s[], char opciones[][MAX_CADENA], size_t n_opciones){
	size_t i;
	for(i = 0; i<n_opciones; i++){
		if ( son_iguales(opciones[i],s) ){
			return i;
		}
	}

	return i++;
}



int main() {
	char buffer[MAX_CADENA];
	char buffer2[MAX_CADENA];

	char campo0[MAX_CADENA];

	char opciones[][MAX_CADENA] = {"PING", "MENSAJE", "SALUDAR", "NOMBRE", "SALIR" };

	while (leer_linea(buffer)) {

		size_t n_campos = cantidad_campos(buffer);

		//saco el campo 0 de lo que ingresó el usuario
		extraer_campo(campo0, buffer, 0);

		size_t pos = (buscar_cadena(campo0, opciones, 5));
		
		//SALIR
		if ( pos == 4){
			break; //rompo el while y va al return 0
		}

		// PING
		else if (pos == 0){

			printf("PONG ");

			for (int f = 1; f < n_campos; f++){
				extraer_campo(buffer2, buffer, f);
				printf("%s ", buffer2);
			}
			
			printf("\n");
		}
		
		//MENSAJE
		else if(pos == 1){
			extraer_campo(buffer2, buffer, 1); 
			printf("%s: ", buffer2);
			extraer_campo(buffer2, buffer, 2); 
			printf("%s ", buffer2);
			printf("\n");
		}

		//SALUDAR
		else if(pos == 2){
			printf("Hola ");
			extraer_campo(buffer2, buffer, 1); 
			printf("%s! ", buffer2);
			printf("\n");
		}

		//NOMBRE
		else if(pos == 3){
			printf("Bienvenido ");
			extraer_campo(buffer2, buffer, 2); 
			printf("%s, ", buffer2);
			extraer_campo(buffer2, buffer, 1); 
			printf("%s ", buffer2);
			printf("\n");
		}

		//OTRO MENSAJE
		else{
			printf("Mensaje de error \n");
		}

	}
	return 0;
}



