#include <stdio.h>

//Puntero a un arreglo;
int main() {
  int x[5] = {1,2,3,4,5};
  int (*p)[5] = &x;
  size_t tamanox = sizeof(x);
  size_t len = sizeof(x)/sizeof(x)[0];
  size_t tamanop = sizeof(p);
  for(size_t i =0; i <len; i++){
    printf("%d ", (*p)[i]);
  }
  
  putchar('\n');
  printf("sizeof(x) = %zu", tamanox);

  putchar('\n');
  printf("len(x) = %zu", len);
  
  putchar('\n');
  printf("sizeof(p) = %zu", tamanop);
  return 0;
}