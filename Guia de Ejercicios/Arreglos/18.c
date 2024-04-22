#include <stdio.h>

#define N 3
#define M 3

int traza(size_t n, int matriz[n][n]){
  int t;
  for (size_t i= 0; i<n; i++){
    t += matriz[i][i];
  }
  return t;
}

void sumarN(size_t n, size_t m, int matriz[n][m], size_t c){
  for(size_t i=0; i<n; i++){
    for(size_t j=0; j<m;j++){
      matriz[i][j] += c;
    }
  }
}

void multiplicarN(size_t n, size_t m, int matriz[n][m], size_t c){
  for(size_t i=0; i<n; i++){
    for(size_t j=0; j<m;j++){
      matriz[i][j] *= c;
    }
  }
}

int main(void) {
  int matriz[N][M]={
    {50,2,3},
    {4,5,6},
    {7,8,1},
  };

  printf("La traza de la matriz es: %d\n", traza(N, matriz));

  sumarN(N, M, matriz, 10);

  puts("Matriz sumada");
  for(size_t k =0; k<N; k++){
    for(size_t g =0; g<M; g++){
      printf("%d    ", matriz[k][g]);
    }
    puts("");
  }

  multiplicarN(N, M, matriz, 10);
  puts("Matriz multiplicada");
  for(size_t k =0; k<N; k++){
    for(size_t g =0; g<M; g++){
      printf("%d    ", matriz[k][g]);
    }
    puts("");
  }
  return 0;
}