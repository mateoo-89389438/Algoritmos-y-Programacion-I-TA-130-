#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


////////EJ1
bool verificar_paridad(uint8_t dato){
  int n = 0;

  for(size_t i = 0; i < 8; i++){
    if (dato & (1 << i)){
      n++;
    }
  }

  if((n%2) != 0){
    return false;
  }

  return true;
}
//tiene que devolver que 0xfb NO es par, 0xfc SI es par



////////EJ2
typedef struct{
    char * nombre;
    char * apellido;
    int dni;
} persona_t;

persona_t *persona_clonar(const persona_t *p){

    //se crea una nueva instancia de persona_t llamada clon
    persona_t *clon = malloc(sizeof(persona_t));
    
    if (clon == NULL){
        return NULL;
    }
    
    //pido memoria para el nombre y el apellido porque tienen largo variable
    clon->nombre = malloc((1+strlen(p->nombre))*sizeof(char));
    
    if (clon->nombre == NULL){
        free (clon);
        return NULL;
    }
    
    clon->apellido = malloc((1+strlen(p->apellido))*sizeof(char));
    
    if (clon->apellido == NULL){
        free(clon->nombre);
        free (clon);
        return NULL;
    }
    
    strcpy(clon->nombre, p->nombre);
    strcpy(clon->apellido, p->apellido);
    clon->dni = p->dni;
    
    return clon;
}

void persona_destruir(persona_t *p){
        free (p->nombre);
        free(p->apellido);
        free(p);
}



////////EJ3
char *leer_digitos(){
	char *cadena_digitos = NULL;
	int i = 0;

	//Primero tengo que leer esos digitos
	int digito_leido;
	while ((digito_leido = getchar()) != EOF){ //leo todos los caracteres ingresados
		//verifico que todos los caracteres leidos sean numeros
		if ( isdigit(digito_leido) == false){
			break;
		}

		char *puntero_aux = realloc(cadena_digitos, i + 1);  

            return NULL;
        }

        if (puntero_aux == NULL) {
            free(cadena_digitos);
        cadena_digitos = puntero_aux;
        cadena_digitos[i] = digito_leido;
        i++;
    }
    cadena_digitos[i] = '\0';
	return cadena_digitos;
}





int main(){
	//EJ1
	uint8_t dato = 0xFB;

	if (verificar_paridad(dato)){
		printf("El dato es par\n");
	}
	else{
		printf("El dato no es par\n");
	}
	return 0;

	//EJ2
    persona_t persona1 = {"Santiago", "Lopez", 12345678};
    persona_t *clon = persona_clonar(&persona1);
    printf("%s %s %d\n", clon->nombre, clon->apellido, clon->dni);
    persona_destruir(clon);


    //EJ3
	char *digitos = leer_digitos();
	    if (digitos) {
	        printf("Dígitos leídos: %s\n", digitos);
	        free(digitos);
	    }
    
    return 0;
}