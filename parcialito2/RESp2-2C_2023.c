#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


//1.
bool misma_cantidad(uint32_t n){
  size_t contadorPares = 0;
  size_t contadorImpares = 0;

  for(size_t i = 0; i<(sizeof(n)*8); i+=2){
    if(n & (1 << i)){
      contadorPares++;
    }

    if(n & (1 << (i+1))){
      contadorImpares++;
    }
  }

  if(contadorPares != contadorImpares){
    return false;
  }

  return true;

}

// EJ2

char *join(char *cadenas[], size_t n, char separador) {

    size_t longitud = 0;

    for(size_t i = 0; i < n; i++){
        longitud += strlen(cadenas[i]);
    }

    char *s = malloc( (longitud + n) * sizeof(char) );
    if(s == NULL){
        return NULL;
    }

    s[0] = '\0';

    for(size_t j = 0; j < n; j++) {
      strcat(s, cadenas[i]);
      s[strlen(s)] = separador; 
    }

    return s;
}


// a)
enum palos {ORO, COPA, ESPADA, BASTO};

struct carta {
    int valor;
    enum palos palo;
};

// b)
typedef struct carta carta_t;

// c)
// Esta es una posible implementacion, no pedida
carta_t *sacar_carta_del_mazo() {
    carta_t *c = malloc(sizeof(carta_t));
    if(c == NULL) return NULL;
    c->palo = rand() % 4;
    c->valor = rand() % 12 + 1;
    return c;
}

carta_t **tirar_reyes(size_t *n){

  carta_t ** v = NULL;
  *n = 0;

  while(1){
    carta_t ** w = realloc(v, (*n+1)*sizeof(carta_t *));
    if(w == NULL){
      return v;
    }
    v = w;

    carta_t * p = sacar_carta_del_mazo();
    v[*n] = p;
    (*n)++;

    if( (p-> valor) == 12){
      break;
    }
  }
  return v;
}



int main() {
  //EJ1
  uint32_t numero = 0x4B; // 0100 1011

  if(misma_cantidad(numero)){
    puts("true");
  }
  else{
    puts("false");
  }
  return 0;


  //EJ2
  char * misCadenas[] = {"Hola", "que", "tal"}; 
  char * s = join(misCadenas, 3, ' ');

  if (s == NULL) {
      puts("Error");
      return 1;
  }

  printf("%s\n", s);

  free(s);

  return 0;

  // EJ3
  char *palos[] = {"oro", "copa", "espada", "basto"};
  size_t n;
  carta_t **cartas = tirar_reyes(&n);
  for(size_t i = 0; i < n; i++)
      printf("%d %s\n", cartas[i]->valor, palos[cartas[i]->palo]);

  for(size_t i = 0; i < n; i++){
    free(cartas[i]);
    free(cartas);
  }
      


  return 0;

}

