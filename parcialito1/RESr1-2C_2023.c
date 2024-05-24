#include <stdbool.h>
#include <ctype.h>

#define N 3
#define M 3

//EJ1
void left_trim(char cadena[]){
  while (cadena[0] == ' '){
    for(size_t i = 0; cadena[i] != '\0'; i++){
      cadena[i] = cadena[i+1];
    }
  }
}

//EJ2
/*
bool es_traspuesta(float matrizA[N][M], float matrizB[M][N]){
	for (int i=0; i<N, i++){
		for(int j=0; j<M, j++){
			if(matrizA[i][j] != matrizB[j][i]){
			return false;
			}
		}
	}
	return true;
}
*/

//EJ3
//va todo en el main, no hay funciones por fuera


int main(){

	//EJ1
	
	char nombre[] = "   hola mundo ";
	left_trim(nombre);
	puts(nombre);
	
	//EJ2
	/*
	float matrizA[N][M]={
		{0,2,3},
		{4,0,5},
	};

	float matrizB[M][N]={
		{0,2},
		{4,0},
		{6,0}
	};
	*/

	//EJ3
	//hace lo pedido pero cuenta mal. Cuenta espacios de mas
	/*
	int c;
	int cant = 0;
	puts("Ingrese caracteres\n");
	while ((c = getchar()) != EOF){
		if (isspace (c)){
			cant += 1;
		}
	}

	printf("%d\n", cant);
	*/

	return 0;
}
