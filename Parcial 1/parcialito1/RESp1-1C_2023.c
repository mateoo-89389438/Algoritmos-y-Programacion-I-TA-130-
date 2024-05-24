#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define PI 3.14159625
#define N 3

//EJ1
/*
void abreviar_nombre(char nombre[]){
  size_t i;
  for(i=0; nombre[i+2] != 0; i++){
  }
  nombre[1] = i +'0';
  nombre[2] = nombre[i+1];
  nombre[3] = '\0';
}
*/

//EJ2
bool es_simetrica(float matriz[N][N]){
	for (int f = 0; f<N; f++){
		for (int c=0; c<N; c++){
			if (matriz[f][c] != matriz[c][f]){
				return false;
			}
		}
	}
	return true;
}



//EJ3
/*
double periodo(double m, double k){
	double t = 2*PI*sqrt(m/k);
	return t;
}
*/







int main(){
	//EJ1
	/*
	char cadena[] = "kaaaaaaaaad";
	if(sizeof(cadena) > 3 && sizeof(cadena) < 14){
		abreviar_nombre(cadena);
		puts(cadena); //no imprimo con for porque el \0 que puse termina la cadena
		return 0;
	}
	else{
		puts("No se pudo abreviar la cadena");
		return 1;
	}
	}*/
	

	//EJ2
	float matriz[N][N]={
		{0,2,3},
		{2,0,8},
		{3,8,0},
	};
	if (es_simetrica(matriz)){
		puts("Es simetrica");
	}
	else{
		puts("no es simetrica");
	}


	/*
	//EJ3
	char buffer[100];
	puts("Ingrese la masa del sistema");
	fgets(buffer, sizeof(buffer), stdin);
	double m = atof(buffer);

	puts("Ingrese el constante eleastica del resorte");
	fgets(buffer, sizeof(buffer), stdin);
	double k = atof(buffer);

	printf("El periodo es: %f", periodo(m,k));
	return 0;
	*/

}















