#include <stdio.h>
#include <string.h>

#define MAX 10

void invertir(char s[], char g[]){
  
  size_t n = strlen(s); //no cuenta el '\0'
  for(size_t i= 0; s[i] != 0; i++){
    g[n-i-1] = s[i];
  }
  g[n] = '\0'; // Asigna el caracter nulo al final
}

int main (){
  char cadena[] = "hola";
  char buffer[MAX];
  invertir(cadena, buffer);

  printf("%s\n", buffer);
 

  return 0;
}
