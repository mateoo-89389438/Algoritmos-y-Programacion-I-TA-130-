// Ej_19. Escribir una funcion que calcule el numero combinatorio n,k:

#include <stdio.h>

double factorial(int n) {
    double f = 1;
    for(int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}


int combinatoria(int n, int k){
    return factorial(n)/ (factorial(k)*factorial(n-k));
}

int main(){
    int n = 9;
    int k = 6;
    printf("%d",combinatoria(n,k));
    return 0;
}