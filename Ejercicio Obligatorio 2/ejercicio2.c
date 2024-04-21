#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>


#define MAX_CADENA 100



bool son_iguales(const char a[], const char b[]){
	for(size_t i = 0; ( (a[i] != '\0') || (b[i] != '\0') ); i++){
		if (	(toupper (a[i]) != toupper(b[i]))	){
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

  	if(	(s[i] == ' ' )  && (s[i+1] == ':')	){
    	return cantidad;
    }
	}

	return cantidad;

}


bool leer_linea(char s[]){
  char c;
	for (size_t i = 0; (c = getchar()) != '\n'; i++){
		if(c == EOF){
			return false;
		}
		s[i] = c;	
		s[i+1] = '\0';
	}
	
	return true;
}


bool extraer_campo(char campo[], const char s[], size_t c){

	if(	(c<0) || (c > cantidad_campos(s)-1)	){
		return false;
	}


	char buffer[100];

	
	for (size_t g = 0; s[g] != '\0'; g++){
		if(s[0] == ':'){
		  buffer[g] = s[g+1];
		}
		else{
		  buffer[g] = s[g];
		}
	}

	
	size_t i;
	size_t numeroCampo = 0;

	for(i = 0; numeroCampo != c; i++){
		if(buffer[i] == ' '){
			numeroCampo++;
		}		
	}

	if(buffer[i] == ':'){
		for(size_t j =0; buffer[i+j] != '\0'; j++){
  		campo[j] = buffer[i+j+1];
	  	campo[j+1] = '\0';
		}
	}
	else{
		for(size_t k =0; buffer[i+k] != ' '; k++){
	  	campo[k] = buffer[i+k];
			campo[k+1] = '\0';
		}
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

  char ping[MAX_CADENA] = "PING";
  char mensaje[MAX_CADENA] = "MENSAJE";
  char saludar[MAX_CADENA] = "SALUDAR";
  char nombre[MAX_CADENA] = "NOMBRE";

  char salir[MAX_CADENA] = "SALIR";

  while (leer_linea(buffer)) {

  	
    extraer_campo(campo0, buffer, 0); 

   	if(son_iguales(salir, campo0)){
   		break;
   	}
   	

    else if (son_iguales(ping, campo0)) {

			printf("PONG ");
			for (int f = 1; f <= ((cantidad_campos(buffer))-1); f++){
				extraer_campo(buffer2, buffer, f);
				printf("%s ", buffer2);
			}
			printf("\n");
		}


		else if(	(son_iguales(mensaje, campo0)) && (cantidad_campos(buffer) == 3)	){
			extraer_campo(buffer2, buffer, 1); 
			printf("%s: ", buffer2);
			extraer_campo(buffer2, buffer, 2); 
			printf("%s ", buffer2);
			printf("\n");
		}

		else if(	(son_iguales(saludar, campo0)) &&	(cantidad_campos(buffer) == 2)	){
			printf("Hola ");
			extraer_campo(buffer2, buffer, 1); 
			printf("%s! ", buffer2);
			printf("\n");
		}

		else if(	(son_iguales(nombre, campo0)) && (cantidad_campos(buffer) == 3)	){
			printf("Bienvenido ");
			extraer_campo(buffer2, buffer, 2); 
			printf("%s, ", buffer2);
			extraer_campo(buffer2, buffer, 1); 
			printf("%s ", buffer2);
			printf("\n");
		}

		else{
			printf("Mensaje de error \n");
		}
	   	
  }

  return 0;
}



