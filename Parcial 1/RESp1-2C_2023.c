#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 3

//EJ1
bool esVocal(char c){
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}


void abreviar_texto(char nombre[]){
    for (size_t j = 0; nombre[j] != '\0'; j++){
        if (esVocal(nombre[j])){
            for(size_t i = j; nombre[i] != '\0'; i++){
                nombre[i] = nombre [i+1];
            }
        j--;
        }
    }
}



//EJ2
bool es_suma(size_t n, size_t m, float matriz[n][m]) {
    for (size_t i = 1; i < n; i++) {
        for (size_t j = 1; j < m; j++) {
            if (matriz[i][j] != (matriz[i-1][j] + matriz[i][j-1])) {
                return false;
            }
        }
    }
    return true;
}

//EJ3
char minutos_totales(char m, char t){

    char tiempo_total = m;

    if (t == 2){
        tiempo_total = (tiempo_total + 45);
    }

    return tiempo_total;
}

char minutos_totales(char m, char t){

    if (t == 2){
        m += 45;
    }

    return m;
}





int main(){
    //main EJ1
    char materia[] = "algoritmos y programacion";

    abreviar_texto(materia);

    for (int i = 0; materia[i] != '\0'; i++){
        printf("%c", materia[i]);
    }


    // main EJ2
    float matriz_ejemplo[N][N] = { 
        {1, 2, 3},
        {4, 6, 9},
        {5, 11, 20}
    };

    if (es_suma(N, N, matriz_ejemplo)) {
        printf("cumple la condicion\n");
    } 
    else{
        printf("no cumple la condicion\n");
    }



    //main EJ3

    char aux[100];

    printf("Ingrese los minutos: ");
    fgets(aux, 100, stdin);
    int m = atoi(aux);

    printf("Ingrese el tiempo: ");
    fgets(aux, 100, stdin);
    int t = atoi(aux);

    if (t<0 || t>2 || m<0 || m>45){
      printf("Pusiste mal los minutos o el tiempo")
        return 1;
      }
    else{
      printf("Los minutos de partidos son %d\n",minutos_totales(m, t));
    }

    
    return 0;
}





