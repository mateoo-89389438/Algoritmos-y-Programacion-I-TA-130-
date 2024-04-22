// Ej_18
#include <stdio.h>

//a. Factorial: n! 
double factorial(int n) {
    double f = 1;
    
    for(int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}


int main(void) {

    //a. factorial
    int n = 5; // Aquí asignamos el valor 5 a la variable n.
    printf("%d! = %f\n", n, factorial(n)); // Imprimimos el resultado del factorial de 5.
    return 0;
}

