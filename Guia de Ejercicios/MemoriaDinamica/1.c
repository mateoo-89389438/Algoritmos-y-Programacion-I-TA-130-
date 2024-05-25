#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>


//a.
char * copiarCadena1(const char * string){
	
	//pido memoria para la nueva cadena
	char * p = malloc( (strlen(string) + 1) *sizeof(char));

	strcpy(p, string);
	return p;
}

//b.
bool copiarCadena2(char * string, char ** p){

  char * c = malloc( (strlen(string)+1) * sizeof(char));
  if (c == NULL){
    return false;
  }

  strcpy(c, string); 

  *p = c;  
  return true;
}



int main(){

	//a.
	char miCadena[] = "buenardo";
	char * p; 
	p = copiarCadena1(miCadena);

	if(p != NULL){
		printf("%s\n", p);
		free(p);
	}
	else{
		puts("no se pudo copiar la cadena");
		free(p);
		return 1;
	}

	//b.
	char miCadena[] = "malardo";
  	char * p;

  	if(copiarCadena2(miCadena, &p)){  
    printf("%s\n", p);
  	}
  	else{
    puts("No se pudo copiar la cadena");
    return 1;
  	}


	return 0;
}








