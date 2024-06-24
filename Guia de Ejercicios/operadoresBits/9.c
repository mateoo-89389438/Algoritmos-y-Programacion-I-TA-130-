#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define SHIFT_TXCIE 6

//a.
bool transmision_completa(uint8_t registro){
	return registro & (1 << SHIFT_TXCIE); 
}


//d.
void transmision_completa2(uint8_t registro, uint8_t *n){
	*n = transmision_completa(registro);
}


int main(){

	//b.
	uint8_t miRegistro = 0xC0;
	if(transmision_completa(miRegistro)){
		puts("Transmicion completada");
	}
	else{
		puts("Todavia cargando …… ");
	}


	//d.
	uint8_t resultado;
  	transmision_completa2(miRegistro, &resultado);
	printf("%d", resultado);
	
	return 0;
}







