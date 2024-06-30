#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define N 3
#define MAX 100

//EJ1
void left_trim(char cadena[]){
    while (cadena[0] == ' '){
        for(size_t i = 0; cadena[i] != '\0'; i++){
          cadena[i] = cadena[i+1];
        }
    }

}

//EJ2
bool es_triangular_superior(size_t n, float matriz[][n]){

    for(size_t i = 0; i<n; i++){

        for(size_t j = 0; j<=i;j++){

            if (matriz[i][j] != 0){
                return false;
            }
        }
    }
    return true;
}



int main(){
    //EJ1
    char cadena[] = "   hola mundo   ";
    left_trim(cadena);
    printf("#%s#\n", cadena);

    //EJ2
    float matriz_ejemplo[][N] = {
        {0,2,3},
        {0,0,2},
        {0,0,0}
    };

    if (es_triangular_superior(N, matriz_ejemplo)){
        printf("Es triangular superior\n");
    }
    else{
        printf("No es triangular superior\n");
    }


    //EJ3
    char buffer[MAX];
    printf("Ingrese un numero positivo para calcular la raiz cuadrada: ");
    fgets(buffer, MAX, stdin);
    double x = atof(buffer);


    if (x<0){
        printf("Tiene que ser positivo");
    }
    else{
        printf("La raiz es %f\n", sqrt(x));
    }

    return 0;
}
