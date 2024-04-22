#include <stdio.h>
#include <stdbool.h>
#include <math.h>


bool es_primo(int n){
	int raiz_n = sqrt(n);
	for (int i=2; i<= raiz_n; i++){
		if ((n % i) == 0){
			return false; 
		}
	}
	return true;
}

int main() {
  //imprimir todos los numeros primos entre 1 y 100;
  for (int j = 3; j<=99; j++){
    if(es_primo(j)){
      printf("%d\n", j);
    }
  }

  //imprimr los primeros 100 primos
  int contador = 0;
  for (int j = 1; contador < 100; j++){
    if(es_primo(j)){
      printf("%d\n", j);
      contador += 1;
    }
  }
  
  return 0;
}