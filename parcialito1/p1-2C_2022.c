#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

// 1
void imprimir_numero1(int n) {
/*    if(n < 0) {
        putchar('-');
        n = -n;
    }*/

    int digitos[20];
    int i;
    for(i = 0; n != 0; i++) {
        digitos[i] = n % 10;
        n /= 10;
    }

    for(; i > 0; i--)
        putchar(digitos[i - 1] + '0');
}

int diez_a_la(int n) {
    int potencia = 1;
    for(int i = 0; i < n; i++)
        potencia *= 10;
    return potencia;
}

void imprimir_numero2(int n) {
    int digitos;
//    int potencia = 1;

    int nn = n;
    for(digitos = 0; nn != 0; digitos++) {
        nn /= 10;
//        potencia *= 10;
    }

    for(int i = 0; i < digitos; i++) {
        putchar((n / diez_a_la(digitos - i - 1)) % 10 + '0');
//      potencia /= 10;
    }
}

// 2.a
bool es_inclusivo(const char s[]) {
    for(size_t i = 0; s[i] != '\0'; i++)
        if(s[i] == 'e')
            return true;
    return false;
}

// 3

int main(void) {
    // 1
    imprimir_numero1(9511);
    putchar('\n');
    imprimir_numero2(9511);
    putchar('\n');

    // 2.b
/*    if(es_inclusivo("alumnes"))
        puts("Es inclusivo");
    else
        puts("No es inclusivo");
    */
    printf("%ses inclusivo\n", es_inclusivo("alumnes") ? "" : "no ");

    // 3
    char aux[MAX];

    printf("Ingrese una distancia: ");
    fgets(aux, MAX, stdin);
    float distancia = atof(aux);

    printf("Ingrese un tiempo: ");
    fgets(aux, MAX, stdin);
    float tiempo = atof(aux);

    if(tiempo == 0) {
        printf("Tiempo invÃ¡lido\n");
        return 1;
    }

    printf("La velocidad es %f\n", distancia / tiempo);

    return 0;
}