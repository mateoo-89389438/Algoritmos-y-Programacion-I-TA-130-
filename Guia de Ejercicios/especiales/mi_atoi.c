#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


int mi_atoi(char s[]){
  size_t i;
  
  for(i=0; (s[i] >= '0' && s[i] <= '9'); i++){
  }

  int n = 1;
  int num = 0;

  while(i>0){
    i--;
    num += (s[i] - '0')*n;
    n *= 10;
  }

  return num;
}



int main(){
	char buffer[100];
  puts("ingresa un numero");
  fgets(buffer, 100, stdin);
  int n = mi_atoi(buffer);
  printf("El numero ingresado es: %d", n);
  return 0;
}
	




