#include <stdio.h>

#define MAX 100

//defino la estructura
struct estudiante{
    char apellido[MAX];
    int  padron;
    char carrera [MAX];
};

//reedefinio la estructura
typedef struct estudiante estudiante_t;

//funcion para imprimir por pantalla

void imprimir(const estudiante_t *p){
    printf("Apellido: %s\nPadron: %d\nCarrera: %s", p->apellido, p->padron, p->carrera);
}

int main(){
    
    estudiante_t Lean = {"Paredes", 109495, "Civil"};
    
    imprimir(&Lean);
    
    
    return 0;
}