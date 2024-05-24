#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//EJ2
/*
bool es_inclusiva(char cadena[]){
	for (int i = 0; cadena[i] != '\0'; i++){
		if (cadena[i] == 'e'){
      return true;
    }
	}
  return false;
}
*/

int main(){
	//EJ2
	/*
	char cadena[] = "les niñes";
	if (es_inclusiva(cadena)){
		puts("Contiene letra 'e'");
	}
	else{
		puts("No contiene letra 'e'");
	}
	return 0;
	*/

	//EJ3
	char buffer[MAX];

	puts("Ingrese la distancia (m)");
	fgets(buffer, MAX, stdin);

	double d = atof(buffer);


	puts("Ingrese el tiempo (s)");
	fgets(buffer, MAX, stdin); //tengo que pasar si o si el tamaño del vector
	double t = atof(buffer);

	if (d > 0 && t > 0){
		printf("La velocidad es: %f m/s\n", d/t);
	}
	else{
		puts("No se pudo calcular");
	}
}









