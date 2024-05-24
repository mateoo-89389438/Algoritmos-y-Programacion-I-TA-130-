#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define MASK 0x01
// 11001100

bool verificar_paridad (uint8_t dato){

    size_t cantidad_unos = 0;

    for (size_t i = 0; i < 8; i++){

        if ((dato >> i)  & MASK == 1)
            cantidad_unos++;
    }
    
    return cantidad_unos % 2 == 0;
}




// EJ2

struct persona {
    char * nombre;
    char * apellido;
    int dni;
};

typedef struct persona persona_t;

persona_t *persona_clonar(const persona_t *p) {
    persona_t * clon;
    
    clon = malloc(sizeof(persona_t));
    if (clon == NULL) {
        return NULL;
    }

    clon->dni = p->dni; 

    clon->nombre = malloc(sizeof(char) * (1 + strlen(p->nombre)));
    if (clon->nombre == NULL) {
        free(clon);
        return NULL;
    }
    clon->apellido = malloc(sizeof(char) * (1 + strlen(p->apellido)));
    if (clon->apellido == NULL) {
        free(clon->nombre);
        free(clon);
        return NULL;
    }
    strcpy(clon->nombre, p->nombre);
    strcpy(clon->apellido, p->apellido);

    return clon;
}

void persona_destruir(persona_t *p) {
    free(p->nombre);
    free(p->apellido);
    free(p);
}






char *leer_digitos() {
    char *digitos = NULL;

    int digit;
    size_t i = 0;
    while( (digit = getchar() ) != EOF) {


        if (!isdigit(digit)) {
            break;
        }


        char *aux = realloc(digitos, i + 1);  // realloc(NULL) == malloc()
        if (aux == NULL) {
            free(digitos);
            return NULL;
        }

        digitos = aux;
        digitos[i] = digit;
        i++;
    }


    char * aux = realloc(digitos, i + 1);  // realloc(NULL) == malloc()
    if (aux == NULL) {
        free(digitos);
        return NULL;

    }
    digitos = aux;
    digitos[i] = '\0';
    return digitos;
}










int main (void){
    uint8_t chequear = 0xFF;
    printf("el dato %s es par\n", verificar_paridad(chequear) ? "" : "no");
    assert(verificar_paridad(0xF0));
    assert(verificar_paridad(0x0C));
    assert(!verificar_paridad(0x5D));

    persona_t original = {"Santiago", "Lopez", 12345678};
    persona_t *clon = persona_clonar(&original);
    printf("%s %s %d\n", clon->nombre, clon->apellido, clon->dni);
    persona_destruir(clon);

    char *digitos = leer_digitos();
    puts(digitos);
    free(digitos);

    return 0;
}
