#include <stdio.h>

int main(){
    float C;
    
    printf("Ingrese un valor en grado Celsius:\n");
    scanf("%f", &C);
    
    float F = 9.0/5*C+32;
    
    printf("Su valor expresado en Farenheit es: %.2f\n", F);
    return 0;
}